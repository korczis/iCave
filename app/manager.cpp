#include "WProgram.h"

#include "general.h"
#include "manager.h"
#include "module.h"

using namespace iCave;

unsigned long last_tick = millis();
float last_tick_diff = 0;
float fps = 0;

void Manager::setup() {
  for(std::vector<Module*>::iterator i = mModules.begin(); i != mModules.end(); i++) {
    (*i)->setup();
  }
}

void Manager::loop() {
  const int tick_start = millis();
  
  for(std::vector<Module*>::iterator i = mModules.begin(); i != mModules.end(); i++) {
    (*i)->loop();
  }
  
  const int loop_tick_time = millis() - tick_start;
    
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
}

