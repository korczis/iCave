// Core includes
#include <SPI.h>
#include <Wire.h>
#include <wiring.h>
#include <EEPROM.h>  

// Global iCave App specific includes
#include "./general.h"
#include "./manager.h"

iCave::Manager manager;

void printInfo() {
  if(Serial) {
    Serial.print("ENABLE_WIFI = ");
    Serial.println(ENABLE_WIFI);

    Serial.print("ENABLE_DISPLAY = ");
    Serial.println(ENABLE_DISPLAY);

    Serial.print("ENABLE_GPS = ");
    Serial.println(ENABLE_GPS);

    Serial.print("ENABLE_SD_CARD = ");
    Serial.println(ENABLE_SD_CARD);

    Serial.print("ENABLE_TSL_2561 = ");
    Serial.println(ENABLE_TSL_2561);
  }
}

// Core Modules
#if ENABLE_SERIAL
  #include "serial.h"
#endif // ENABLE_SERIAL

#if ENABLE_EEPROM
  #include "eeprom.h"
#endif // ENABLE_EEPROM

#if ENABLE_DISPLAY
  #include "Adafruit_GFX.h"
  // #include "Adafruit_ILI9340.h"
  #include "TFT_ILI9340.h"
  
  #include "./display.h"
#endif // ENABLE_DISPLAY

#if ENABLE_DHT
  #include <DHT.h>
  #include "dht.h"
#endif // ENABLE_DHT

#if ENABLE_GPS
  #include <Adafruit_GPS.h>
  
  #include "gps.h"
#endif // ENABLE_GPS

#if ENABLE_TSL_2561
  #include "TSL2561.h"
  #include "tsl_2561.h"
#endif // ENABLE_TSL_2561

#if ENABLE_WIFI
  #include <Adafruit_CC3000.h>
  #include <Adafruit_CC3000_Server.h>
  #include <ccspi.h>
  
  #include "wifi.h"
#endif // ENABLE_WIFI

#if ENABLE_SD_CARD
  // include the SD library:
  #include <SD.h>
  
  #include "./sd_card.h"
#endif // ENABLE_SD_CARD

#if ENABLE_SNOOZE
  // Snooze
  #include <LowPower_Teensy3.h>
  
  #include "snooze.h"
#endif // ENABLE_SNOOZE

/**
 * @brief Main setup
 */
void setup() {  
  // Print banner
  char buff[128];
  sprintf(buff, "iCave %d.%d.%d", getVersionMajor(), getVersionMinor(), getVersionPatch());
  Serial.println(buff);
  
  #if ENABLE_SERIAL
    manager.createAndRegisterModule<iCave::SerialModule>();
  #endif // ENABLE_SERIAL
  
  #if ENABLE_EEPROM
    manager.createAndRegisterModule<iCave::EepromModule>();
  #endif // ENABLE_EEPROM
  
  #if ENABLE_SD_CARD
    manager.createAndRegisterModule<iCave::SdCardModule>();
  #endif // ENABLE_SD_CARD

  #if ENABLE_DISPLAY
    manager.createAndRegisterModule<iCave::DisplayModule>();
  #endif // ENABLE_DISPLAY
  
  #if ENABLE_DHT
    manager.createAndRegisterModule<iCave::DhtModule>();
  #endif // ENABLE_DHT
  
  #if ENABLE_GPS
    manager.createAndRegisterModule<iCave::GpsModule>();
  #endif // ENABLE_GPS
  
  #if ENABLE_TSL_2561
    manager.createAndRegisterModule<iCave::Tsl2561Module>();
  #endif // ENABLE_TSL_2561
  
  #if ENABLE_WIFI
    manager.createAndRegisterModule<iCave::WifiModule>();
  #endif // WIFI_ENABLED

  #if ENABLE_SNOOZE
    manager.createAndRegisterModule<iCave::SnoozeModule>();
  #endif // ENABLE_SNOOZE
  
  // Setup modules registered in manager
  manager.setup();    
  
  // Print info about enabled components
  printInfo();
}

/**
 * @brief Main loop
 */
unsigned int tickNo = 0;

void loop(void) {
  // Loop modules registered in manager
  manager.loop();  
  
  tickNo++;
}

