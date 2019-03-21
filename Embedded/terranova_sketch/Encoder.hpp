#pragma once

#include <Arduino.h>
#include "PinInterrupt.hpp"

class Encoder : public PinInterrupt {
  public:
    Encoder(uint8_t PINA, uint8_t PINB, uint16_t ticks_per_rot);
    Encoder(uint8_t PIN, uint16_t ticks_per_rot);
    void init();
    float readSpeed();
    
    void pinChanged(uint8_t pin);

  private:
    uint8_t _PINA;
    uint8_t _PINB;
    uint16_t _ticks_per_rot;
    unsigned long _prev_time;
    volatile uint8_t _tick_count;
    volatile unsigned long _rot_time;
    volatile bool _dir_primed;
    volatile bool _dir;
};
