#ifndef ICAVE_TSL_2561_H
#define ICAVE_TSL_2561_H
  #include "module.h"
  
  #include "TSL2561.h"
  
  namespace iCave {
    
    class Tsl2561Module : public Module {
    public:
      Tsl2561Module(Manager* manager) : Module(manager) {} 
  
      void setup();
      void loop();
    }; // class Tsl2561Module
  }; // namespace iCave
  
  extern float lux;
#endif // ICAVE_TSL_2561_H
