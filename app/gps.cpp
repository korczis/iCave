#include "display.h"
#include "gps.h"
#include "general.h"
#include "eeprom.h"
#include "dht.h"
#include "tsl_2561.h"

using namespace iCave;

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdio.h>

Adafruit_GPS GPS(&Serial1);

extern int getFreeRam(void);
extern unsigned long last_tick;
extern float fps;
extern float last_tick_diff;

// this keeps track of whether we're using the interrupt
// off by default!
boolean usingInterrupt = false;
void useInterrupt(boolean val) {
  usingInterrupt = val;
}

void GpsModule::setup() {
  if(Serial) {
    Serial.println("Setting up GPS ...");
  }
  
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(GPS_BAUDRATE);

  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  // GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time
  // GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_ALLDATA);

  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

  // the nice thing about this code is you can have a timer0 interrupt go off
  // every 1 millisecond, and read data from the GPS for you. that makes the
  // loop code a heck of a lot easier!
  //useInterrupt(true);

  delay(1000);
  // Ask for firmware version
  Serial.print("GPS: ");
  Serial.println(PMTK_Q_RELEASE);
}

extern unsigned short bootNo;

void GpsModule::updateDisplay() {
  tft.setCursor(0, 0);
  // tft.fillScreen(ILI9340_BLACK);
  tft.setTextColor(ILI9340_GREEN, ILI9340_BLACK);
  tft.setTextSize(2);
  
  char buff[128];
  
  sprintf(buff, "Date: 20%02d/%02d/%02d", GPS.year, GPS.month, GPS.day);
  tft.println(buff);
  
  sprintf(buff, "Time: %02d:%02d:%02d.%02d", GPS.hour, GPS.minute, GPS.seconds, GPS.milliseconds);
  tft.println(buff);
  
  // Serial.print("Fix: "); 
  // Serial.print((int)GPS.fix);
  // Serial.print(" quality: "); 
  // Serial.println((int)GPS.fixquality); 
  
  sprintf(buff, "Loc: %.4f %.4f", GPS.latitude * 0.01, 4, GPS.longitude * 0.01, 4);
  tft.println(buff);
  
  sprintf(buff, "Speed: %.2f", GPS.speed);
  tft.println(buff);
  
  // sprintf(buff, "Angle: %.2f", GPS.angle);
  // tft.println(buff);
  
  sprintf(buff, "Altitude: %.2f", GPS.altitude);
  tft.println(buff);

  sprintf(buff, "Fix: %d, Sats: %d", GPS.fix, GPS.satellites);
  tft.println(buff);  
  
  // tft.println();

  #if ENABLE_DHT
    sprintf(buff, "Temperature: %.2f C", dhtTemperature);
    tft.println(buff);
    
    sprintf(buff, "Humidity: %.2f%%", dhtHumidity);
    tft.println(buff);
    
    sprintf(buff, "Heat Index: %.2f C", dhtHeatIndex);
    tft.println(buff);
    
    // tft.println();
  #endif // ENABLE_DHT
  
  #if ENABLE_TSL_2561
    sprintf(buff, "Lux: %.2f", lux);
    tft.println(buff);
  #endif // ENABLE_2561
  
  unsigned int raw_secs = millis() * 0.001f;
  
  const unsigned int rt_days = raw_secs / 86400;
  raw_secs %= 86400;
  
  const unsigned int rt_hours = raw_secs / 3600;
  raw_secs %= 3600;
  
  const unsigned int rt_mins = raw_secs / 60;
  raw_secs %= 60; 
  
  const unsigned int rt_secs = raw_secs;

  #if DISPLAY_STATS
    sprintf(buff, "Uptime: %02dd %02d:%02d:%02d", rt_days, rt_hours, rt_mins, rt_secs);
    tft.println(buff);
  
    unsigned int mem_free = getFreeRam();
    unsigned int mem_total = getTotalRam();
    
    sprintf(buff, "RAM: %d/%d (%.1f%%)", mem_free, mem_total, ((float)mem_free / (float)mem_total) * 100.0f);
    tft.println(buff);
    
    //*
    sprintf(buff, "Tick: %0.4f, FPS: %0.2f", last_tick_diff, fps);
    tft.println(buff);
    //*/
      
    sprintf(buff, "Ver: %d.%d.%d, Run: #%d", getVersionMajor(), getVersionMinor(), getVersionPatch(), persistenceInfo.bootNo);
    tft.println(buff);
  #endif // DISPLAY_STATS
  
  // tft.setTextColor(ILI9340_RED, ILI9340_BLACK);
  // tft.setTextSize(3);
  // tft.println("\nMarianka");
}

uint32_t timer = millis();
void GpsModule::loop() {
  //*
  // in case you are not using the interrupt above, you'll
  // need to 'hand query' the GPS, not suggested :(
  if (! usingInterrupt) {
    // read data from the GPS in the 'main loop'
    char c = '\0';
    do {
      c = GPS.read();

      // if you want to debug, this is a good time to do it!
      if (GPSECHO && c) {
        Serial.print(c);
      }
    } 
    while(c);
  }
  //*/

  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences! 
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false

    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }

  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis()) { 
    timer = millis();
  }
  
  // approximately every 2 seconds or so, print out the current stats
  int ms = millis();
  if (ms - timer > LOOP_FPS) { 
    timer = ms; // reset the timer

    updateDisplay();
  }
}

