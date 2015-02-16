#ifndef ICAVE_GENERAL_H
#define ICAVE_GENERAL_H
  #if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
  #endif
#endif // ICAVE_GENERAL_H
