#ifndef ICAVE_PWM_PIN_H
#define ICAVE_PWM_PIN_H

#include "./IoPin.h"

/**
 * PWM Pin
 */
class PwmPin : public IoPin {
public:
  typedef unsigned char T_VALUE;
  static const T_VALUE DEFAULT_VALUE = (T_VALUE)(0);
  
  /**
   * Default PwmPin constructor
   *
   * @param id Pin ID
   * @param value Initial Pin value
   */
  PwmPin(const T_ID id = DEFAULT_ID, const T_VALUE value = DEFAULT_VALUE) : IoPin(id), mValue(value) {
  }; 
  
  /**
   * Get PwmPin value
   */
  const T_VALUE& getValue() const {
    return mValue;
  };
  
  /**
   * Set PwmPin value
   */
  T_VALUE& setValue() {
    return mValue;
  };
  
  /**
   * Increment PwmPin value
   */
  PwmPin& operator+=(const T_VALUE& value) {
    mValue += value;
    return *this;
  }
  
  /**
   * Write PwmPin value to output (pin)
   */
  PwmPin& analogWrite() {
    ::analogWrite(this->getId(), this->getValue());
    return *this;
  }
  
private:
  
  /**
   * Current PwmPin value
   */
  T_VALUE mValue;
};

#endif // ICAVE_PWM_PIN_H

