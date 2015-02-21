#include "./manager.h"
#include "module.h"

#include "general.h"

using namespace iCave;

void Manager::setup() {
  for(std::vector<Module*>::iterator i = mModules.begin(); i != mModules.end(); i++) {
    (*i)->setup();
  }
}

void Manager::loop() {
  for(std::vector<Module*>::iterator i = mModules.begin(); i != mModules.end(); i++) {
    (*i)->loop();
  }
}

