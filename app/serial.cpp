#include "serial.h"
#include "SPI.h"
#include "general.h"

using namespace iCave;

HardwareSerial Uart = HardwareSerial();

void SerialModule::setup() {
  static const bool wait_for_serial = SERIAL_WAIT;
  
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Uart.begin(9600);
  
  // wait for serial port to connect. Needed for Leonardo only
  while (wait_for_serial && !Serial) {
    ;
  }
}
