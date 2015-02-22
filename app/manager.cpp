#include "WProgram.h"

#include "general.h"
#include "manager.h"
#include "module.h"

using namespace iCave;

unsigned long last_tick = millis();
float last_tick_diff = 0;
float fps = 0;

void Manager::setup() {
  // Print info about enabled components
  #if PRINT_ENABLED_MODULES
    printInfo();
  #endif // PRINT_ENABLED_MODULES
  
  for(std::vector<Module*>::iterator i = mModules.begin(); i != mModules.end(); i++) {
    Module* m = (*i);
    if(Serial) {
      Serial.print("Manager::setup() - ");
      Serial.println(m->name());
    }
    m->setup();
  }
}

unsigned int tickNo = 0;

void Manager::loop() {
  const int tick_start = millis();
  
  // Serial.print("Manager::loop() - tick #");
  // Serial.println(tickNo);
  
  if(SENSOR_UPDATE_TICKS == 0 || (tickNo % SENSOR_UPDATE_TICKS) == 0) {
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
  
  tickNo++;
}

void Manager::printInfo() {
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

