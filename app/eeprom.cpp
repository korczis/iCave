#include "./eeprom.h"

using namespace iCave;

EepromModule::PersistentInfo persistenceInfo;

void EepromModule::readPersistentInfo() {
  for(unsigned int i = 0; i < sizeof(PersistentInfo); i++) {
    ((unsigned char*)&persistenceInfo)[i] = EEPROM.read(i);
  }
}

void EepromModule::writePersistentInfo() {
  for(unsigned int i = 0; i < sizeof(PersistentInfo); i++) {
    EEPROM.write(i, ((unsigned char*)&persistenceInfo)[i]);
  }
}

void EepromModule::clearEeprom() {
  for(unsigned short i = 0; i < getEepromSize(); i++) {
    EEPROM.write(i, 0);
  }
}

void EepromModule::setup() {
  // clearEeprom();
  
  readPersistentInfo();
  
  persistenceInfo.bootNo++;
  
  writePersistentInfo();
}
