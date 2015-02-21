#include "./snooze.h"

using namespace iCave;

TEENSY3_LP LP = TEENSY3_LP();

void callbackhandler() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
}
  
void SnoozeModule::setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(0, INPUT_PULLUP);
  attachInterrupt(0, callbackhandler, RISING);
}

void SnoozeModule::loop() {
  LP.Sleep();
}
