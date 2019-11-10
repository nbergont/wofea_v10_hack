#include <Arduino.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  delay(200); //Boot delay
  pinMode(LED_BUILTIN, OUTPUT);
  mySwitch.enableTransmit(2); //Pin 2
  mySwitch.setPulseLength(433);
  mySwitch.setRepeatTransmit(3);
}

void loop() {
  mySwitch.send("101001001001110110101011");
  digitalWrite(LED_BUILTIN, 1);
  delay(50);
  digitalWrite(LED_BUILTIN, 0);
  delay(15000); //Send ping every 15s 
}
