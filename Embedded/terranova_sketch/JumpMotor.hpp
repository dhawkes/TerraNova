#pragma once

#include <Arduino.h>
#include "Encoder.hpp"

class JumpMotor : public PinInterrupt {
  public:
    JumpMotor(uint8_t PWM, uint8_t FAULT, uint8_t CS, uint8_t HALL, uint8_t ENC, uint16_t ticks_per_rot);

    void init();
    void setSpeed(uint8_t speed);
    float readCurrent();
    float readRotationalSpeed();
    bool hallSensorTriggered();
    bool readFaultStatus();

    void pinChanged(uint8_t pin);

  private:
    Encoder* encoder;
    uint8_t _PWM;
    uint8_t _FAULT;
    uint8_t _CS;
    uint8_t _HALL;
    volatile bool fault;
    volatile bool checked;
};
