#include "JumpMotor.hpp"

JumpMotor j(30, 34, A14, A0, 0, 2 * 175);

void setup() {
  // put your setup code here, to run once:
  j.init();
  Serial.begin(9600);
  j.setSpeed(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(j.readRotationalSpeed());
  delay(100);
}
