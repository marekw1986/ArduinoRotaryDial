#include "RotaryDial.h"

RotaryDial tarcza(1, 2);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  int number;
  // put your main code here, to run repeatedly:
  if (tarcza.update()) {
    number = tarcza.getNextNumber();
    Serial.print(F("Dialed number: "));
    Serial.print(number);
    Serial.print("\r\n");
  }
}
