#include "dht.h"

DHT dht(DHTPIN, DHTTYPE, 25);

float dhtHumidity = 0;
float dhtTemperature = 0;
float dhtHeatIndex = 0;

void setupDht() {
    dht.begin();
}

void loopDht() {
  // Reading temperature or humidity takes about 250 milliseconds!
  
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float dhtHumidity = dht.readHumidity();
  
  // Read temperature as Celsius
  float dhtTemperature = dht.readTemperature();
  
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(dhtHumidity)) {
    dhtHumidity = 0;
  }

  if (isnan(dhtTemperature)) {
    dhtTemperature = 0;
  }
  
  float dhtHeatIndex = dht.computeHeatIndex(f, dhtHumidity);
}
