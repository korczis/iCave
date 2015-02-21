#ifndef ICAVE_EEPROM_H
#define ICAVE_EEPROM_H
  #include "module.h"
  #include "general.h"
  
  #include <EEPROM.h>  
  
  namespace iCave {
    class EepromModule : public Module {
    public:
      EepromModule(Manager* manager) : Module(manager) {} 
     
      typedef struct PersistentInfo {
        unsigned char versionMajor;
        unsigned char versionMinor;
        unsigned char versionPatch;
        unsigned int bootNo;
      };

      inline unsigned short getEepromSize() {
        return 2048;
      }

      void clearEeprom();
       /* virtual */ void setup(/* int wait_for_serial = false */);
      
      void readPersistentInfo();
      void writePersistentInfo();

    }; // class EepromModule
  }; // namespace iCave
  
  extern iCave::EepromModule::PersistentInfo persistenceInfo;

#endif // ICAVE_EEPROM_H

