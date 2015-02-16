#if ENABLE_WIFI

#include "wifi.h"

// Use hardware SPI for the remaining pins
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ,  ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIVIDER);

void setupWifi() {
  Serial.println(F("Initializing CC3000 ..."));
  if (!cc3000.begin(false))
  {
    Serial.println(F("Unable to initialise the CC3000! Check your wiring?"));
    // while(1);
  } 
  else {
    Serial.println(F("CC3000 initialized!"));
  }
}

#endif // ENABLE_WIFI

