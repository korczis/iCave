#include "WProgram.h"

#include "general.h"
#include "manager.h"
#include "module.h"

using namespace iCave;

#if JSON_SUPPORT
  #include <ArduinoJson.h>
#endif // JSON_SUPPORT

unsigned long last_tick = millis();
float last_tick_diff = 0;
float fps = 0;

void Manager::setup() {
  for(std::vector<Module*>::iterator i = mModules.begin(); i != mModules.end(); i++) {
    Module* m = (*i);
    if(Serial) {
      Serial.print("Manager::setup() - ");
      Serial.println(m->name());
    }
    m->setup();
  }
  
  // Print info about enabled components
  #if PRINT_ENABLED_MODULES
    printInfo();
  #endif // PRINT_ENABLED_MODULES
}

unsigned long tick_no = 0;

void Manager::loop() {
  const int tick_start = millis();
  
  // Serial.print("Manager::loop() - tick #");
  // Serial.println(tickNo);
  
  if(SENSOR_UPDATE_TICKS == 0 || (tick_no % SENSOR_UPDATE_TICKS) == 0) {
    for(std::vector<Module*>::iterator i = mModules.begin(); i != mModules.end(); i++) {
      (*i)->loop();
    }
  }
  
  const int loop_tick_time = millis() - tick_start;
  
  // Serial.print("Manager::loop() - tick time (ms) ");
  // Serial.println(loop_tick_time);
    
  if(LOOP_TYPE == LT_FIXED_SLEEP) {
    // Sleep for some time, if needed
    delay(LOOP_INTERVAL);
  } // LT_FIXED_SLEEP

  
  if(LOOP_TYPE == LT_FIXED_FPS) {
    static const int LOOP_SLEEP_TIME = ((1.0f / LOOP_FPS) * 1000);
    const int sleep_time = (LOOP_SLEEP_TIME - loop_tick_time);
    if(sleep_time > 0) {
      delay(sleep_time >= 0 ? sleep_time : 1);
    }
  } // LT_FIXED_FPS
  
  unsigned long ms = millis();
  last_tick_diff = (ms - tick_start) * 0.001f;
  fps = 1.0f / last_tick_diff;
  last_tick = tick_start;
  
  #if JSON_STATS && JSON_SUPPORT
    StaticJsonBuffer<2048> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    
    root["loop_type"] = LOOP_TYPE;
    root["tick_no"] = tick_no;
    root["tick_start"] = tick_start;
    root["loop_tick_time"] = loop_tick_time * 0.001;
    root["last_tick_diff"] = last_tick_diff;
    root["fps"] = fps;
    
    root.prettyPrintTo(Serial);
    
    if(Serial) {
      Serial.println();
    }
  #endif // JSON_SUPPORT
  
  tick_no++;
}

void Manager::printInfo() {
  if(Serial) {
    Serial.print("ENABLE_DHT = ");
    Serial.println(ENABLE_DHT);
    
    Serial.print("ENABLE_DISPLAY = ");
    Serial.println(ENABLE_DISPLAY);
    
    Serial.print("ENABLE_GPS = ");
    Serial.println(ENABLE_GPS);
    
    Serial.print("ENABLE_SD_CARD = ");
    Serial.println(ENABLE_SD_CARD);

    Serial.print("ENABLE_TSL_2561 = ");
    Serial.println(ENABLE_TSL_2561);
    
    Serial.print("ENABLE_WIFI = ");
    Serial.println(ENABLE_WIFI);
  }
}

