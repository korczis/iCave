#ifndef ICAVE_WIFI_H
#define ICAVE_WIFI_H
  #include "SPI.h"

  // These are the interrupt and control pins
  #define ADAFRUIT_CC3000_IRQ   3  // MUST be an interrupt pin!
  // These can be any two pins
  #define ADAFRUIT_CC3000_VBAT  5
  #define ADAFRUIT_CC3000_CS    10
  
  #define DEVICE_NAME "CC3000"
  
  extern Adafruit_CC3000 cc3000; 
  
  void setupWifi();
#endif // ICAVE_WIFI_H
