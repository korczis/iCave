#include "dht.h"

using namespace iCave;

DHT dht(DHTPIN, DHTTYPE, 20);

float dhtHumidity = 0;
float dhtTemperature = 0;
float dhtHeatIndex = 0;

void DhtModule::setup() {
    dht.begin();
}

void DhtModule::loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  dhtHumidity = dht.readHumidity();
  
  // Read temperature as Celsius
  dhtTemperature = dht.readTemperature();
  
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(dhtHumidity)) {
    dhtHumidity = 0;
  }

  if (isnan(dhtTemperature)) {
    dhtTemperature = 0;
  }
  
  dhtHeatIndex = (dht.computeHeatIndex(f, dhtHumidity) - 32) * (5.0f / 9.0f);
}
