#ifndef ICAVE_SD_CARD_H
#define ICAVE_SD_CARD_H
  // include the SD library:
  #include <SD.h>
  
  // set up variables using the SD utility library functions:
  Sd2Card card;
  SdVolume volume;
  SdFile root;
  
  boolean sdInited = false;
  
  // change this to match your SD shield or module;
  // Arduino Ethernet shield: pin 4
  // Adafruit SD shields and modules: pin 10
  // Sparkfun SD shield: pin 8
  // Teensy 2.0: pin 0
  // Teensy++ 2.0: pin 20
  const int chipSelect = 10;   
#endif // ICAVE_GPS_H

