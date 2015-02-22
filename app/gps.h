#ifndef ICAVE_GPS_H
#define ICAVE_GPS_H
  #include "module.h"
  
  #include <Adafruit_GPS.h>
  
  extern Adafruit_GPS GPS;
  
  extern boolean usingInterrupt;
  
  // Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
  // Set to 'true' if you want to debug and listen to the raw GPS sentences
  #define GPSECHO  (false)

  #define GPS_BAUDRATE (9600)
  
  namespace iCave {
    class GpsModule : public Module {
    public:
      GpsModule(Manager* manager) : Module(manager) {} 
      /* virtual */ void setup(/* int wait_for_serial = false */);
      
      /* virtual */ const char* name() const {
        return "gps";
      };
      
      void updateDisplay();
  
      /* virtual */ void loop();
    }; // class GpsModule
  }; // namespace iCave
#endif // ICAVE_GPS_H

