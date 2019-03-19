#pragma once

#include <Arduino.h>

class Encoder {
  public:
    Encoder(uint8_t PINA,
            uint8_t PINB,
            uint16_t ticksPerRot);
    Encoder(uint8_t PIN,
            uint16_t ticksPerRot);
    void init();
    float read_speed();

  private:
    uint8_t _PINA;
    uint8_t _PINB;
    uint16_t _ticksPerRot;
    unsigned long _prevTime;
    volatile uint8_t _tickCount;
    volatile unsigned long _rotTime;
    volatile bool _dirPrimed;
    volatile bool _dir;

    void pinA_ISR();
    void pinB_ISR();
}