#ifndef ICAVE_IO_PIN_H
#define ICAVE_IO_PIN_H

/**
 * Default IO Pin
 */
class IoPin {
public:
  typedef unsigned char T_ID;
  static const T_ID DEFAULT_ID = (T_ID)(0);
  
  /**
   * Basic IoPin constructor
   *
   * @param id Pin ID
   * @param value Initial Pin value
   */
  IoPin(const T_ID id = DEFAULT_ID) : mId(id) {
  };
  
  /**
   * Get pin ID
   */
  const T_ID& getId() const {
    return mId;
  };
  
  /**
   * Switch pin to input mode
   */
  IoPin& setInput() {
    pinMode(this->getId(), INPUT);
    return *this;
  }
  
  /**
   * Switch pin to output mode
   */
  IoPin& setOutput() {
    pinMode(this->getId(), OUTPUT);
    return *this;
  }
  
  const T_ID mId;
};

#endif // ICAVE_IO_PIN_H

