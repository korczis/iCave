#define ENABLE_WIFI (1)
#define ENABLE_DISPLAY (1)
#define ENABLE_GPS (1)
#define ENABLE_SD_CARD (0)

#include "SPI.h"
#include <Wire.h>
#include <wiring.h>

#if ENABLE_WIFI
  #include <Adafruit_CC3000.h>
  #include <Adafruit_CC3000_Server.h>
  #include <ccspi.h>
  
  #include "wifi.h"
  
  // Use hardware SPI for the remaining pins
  // On an UNO, SCK = 13, MISO = 12, and MOSI = 11
  Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ,  ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIVIDER);
  
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
#endif // ENABLE_WIFI

#if ENABLE_DISPLAY
  #include "Adafruit_GFX.h"
  // #include "Adafruit_ILI9340.h"
  #include "TFT_ILI9340.h"
  
  #include "display.h"
#endif // ENABLE_DISPLAY

#if ENABLE_GPS
  #include <Adafruit_GPS.h>
  
  #include "gps.h"
#endif // ENABLE_GPS

#if ENABLE_SD_CARD
  // include the SD library:
  #include <SD.h>
  
  #include "sd_card.h"
#endif // ENABLE_SD_CARD

HardwareSerial Uart = HardwareSerial();

#if defined(__SAM3X8E__)
  #undef __FlashStringHelper::F(string_literal)
  #define F(string_literal) string_literal
#endif

#include "TSL2561.h"

// connect SCL to analog 5
// connect SDA to analog 4
// connect VDD to 3.3V DC
// connect GROUND to common ground
// ADDR can be connected to ground, or vdd or left floating to change the i2c address

// The address will be different depending on whether you let
// the ADDR pin float (addr 0x39), or tie it to ground or vcc. In those cases
// use TSL2561_ADDR_LOW (0x29) or TSL2561_ADDR_HIGH (0x49) respectively
TSL2561 tsl(TSL2561_ADDR_FLOAT); 

void setupSerial() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Uart.begin(9600);
  
  // wait for serial port to connect. Needed for Leonardo only
  // while (!Serial) {
  //    ;
  // }
}

void setup() {
  // First setup serial port for communicating with PC
  setupSerial();

  // Print banner
  Serial.println("iCave 0.0.1"); 

  #if ENABLE_SD_CARD
    sdInited = setupSdCard();
  #endif // ENABLE_SD_CARD
  
  #if ENABLE_GPS
    setupGps();
  #endif // ENABLE_GPS
  
  #if ENABLE_WIFI
    // setupWifi();
  #endif // WIFI_ENABLED

  #if ENABLE_DISPLAY
    setupDisplay();
  #endif // ENABLE_DISPLAY
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



