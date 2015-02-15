#ifndef ICAVE_ENGINE_H
#define ICAVE_ENGINE_H

#include <vector>

#include "./IoPin.h"
#include "./PwmPin.h"
#include "./LedPin.h"

class Engine {
public:
  Engine(std::vector<LedPin>& pins) :  mPins(pins) {
  };

  Engine& loop() {
    for(unsigned int i = 0; i < pinsCount(); i++) {
      mPins[i].update();
    } 

    delay(DEFAULT_SLEEP);

    return *this;
  };

  const size_t pinsCount() const {
    const size_t res = mPins.size();
    Serial.println(res);
    return res;
  };

  Engine& setup() {
    return *this;
  };

private:
  std::vector<LedPin>& mPins;
};

#endif // ICAVE_ENGINE_H


