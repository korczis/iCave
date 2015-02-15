/* RGB Analog Example, Teensyduino Tutorial #2
   http://www.pjrc.com/teensy/tutorial2.html

   This example code is in the public domain.
*/

#include <vector>

static const unsigned char DEFAULT_SLEEP = 10;

#include "./LedPin.h"
#include "./Engine.h"

/**
 * Specific Pins with its initial values
 */ 
std::vector<LedPin> pins = {
  LedPin(3, 0),
  LedPin(4, 80),
  LedPin(5, 160)
};

Engine engine(pins);

/**
 * Initial setup func
 */
void setup() {
  engine.setup();
}

/**
 * Tick loop
 */
void loop()                     
{ 
  engine.loop();
}

