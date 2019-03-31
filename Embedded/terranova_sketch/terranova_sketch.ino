#include "WirelessCommunication.hpp"

WirelessCommunication wc(&Serial1);

void setup() {
  wc.init();
  wc.setDataValue(5,10.2f);
  wc.setDataValue(10, 11.0f);
  wc.setFaultValue(0, true);
}

void loop() {
  wc.sendMessages();
  delay(5000);
}
