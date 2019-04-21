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

  analogWriteFrequency(_PWM, 1000);
  analogWriteResolution(12);
  analogReadResolution(13);

  attachArgInterrupt(_EN, CHANGE);
  encoder->init();

  _current_speed = 100;
  _desired_speed = 100;
}

void DriveMotor::setSpeed(uint8_t speed) {
  _desired_speed = speed > 200 ? 200 : speed;
}

void DriveMotor::updateSpeed(float supply_voltage) {
  int spd = _current_speed - 100;
  
  if(_desired_speed != _current_speed) {
    int nom_acc = 2;
    int acc = nom_acc; //abs(_desired_speed - _current_speed) <= nom_acc * 2 ? nom_acc / 10 : nom_acc;
    
    
    if(_desired_speed > _current_speed)
      _current_speed += acc;
    else
      _current_speed -= acc;
  }
    
  int max_ticks = 4096; //1200;
  
  analogWrite(_PWM, (max_ticks * abs(spd)) / 100);

  if(spd < 10 && spd > -10) {
    digitalWrite(_INA, LOW);
    digitalWrite(_INB, LOW);
  }
  else if(spd < -10) {
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
