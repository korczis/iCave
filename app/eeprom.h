#ifndef ICAVE_EEPROM_H
#define ICAVE_EEPROM_H

#include "general.h"

#include <EEPROM.h>

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
void setupEeprom();

void readPersistentInfo();
void writePersistentInfo();

extern PersistentInfo persistenceInfo;

#endif // ICAVE_EEPROM_H

