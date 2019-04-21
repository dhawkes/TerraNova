#pragma once

#include <Arduino.h>
#include "Constants.hpp"

enum Button {
  A = 0,
  B,
  X,
  Y,
  LT,
  RT,
  DUP,
  DDOWN,
  DLEFT,
  DRIGHT,
  LB,
  RB
};

enum ButtonState {
  DOWN = 0,
  UP,
  PRESSED,
  RELEASED,
  CHANGED
};

class WirelessCommunication {
  public:
    WirelessCommunication(HardwareSerial* serial);
    void init();
    void setDataValue(uint16_t id, float value);
    float getDataValue(uint16_t id);
    void setFaultValue(uint16_t id, bool value);
    void sendMessages();
    bool receiveMessages(uint8_t* msg);
    bool buttonState(Button btn, ButtonState state);

    uint8_t escapeMessage(uint8_t *data, uint8_t len);

  private:
    HardwareSerial* _serial;
    float _data[MAX_DATA_LENGTH];
    bool _faults[MAX_FAULT_LENGTH];

    bool _c_btns[12];
    bool _p_btns[12];

    
    void updateButtons(uint8_t btn1, uint8_t btn2);
    uint16_t fletcher16(uint8_t* data, size_t len);
};
