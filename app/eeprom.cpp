#include "eeprom.h"

PersistentInfo persistenceInfo;

void readPersistentInfo() {
  for(unsigned int i = 0; i < sizeof(PersistentInfo); i++) {
    ((unsigned char*)&persistenceInfo)[i] = EEPROM.read(i);
  }
}

void writePersistentInfo() {
  for(unsigned int i = 0; i < sizeof(PersistentInfo); i++) {
    EEPROM.write(i, ((unsigned char*)&persistenceInfo)[i]);
  }
}

void clearEeprom() {
  for(unsigned short i = 0; i < getEepromSize(); i++) {
    EEPROM.write(i, 0);
  }
}

void setupEeprom() {
  // clearEeprom();
  
  readPersistentInfo();
  
  persistenceInfo.bootNo++;
  
  writePersistentInfo();
}
