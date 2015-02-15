#ifndef ICAVE_LED_PIN_H
#define ICAVE_LED_PIN_H

#include "./PwmPin.h"

/**
 * LED output pin
 */
class LedPin : public PwmPin { 
public:
  static const int DEFAULT_INCREMENT = 1;

  LedPin(T_ID id = DEFAULT_ID, T_VALUE value = DEFAULT_VALUE) : PwmPin(id, value) {
    this->setOutput();
  }
  
  LedPin& update() {
    (*this) += DEFAULT_INCREMENT;
    this->analogWrite();
    return *this;
  };
};

#endif // ICAVE_LED_PIN_H

