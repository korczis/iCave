#ifndef ICAVE_GENERAL_H
#define ICAVE_GENERAL_H
  #if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
  #endif
 
  #define ICAVE_VERSION_MAJOR (0)
  #define ICAVE_VERSION_MINOR (0)
  #define ICAVE_VERSION_PATCH (1)

  typedef enum E_LOOP_TYPE {
    LT_UNKNOWN = -1,
    LT_FIXED_SLEEP,
    LT_FIXED_FPS,
  
    // Last marker
    LT_LAST
  } 
  E_LOOP_TYPE;
  
  // Global configuration
  #define LOOP_TYPE (LT_FIXED_FPS)
  #define LOOP_INTERVAL (16)
  #define LOOP_FPS (1.0f)

  unsigned int getTotalRam();
  
  inline unsigned int getVersionMajor() {
    return ICAVE_VERSION_MAJOR;
  }
  
  inline unsigned int getVersionMinor() {
    return ICAVE_VERSION_MINOR;
  }
  
  inline unsigned int getVersionPatch() {
    return ICAVE_VERSION_PATCH;
  }
 
#endif // ICAVE_GENERAL_H
