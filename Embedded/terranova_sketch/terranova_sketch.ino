#include "DriveMotor.hpp"

DriveMotor m1(31, 30, 2, 0, A14, 28, 29, 48 * 99);


void setup() {
  // put your setup code here, to run once:
  m1.init();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(m1.readFaultStatus());
  delay(2000);
}
