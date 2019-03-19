#include "Encoder.h"

Encoder::Encoder(uint8_t PINA, uint8_t PINB, uint16_t ticksPerRot) {
  _PINA = PINA;
  _PINB = PINB;
  _ticksPerRot = ticksPerRot;
}

Encoder::Encorder(uint8_t PIN, uint16_t ticksPerRot) {
  _PINA = PIN;
  _ticksPerRot = ticksPerRot;
}

Encoder::init() {
  pinMode(PINA, INPUT_PULLUP);
  pinMode(PINB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(_PINA), pinA_ISR, CHANGE);
  if(_PINB > 0)
    attachInterrupt(digitalPinToInterrupt(_PINB), pinB_ISR, CHANGE);
  _prevTime = micros();
}

float Encoder::read_speed() {
  if(micros() - prevTime > 1000000)
    return 0;
  float speed = 1.0f / _rotTime / 1000000.0f / 60.0f;
  if(PINB > 0 && _dir)
    return -speed;
  return speed;
}

Encoder::pinA_ISR() {
  _tickCount++;

  if(_dirPrimed) {
    _dirPrimed = false;
    _dir = true;
  }
  if(_PINB > 0 && digitalRead(_PINA) == LOW && digitalRead(_PINB) == LOW) {
    _dirPrimed = true;
  }

  if(_tickCount >= _ticksPerRot) {
    _tickCount = 0;
    unsigned long t = micros();
    _rotTime = t - _prevTime;
    _prevTime = t;
  }
}

Encoder::pinB_ISR() {
  _tickCount++;

  if(_dirPrimed) {
    _dirPrimed = false;
    _dir = false;
  }
  if(_PINB > 0 && digitalRead(_PINA) == LOW && digitalRead(_PINB) == LOW) {
    _dirPrimed = true;
  }

  if(_tickCount >= _ticksPerRot) {
    _tickCount = 0;
    unsigned long t = micros();
    _rotTime = t - _prevTime;
    _prevTime = t;
  }
}
