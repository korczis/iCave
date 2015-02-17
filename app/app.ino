// Core includes
#include "SPI.h"
#include <Wire.h>
#include <wiring.h>
#include <EEPROM.h>  

typedef enum E_LOOP_TYPE {
  LT_UNKNOWN = -1,
  LT_FIXED_SLEEP,
  LT_FIXED_FPS,

  // Last marker
  LT_LAST
} 
E_LOOP_TYPE;

// Global configuration
#define LOOP_TYPE (LT_FIXED_FPS)
#define LOOP_INTERVAL (16)
#define LOOP_FPS (3.4567f)

// App configuration related defines
#define SERIAL (1)
#define SERIAL_WAIT (0)

#define ENABLE_WIFI (0)

#define ENABLE_DISPLAY (1)
#define ENABLE_DISPLAY_TEST_LOOP (0)

#define ENABLE_GPS (1)
#define ENABLE_SD_CARD (1)
#define ENABLE_TSL_2561 (1)
#define ENABLE_SNOOZE (0)
#define ENABLE_DHT (1)

// Global App specific includes
#include "general.h"
#include "serial.h"
#include "eeprom.h"

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

#if ENABLE_TSL_2561
  #include "TSL2561.h"
#endif // ENABLE_TSL_2561

#if ENABLE_DHT
  #include <DHT.h>
  #include "dht.h"
#endif // ENABLE_DHT

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

#if ENABLE_SNOOZE
// Snooze
// #include <Snooze.h>
#include <LowPower_Teensy3.h>

TEENSY3_LP LP = TEENSY3_LP();

void callbackhandler() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
}

void setupSleepMode() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(0, INPUT_PULLUP);
  attachInterrupt(0, callbackhandler, RISING);
}
#endif // ENABLE_SNOOZE



/**
 * @brief Main setup
 */
void setup() {
  // First setup serial port for communicating with PC
  setupSerial(SERIAL_WAIT);

  // Setup EEPROM
  setupEeprom();

  // Setup sleep mode
#if ENABLE_SNOOZE
  setupSleepMode();
#endif // ENABLE_SNOOZE

  // Print banner
  char buff[128];
  sprintf(buff, "iCave %d.%d.%d", getVersionMajor(), getVersionMinor(), getVersionPatch());
  Serial.println(buff); 

  // Print info about enabled components
  printInfo();

#if ENABLE_SD_CARD
  sdInited = setupSdCard();
#endif // ENABLE_SD_CARD

#if ENABLE_GPS
  setupGps();
#endif // ENABLE_GPS

#if ENABLE_WIFI
  setupWifi();
#endif // WIFI_ENABLED

#if ENABLE_DISPLAY
  setupDisplay();
#endif // ENABLE_DISPLAY
}

unsigned long last_delta = 0;

/**
 * @brief Main loop
 */
void loop(void) {
  const int tick_start = millis();

#if ENABLE_GPS
  loopGps();
#endif // ENABLE_GPS

#if ENABLE_DISPLAY && ENABLE_DISPLAY_TEST_LOOP
  for(uint8_t rotation = 0; rotation < 4; rotation++) {
    tft.setRotation(rotation);
    testDisplay();
    delay(2000);
  }    
#endif // ENABLE_DISPLAY

  if(LOOP_TYPE == LT_FIXED_SLEEP) {
    // Sleep for some time, if needed
    delay(LOOP_INTERVAL);
  } // LT_FIXED_SLEEP

  if(LOOP_TYPE == LT_FIXED_FPS) {
    static const int LOOP_SLEEP_TIME = ((1.0f / LOOP_FPS) * 1000);
    const int tick_loop = millis() - tick_start;
    const int sleep_time = (LOOP_SLEEP_TIME - tick_loop);

    Serial.println(sleep_time);

    delay(sleep_time >= 0 ? sleep_time : 1);
  } // LT_FIXED_FPS

  // Leak test
  // char* data = new char(64);

  last_delta = millis() - tick_start;

#if ENABLE_SNOOZE
  LP.Sleep();
#endif // ENABLE_SNOOZE


#if ENABLE_DHT
  loopDht();
#endif // ENABLE_DHT
}




