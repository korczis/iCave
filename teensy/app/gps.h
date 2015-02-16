#ifndef ICAVE_GPS_H
#define ICAVE_GPS_H
  #include <Adafruit_GPS.h>

  extern Adafruit_GPS GPS;
  
  extern boolean usingInterrupt;
  
  // Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
  // Set to 'true' if you want to debug and listen to the raw GPS sentences
  #define GPSECHO  (true)
  
  void setupGps();
  
  void updateDisplay();
  
  void loopGps();
#endif // ICAVE_GPS_H

