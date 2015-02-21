#ifndef ICAVE_SNOOZE_H
#define ICAVE_SNOOZE_H
  #include "module.h"
  
  #include <LowPower_Teensy3.h>
  
  extern TEENSY3_LP LP;
  
  void callbackhandler();
  
  void setupSleepMode();
  
  namespace iCave {
    class SnoozeModule : public Module {
    public:
      SnoozeModule(Manager* manager) : Module(manager) {} 
      
      /* virtual */ void setup();
      /* virtual */ void loop();
    }; // SnoozeModule    
  }; // namespace iCave

#endif // ICAVE_SNOOZE_H

