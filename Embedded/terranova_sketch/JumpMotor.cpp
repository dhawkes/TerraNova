#include "JumpMotor.hpp"

JumpMotor::JumpMotor(uint8_t PWM, uint8_t FAULT, uint8_t CS, uint8_t HALL, uint8_t ENC, uint16_t ticks_per_rot) {
  _PWM = PWM;
  _CS = CS;
  _FAULT = FAULT;
  _HALL = HALL;
  encoder = new Encoder(ENC, ticks_per_rot);
}

void JumpMotor::init() {
  pinMode(_PWM, OUTPUT);
  pinMode(_CS, INPUT);
  pinMode(_HALL, INPUT);

  //analogWriteFrequency(_PWM, 200);
  analogWriteResolution(12);
  analogReadResolution(13);

  attachArgInterrupt(_FAULT, CHANGE);
  encoder->init();
}

void JumpMotor::setSpeed(uint8_t speed) {
  speed = speed > 100 ? 100 : speed;
  analogWrite(_PWM, (4096 * speed) / 100);
}

float JumpMotor::readCurrent() {
  //return ((analogRead(_CS) * 3300000) / 8191) / 90.0f;
  return (((float)analogRead(_CS) / 8191.0f) * 36.7f) - 18.3f;
}

float JumpMotor::readRotationalSpeed() {
  return encoder->readSpeed();
}

bool JumpMotor::hallSensorTriggered() {
  return analogRead(_HALL) > 4000;
}

bool JumpMotor::readFaultStatus() {
  bool lastF = fault;
  fault = !digitalRead(_FAULT);
  checked = true;
  return lastF;
}


void JumpMotor::pinChanged(uint8_t pin) {
  fault = !(digitalRead(_FAULT) && checked);
  checked = false;
}
