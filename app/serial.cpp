#include "serial.h"

#include "SPI.h"

HardwareSerial Uart = HardwareSerial();

void setupSerial() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Uart.begin(9600);
  
  // wait for serial port to connect. Needed for Leonardo only
  // while (!Serial) {
  //    ;
  // }
}