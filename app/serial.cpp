#include "serial.h"
#include "SPI.h"

using namespace iCave;

HardwareSerial Uart = HardwareSerial();

void SerialModule::setup(/* int wait_for_serial */) {
  static const int wait_for_serial = false;
  
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Uart.begin(9600);
  
  // wait for serial port to connect. Needed for Leonardo only
  while (wait_for_serial && !Serial) {
    ;
  }
}
