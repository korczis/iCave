#include "general.h"

unsigned int getTotalRam() {
  return 64 * 1024;
}

unsigned int getVersionMajor() {
    return ICAVE_VERSION_MAJOR;
}

unsigned int getVersionMinor() {
  return ICAVE_VERSION_MINOR;
}

unsigned int getVersionPatch() {
  return ICAVE_VERSION_PATCH;
}
