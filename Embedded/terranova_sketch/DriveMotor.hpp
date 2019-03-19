#pragma once

#include <Arduino.h>
#include "Encoder.hpp"

class DriveMotor
{
  public:
    DriveMotor(uint8_t INA,
               uint8_t INB,
               uint8_t PWM,
               uint8_t EN,
               uint8_t CS,
               uint8_t ENCA,
               uint8_t ENCB);

    void init();
    void setSpeed(int speed);
    void setBrake(int brake);
    float readCurrent();
    float readRotationalSpeed();

  private:
    uint8_t _INA;
    uint8_t _INB;
    uint8_t _PWM;
    uint8_t _EN;
    uint8_t _CS;
    uint8_t _ENCA;
    uint8_t _ENCB;
};
