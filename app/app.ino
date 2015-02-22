// Core includes
#include <SPI.h>
#include <Wire.h>
#include <wiring.h>
#include <EEPROM.h>  

// Global iCave App specific includes
#include "./general.h"
#include "./manager.h"
#include "./core.h"

iCave::Manager* manager = NULL;

#if ENABLE_DHT
  #include <DHT.h>
  #include "dht.h"
#endif // ENABLE_DHT

#if ENABLE_DISPLAY
  #include "Adafruit_GFX.h"
  // #include "Adafruit_ILI9340.h"
  #include "TFT_ILI9340.h"
  
  #include "./display.h"
#endif // ENABLE_DISPLAY

#if ENABLE_EEPROM
  #include "eeprom.h"
#endif // ENABLE_EEPROM

#if ENABLE_GPS
  #include <Adafruit_GPS.h>
  
  #include "gps.h"
#endif // ENABLE_GPS

#if ENABLE_RFID
  #include <MFRC522.h>

  #include "rfid.h"
#endif // ENABLE_RFID

#if ENABLE_SD_CARD
  // include the SD library:
  #include <SD.h>
  
  #include "./sd_card.h"
#endif // ENABLE_SD_CARD

// Core Modules
#if ENABLE_SERIAL
  #include "serial.h"
#endif // ENABLE_SERIAL

#if ENABLE_SNOOZE
  // Snooze
  #include <LowPower_Teensy3.h>
  
  #include "snooze.h"
#endif // ENABLE_SNOOZE

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

#if JSON_SUPPORT
  #include <ArduinoJson.h>
#endif // JSON_SUPPORT

/**
 * @brief Main setup
 */
void setup() {  
  manager = new iCave::Manager();
  
  iCave::CoreModule* coreModule = manager->createAndRegisterModule<iCave::CoreModule>();
  
  // Serial needs to be initialized first as it is used for logging
  
  #if ENABLE_SERIAL
    iCave::SerialModule* serialModule = manager->createAndRegisterModule<iCave::SerialModule>();
  #endif // ENABLE_SERIAL
  
  // EEPROM update needs to be done soon as well
  
  #if ENABLE_EEPROM
    iCave::EepromModule* eepromModule = manager->createAndRegisterModule<iCave::EepromModule>();
  #endif // ENABLE_EEPROM
  
  // Alphabetically 
  
  #if ENABLE_DHT
    iCave::DhtModule* dhtModule = manager->createAndRegisterModule<iCave::DhtModule>();
  #endif // ENABLE_DHT
  
  #if ENABLE_DISPLAY
    iCave::DisplayModule* displayModule = manager->createAndRegisterModule<iCave::DisplayModule>();
  #endif // ENABLE_DISPLAY
  
  #if ENABLE_GPS
    iCave::GpsModule* gpsModule = manager->createAndRegisterModule<iCave::GpsModule>();
  #endif // ENABLE_GPS

  #if ENABLE_SD_CARD
    iCave::SdCardModule* sdCardModule = manager->createAndRegisterModule<iCave::SdCardModule>();
  #endif // ENABLE_SD_CARD
  
  #if ENABLE_TSL_2561
    iCave::Tsl2561Module* tsl2561Module = manager->createAndRegisterModule<iCave::Tsl2561Module>();
  #endif // ENABLE_TSL_2561
  
  #if ENABLE_WIFI
    iCave::WifiModule* wifiModule = manager->createAndRegisterModule<iCave::WifiModule>();
  #endif // WIFI_ENABLED

  // Snooze needs to be last ...
  #if ENABLE_SNOOZE
    iCave::SnoozeModule* snoozeModule = manager->createAndRegisterModule<iCave::SnoozeModule>();
  #endif // ENABLE_SNOOZE
  
  // Setup modules registered in manager
  manager->setup();    
}

/**
 * @brief Main loop
 */
void loop(void) {
  // Loop modules registered in manager
  manager->loop();
}

