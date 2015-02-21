#ifndef ICAVE_WIFI_H
#define ICAVE_WIFI_H
  #include "module.h"
  
  #include <Adafruit_CC3000.h>
  #include <Adafruit_CC3000_Server.h>
  #include <ccspi.h>
  
  // These are the interrupt and control pins
  #define ADAFRUIT_CC3000_IRQ   3  // MUST be an interrupt pin!
  // These can be any two pins
  #define ADAFRUIT_CC3000_VBAT  5
  #define ADAFRUIT_CC3000_CS    10
  
  #define DEVICE_NAME "CC3000"
  
  extern Adafruit_CC3000 cc3000; 
  
  namespace iCave {
    class WifiModule : public Module {
    public:
      WifiModule(Manager* manager) : Module(manager) {} 
      
      void setup();
    }; // WifiModule
  }; // namespace iCave
#endif // ICAVE_WIFI_H
