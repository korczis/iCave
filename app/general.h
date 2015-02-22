#ifndef ICAVE_GENERAL_H
#define ICAVE_GENERAL_H
  #define ICAVE_VERSION_MAJOR (0)
  #define ICAVE_VERSION_MINOR (0)
  #define ICAVE_VERSION_PATCH (1)
  
  #define JSON_SUPPORT (1)
  #define JSON_STATS (1)
    
  #define PRINT_ENABLED_MODULES (1)

  #define SENSOR_UPDATE_TICKS (10)
  
  // App configuration related defines
  #define ENABLE_DHT (1)
  #define DHT_SHOW_TEMPERATURE (1)
  #define DHT_SHOW_HUMIDITY (1)
  #define DHT_SHOW_HEAT_INDEX (1)
  
  #define ENABLE_DISPLAY (1)
  #define ENABLE_DISPLAY_TEST_LOOP (0)
  #define DISPLAY_STATS (1)
  
  #define ENABLE_EEPROM (1)
  #define EEPROM_UPDATE_RUN_NO (1)
  
  #define ENABLE_GPS (1)
  #define GPS_SHOW_ALTITUDE (1)
  #define GPS_SHOW_ANGLE (0)
  #define GPS_SHOW_DATE (1)
  #define GPS_SHOW_FIX (1)
  #define GPS_SHOW_POSITION (1)
  #define GPS_SHOW_SPEED (1)
  #define GPS_SHOW_TIME (1)
  
  #define ENABLE_RFID (0)
  
  #define ENABLE_SERIAL (1)
  #define SERIAL (1)
  #define SERIAL_WAIT (1) // Wait for Arduino IDE "Serial Monitor to get connected"
  
  #define ENABLE_SD_CARD (1)
  #define ENABLE_SNOOZE (0) // Problematic
  #define ENABLE_TSL_2561 (1)
  #define ENABLE_WIFI (0) // Problematic
  
  typedef enum E_LOOP_TYPE {
    LT_UNKNOWN = -1,
    LT_FIXED_SLEEP,
    LT_FIXED_FPS,
  
    // Last marker
    LT_LAST
  } 
  E_LOOP_TYPE;
  
  // Global LT_FIXED_SLEEP
  #define LOOP_TYPE (LT_FIXED_FPS)
  #define LOOP_INTERVAL (16)
  #define LOOP_FPS (20.0f)
  
  unsigned int getVersionMajor();  
  unsigned int getVersionMinor();  
  unsigned int getVersionPatch();
  
  unsigned int getTotalRam();
 
  #if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
  #endif
#endif // ICAVE_GENERAL_H
