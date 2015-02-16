#include "gps.h"

#include "display.h"

Adafruit_GPS GPS(&Serial1);

extern int getFreeRam(void);

// this keeps track of whether we're using the interrupt
// off by default!
boolean usingInterrupt = false;
void useInterrupt(boolean val) {
  usingInterrupt = val;
}

void setupGps() {
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);

  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  // GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  // GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_ALLDATA);

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
  Serial.println(PMTK_Q_RELEASE);
}

void updateDisplay() {
  tft.setCursor(0, 0);
  //tft.fillScreen(ILI9340_BLACK);
  // tft.clearScreen(ILI9340_BLACK);
  tft.setTextColor(ILI9340_GREEN, ILI9340_BLACK);
  tft.setTextSize(2);
  // tft.println("Groop");

  tft.print("\nTime: ");
  tft.print(GPS.hour, DEC); 
  tft.print(':');
  tft.print(GPS.minute, DEC); 
  tft.print(':');
  tft.print(GPS.seconds, DEC); 
  tft.print('.');
  tft.println(GPS.milliseconds);
  tft.print("Date: ");
  tft.print(GPS.day, DEC); 
  tft.print('/');
  tft.print(GPS.month, DEC); 
  tft.print("/20");
  tft.println(GPS.year, DEC);
  // Serial.print("Fix: "); 
  // Serial.print((int)GPS.fix);
  // Serial.print(" quality: "); 
  Serial.println((int)GPS.fixquality); 
  if (GPS.fix) {
    tft.print("Loc: ");
    tft.print(GPS.latitude * 0.01, 2); 
    //tft.print(GPS.lat);
    tft.print(", "); 
    tft.print(GPS.longitude * 0.01, 2); 
    //tft.println(GPS.lon);
    tft.println();

    tft.print("Speed: "); 
    tft.println(GPS.speed);
    Serial.print("Angle: "); 
    Serial.println(GPS.angle);
    tft.print("Alt: "); 
    tft.println(GPS.altitude);
    Serial.print("Satellites: "); 
    Serial.println((int)GPS.satellites);
  }  

  tft.print("ms: ");
  tft.println(millis());

  tft.print("Free RAM: ");
  tft.println(getFreeRam(), DEC);
}

uint32_t timer = millis();
void loopGps() {
  // in case you are not using the interrupt above, you'll
  // need to 'hand query' the GPS, not suggested :(
  if (! usingInterrupt) {
    // read data from the GPS in the 'main loop'
    char c = '\0';
    do {
      c = GPS.read();

      // if you want to debug, this is a good time to do it!
      if (GPSECHO) {
        if (c) Serial.print(c);
      }
    } 
    while(c);
  }

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
  if (timer > millis())  
    timer = millis();

  // approximately every 2 seconds or so, print out the current stats
  int ms = millis();
  if (ms - timer > 1000) { 
    timer = ms; // reset the timer

    updateDisplay();
  }
}

