#ifndef ICAVE_RFID_H
#define ICAVE_RFID_H
  #include "module.h"
  
  #include <MFRC522.h>
  
  namespace iCave {
    class RfidModule : public Module {
    public:
      RfidModule(Manager* manager) : Module(manager) {} 
      
      /* virtual */ const char* name() const { 
        return "rfid";
      }
      
    }; // RfidModule
  }; // namespace iCave
#endif // ICAVE_RFID_H

