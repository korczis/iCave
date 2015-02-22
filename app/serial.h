#ifndef ICAVE_SERIAL_H
#define ICAVE_SERIAL_H
  #include "module.h"
  
  namespace iCave {
    class SerialModule : public Module {
    public:
      SerialModule(Manager* manager) : Module(manager) {} 
      
      /* virtual */ const char* name() const { 
        return "serial";
      }
      
      /* virtual */ void setup();
    }; // class SerialModule
  }; // namespace iCave
#endif // ICAVE_SERIAL_H
