#include "DriveMotor.hpp"

DriveMotor::DriveMotor(uint8_t INA, uint8_t INB, uint8_t PWM, uint8_t EN, uint8_t CS, uint8_t ENCA, uint8_t ENCB, uint16_t ticks_per_rot) {
  _INA = INA;
  _INB = INB;
  _PWM = PWM;
  _EN = EN;
  _CS = CS;
  encoder = new Encoder(ENCA, ENCB, ticks_per_rot);
}

void DriveMotor::init() {
  pinMode(_INA, OUTPUT);
  pinMode(_INB, OUTPUT);
  pinMode(_PWM, OUTPUT);
  pinMode(_EN, INPUT);
  pinMode(_CS, INPUT);

  analogWriteFrequency(_PWM, 20000);
  analogWriteResolution(12);
  analogReadResolution(13);

  attachArgInterrupt(_EN, CHANGE);
  encoder->init();
}

void DriveMotor::setSpeed(int8_t speed) {
  bool reverse = false;
  if(speed < 0) {
    speed = -speed;
    reverse = true;
  }
  speed = speed > 100 ? 100 : speed;

  analogWrite(_PWM, (4096 * speed) / 100);

  if(speed == 0) {
    digitalWrite(_INA, LOW);
    digitalWrite(_INB, LOW);
  }
  else if(reverse) {
    digitalWrite(_INA, LOW);
    digitalWrite(_INB, HIGH);
  }
  else {
    digitalWrite(_INA, HIGH);
    digitalWrite(_INB, LOW);
  }
}

void DriveMotor::setBrake(uint8_t brake) {
  brake = brake > 100 ? 100 : brake;

  digitalWrite(_INA, LOW);
  digitalWrite(_INB, LOW);

  analogWrite(_PWM, (4096 * brake) / 100);
}

float DriveMotor::readCurrent() {
  return ((analogRead(_CS) * 3300000) / 8191) / 140.0f;
}

float DriveMotor::readRotationalSpeed() {
  return encoder->readSpeed();
}

bool DriveMotor::readFaultStatus() {
  bool lastF = fault;
  fault = !digitalRead(_EN);
  checked = true;
  return lastF;
}


void DriveMotor::pinChanged(uint8_t pin) {
  fault = !(digitalRead(_EN) && checked);
  checked = false;
}
