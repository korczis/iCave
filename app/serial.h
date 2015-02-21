#ifndef ICAVE_SERIAL_H
#define ICAVE_SERIAL_H
  #include "module.h"
  
  namespace iCave {
    class SerialModule : public Module {
    public:
      SerialModule(Manager* manager) : Module(manager) {} 
      /* virtual */ void setup(/* int wait_for_serial = false */);
    }; // class SerialModule
  }; // namespace iCave
#endif // ICAVE_SERIAL_H
