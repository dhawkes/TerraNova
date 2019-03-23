#include "Encoder.hpp"

Encoder::Encoder(uint8_t PINA, uint8_t PINB, uint16_t ticks_per_rot) {
  _PINA = PINA;
  _PINB = PINB;
  _ticks_per_rot = ticks_per_rot;
}

Encoder::Encoder(uint8_t PIN, uint16_t ticks_per_rot) {
  _PINA = PIN;
  _PINB = 255;
  _ticks_per_rot = ticks_per_rot;
}

void Encoder::init() {
  pinMode(_PINA, INPUT_PULLUP);
  pinMode(_PINB, INPUT_PULLUP);
  attachArgInterrupt(_PINA, CHANGE);
  if(_PINB < 255)
    attachArgInterrupt(_PINB, CHANGE);
  _prev_time = micros();
  //_rot_time = 0;
}

float Encoder::readSpeed() {
  float speed = (float)(1.0f / (((float)_rot_time) / 1000000.0f / 60.0f));
  //float speed = _rot_time;
  if(_PINB < 255 && _dir)
    return -speed;
  return speed;
}


void Encoder::pinChanged(uint8_t pin) {
  _tick_count++;

  if(_dir_primed) {
    _dir_primed = false;
    _dir = pin == _PINA;
  }
  if(_PINB < 255 && digitalRead(_PINA) == LOW && digitalRead(_PINB) == LOW) {
    _dir_primed = true;
  }

  if(_tick_count >= _ticks_per_rot) {
    _tick_count = 0;
    unsigned long t = micros();
    _rot_time = t - _prev_time;
    _prev_time = t;
  }
}
