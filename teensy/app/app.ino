#define ENABLE_WIFI (1)
#define ENABLE_DISPLAY (1)
#define ENABLE_GPS (1)
#define ENABLE_SD_CARD (0)
#define ENABLE_TSL_2561 (1)

#include "SPI.h"
#include <Wire.h>
#include <wiring.h>

#include "general.h"
#include "serial.h"

#if ENABLE_WIFI
  #include <Adafruit_CC3000.h>
  #include <Adafruit_CC3000_Server.h>
  #include <ccspi.h>
  
  #include "wifi.h"
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
  #if ENABLE_GPS
    loopGps();
  #endif // ENABLE_GPS
  
  #if ENABLE_DISPLAY
    /*
    for(uint8_t rotation=0; rotation<4; rotation++) {
      tft.setRotation(rotation);
      testDisplay();
      delay(2000);
    }
    //*/
  #endif // ENABLE_DISPLAY
}


