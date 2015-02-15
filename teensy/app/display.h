#ifndef ICAVE_DISPLAY_H
#define ICAVE_DISPLAY_H

  #include "SPI.h"
  #include "Adafruit_GFX.h"
  // #include "Adafruit_ILI9340.h"
  #include "TFT_ILI9340.h"
  
  // Color definitions
  #define	ILI9340_BLACK   0x0000
  #define	ILI9340_BLUE    0x001F
  #define	ILI9340_RED     0xF800
  #define	ILI9340_GREEN   0x07E0
  #define ILI9340_CYAN    0x07FF
  #define ILI9340_MAGENTA 0xF81F
  #define ILI9340_YELLOW  0xFFE0  
  #define ILI9340_WHITE   0xFFFF

  unsigned long testFillScreen();
  
  unsigned long testText();
  
  unsigned long testLines(uint16_t color);
  
  unsigned long testFastLines(uint16_t color1, uint16_t color2);
  
  unsigned long testRects(uint16_t color);
  
  unsigned long testFilledRects(uint16_t color1, uint16_t color2);
  
  unsigned long testFilledCircles(uint8_t radius, uint16_t color);
  
  unsigned long testCircles(uint8_t radius, uint16_t color);
  
  unsigned long testTriangles();
  
  unsigned long testFilledTriangles();
  
  unsigned long testRoundRects();
  
  unsigned long testFilledRoundRects();
  
  void testDisplay();

#endif // ICAVE_DISPLAY_H
