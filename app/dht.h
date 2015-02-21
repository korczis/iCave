#ifndef ICAVE_DHT_H
#define ICAVE_DHT_H
  #include "module.h"
  
  #include <DHT.h>

  #define DHTPIN (2)     // what pin we're connected to

  // Uncomment whatever type you're using!
  //#define DHTTYPE DHT11   // DHT 11 
  #define DHTTYPE DHT22   // DHT 22  (AM2302)
  //#define DHTTYPE DHT21   // DHT 21 (AM2301)
  
  extern DHT dht;
  
  extern float dhtHumidity;
  extern float dhtTemperature;
  extern float dhtHeatIndex;

  namespace iCave {
    class DhtModule : public Module {
    public:
      DhtModule(Manager* manager) : Module(manager) {} 
      /* virtual */ void setup();
  
      /* virtual */ void loop();
    }; // class DhtModule
  }; // namespace iCave
#endif // ICAVE_DHT_H

