#define ENABLE_WIFI (1)
#define ENABLE_DISPLAY (1)
#define ENABLE_GPS (1)

#include "SPI.h"
#include <Wire.h>
#include <wiring.h>

#if ENABLE_WIFI
  #include <Adafruit_CC3000.h>
  #include <Adafruit_CC3000_Server.h>
  #include <ccspi.h>
  
  #include "wifi.h"
  
  // These are the interrupt and control pins
  #define ADAFRUIT_CC3000_IRQ   3  // MUST be an interrupt pin!
  // These can be any two pins
  #define ADAFRUIT_CC3000_VBAT  5
  #define ADAFRUIT_CC3000_CS    10
  
  #define DEVICE_NAME "CC3000"
  
  // Use hardware SPI for the remaining pins
  // On an UNO, SCK = 13, MISO = 12, and MOSI = 11
  Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ,  ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIVIDER);
#endif // ENABLE_WIFI

#if ENABLE_DISPLAY
  #include "Adafruit_GFX.h"
  // #include "Adafruit_ILI9340.h"
  #include "TFT_ILI9340.h"
  
  #include "display.h"
  
  // These are the pins used for the UNO
  // for Due/Mega/Leonardo use the hardware SPI pins (which are different)
  #define _sclk 13
  #define _miso 4
  #define _mosi 11
  #define _cs 10
  #define _dc 9
  #define _rst 8
  
  // Using software SPI is really not suggested, its incredibly slow
  //Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _mosi, _sclk, _rst, _miso);
  // Use hardware SPI
  // Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _rst);
  TFT_ILI9340 tft = TFT_ILI9340(_cs, _dc, _rst);
#endif // ENABLE_DISPLAY

#if ENABLE_GPS
  #include <Adafruit_GPS.h>
  
  Adafruit_GPS GPS(&Serial1);

  // Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
  // Set to 'true' if you want to debug and listen to the raw GPS sentences
  #define GPSECHO  (true)
  
  // this keeps track of whether we're using the interrupt
  // off by default!
  boolean usingInterrupt = false;
  void useInterrupt(boolean val) {
    usingInterrupt = val;
  }
#endif // ENABLE_GPS

#include "TSL2561.h"

/***************************************************
 * This is an example sketch for the Adafruit 2.2" SPI display.
 * This library works with the Adafruit 2.2" TFT Breakout w/SD card
 * ----> http://www.adafruit.com/products/1480
 * 
 * Check out the links above for our tutorials and wiring diagrams
 * These displays use SPI to communicate, 4 or 5 pins are required to
 * interface (RST is optional)
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 * 
 * Written by Limor Fried/Ladyada for Adafruit Industries.
 * MIT license, all text above must be included in any redistribution
 ****************************************************/



HardwareSerial Uart = HardwareSerial();


#if defined(__SAM3X8E__)
  #undef __FlashStringHelper::F(string_literal)
  #define F(string_literal) string_literal
#endif

// include the SD library:
#include <SD.h>

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
// Teensy 2.0: pin 0
// Teensy++ 2.0: pin 20
const int chipSelect = 10;    

// connect SCL to analog 5
// connect SDA to analog 4
// connect VDD to 3.3V DC
// connect GROUND to common ground
// ADDR can be connected to ground, or vdd or left floating to change the i2c address

// The address will be different depending on whether you let
// the ADDR pin float (addr 0x39), or tie it to ground or vcc. In those cases
// use TSL2561_ADDR_LOW (0x29) or TSL2561_ADDR_HIGH (0x49) respectively
TSL2561 tsl(TSL2561_ADDR_FLOAT); 

boolean setupSdCard() {
  Serial.print("\nInitializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
  pinMode(10, OUTPUT);     // change this to 53 on a mega


  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card is inserted?");
    Serial.println("* Is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    return false;
  } 
  else {
    Serial.println("Wiring is correct and a card is present."); 
  }

  // print the type of card
  Serial.print("\nCard type: ");
  switch(card.type()) {
  case SD_CARD_TYPE_SD1:
    Serial.println("SD1");
    break;
  case SD_CARD_TYPE_SD2:
    Serial.println("SD2");
    break;
  case SD_CARD_TYPE_SDHC:
    Serial.println("SDHC");
    break;
  default:
    Serial.println("Unknown");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    return false;
  }


  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("\nVolume type is FAT");
  Serial.println(volume.fatType(), DEC);
  Serial.println();

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize *= 512;                            // SD card blocks are always 512 bytes
  Serial.print("Volume size (bytes): ");
  Serial.println(volumesize);
  Serial.print("Volume size (Kbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Mbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);


  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);

  return true;
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

extern int getFreeRam(void);

volatile boolean sdInited = false;

void setupSerial() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Uart.begin(9600);
  
  // wait for serial port to connect. Needed for Leonardo only
  // while (!Serial) {
  //   ;
  // }
}

void setupTft() {
  tft.begin();
  
  #if defined(__MK20DX128__) || defined(__MK20DX256__)
    //want try the fastest?
    tft.setBitrate(24000000);
  #endif

  tft.fillScreen(ILI9340_BLACK);
  tft.setRotation(1);
}

void setupWifi() {
  Serial.println(F("Initializing CC3000 ..."));
  if (!cc3000.begin(false))
  {
    Serial.println(F("Unable to initialise the CC3000! Check your wiring?"));
    // while(1);
  } 
  else {
    Serial.println(F("CC3000 initialized!"));
  }
}

void setup() {
  
  setupSerial();

  sdInited = setupSdCard();

  setupGps();

  Serial.println("Adafruit 2.2\" SPI TFT Test!"); 

  #if ENABLE_WIFI
    setupWifi();
  #endif // WIFI_ENABLED

  setupTft();
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
  if (timer > millis())  timer = millis();

  // approximately every 2 seconds or so, print out the current stats
  int ms = millis();
  if (ms - timer > 1000) { 
    timer = ms; // reset the timer

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
    tft.println(ms);

    tft.print("Free RAM: ");
    tft.println(getFreeRam(), DEC);
  }
}

void loop(void) {
  loopGps();

  /*
  for(uint8_t rotation=0; rotation<4; rotation++) {
   tft.setRotation(rotation);
   testDisplay();
   delay(2000);
   }
   //*/
}



