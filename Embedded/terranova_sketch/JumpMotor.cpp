#include "JumpMotor.hpp"

JumpMotor::JumpMotor(uint8_t PWM, uint8_t DIR, uint8_t SLP, uint8_t FLT, uint8_t CS, uint8_t HAL, uint8_t ENC, uint16_t ticks_per_rot) {
  _PWM = PWM;
  _DIR = DIR;
  _SLP = SLP;
  _FLT = FLT;
  _CS = CS;
  _HAL = HAL;
  encoder = new Encoder(ENC, ticks_per_rot);
}

void JumpMotor::init() {
  pinMode(_PWM, OUTPUT);
  pinMode(_DIR, OUTPUT);
  pinMode(_SLP, OUTPUT);
  pinMode(_FLT, INPUT_PULLUP);
  pinMode(_CS, INPUT);
  pinMode(_HAL, INPUT);
  
  analogWriteResolution(12);
  analogReadResolution(13);

  attachArgInterrupt(_FLT, CHANGE);
  encoder->init();
}

void JumpMotor::setSpeed(uint8_t speed) {
  speed = speed > 100 ? 100 : speed;
  speed = speed < -100 ? -100 : speed;
  
  analogWrite(_PWM, (4096 * abs(speed)) / 100);

  if(speed == 0)
    digitalWrite(_SLP, LOW);
  else if(speed > 0) {
    digitalWrite(_SLP, HIGH);
    digitalWrite(_DIR, HIGH);
  }
  else {
    digitalWrite(_SLP, HIGH);
    digitalWrite(_DIR, LOW);
  }
}

float JumpMotor::readCurrent() {
  //return ((analogRead(_CS) * 3300000) / 8191) / 90.0f;
  return (((float)analogRead(_CS) / 8191.0f) * 36.7f) - 18.3f;
}

float JumpMotor::readRotationalSpeed() {
  return encoder->readSpeed();
}

bool JumpMotor::hallSensorTriggered() {
  return analogRead(_HAL) > 4000;
}

bool JumpMotor::readFaultStatus() {
  bool lastF = fault;
  fault = !digitalRead(_FLT);
  checked = true;
  return lastF;
}


void JumpMotor::pinChanged(uint8_t pin) {
  fault = !(digitalRead(_FLT) && checked);
  checked = false;
}
