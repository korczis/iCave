#include "core.h"
#include "general.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <stdio.h>

using namespace iCave;

void CoreModule::setup() {
  // Print banner
  char buff[128];
  sprintf(buff, "iCave %d.%d.%d", getVersionMajor(), getVersionMinor(), getVersionPatch());
  Serial.println(buff);
}

