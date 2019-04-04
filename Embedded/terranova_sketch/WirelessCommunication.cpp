#include "WirelessCommunication.hpp"

WirelessCommunication::WirelessCommunication(HardwareSerial* serial) {
  _serial = serial;
}

void WirelessCommunication::init() {
  _serial->begin(115200);
  _serial->setTimeout(1);
}

void WirelessCommunication::setDataValue(uint16_t id, float value) {
  _data[id] = value;
}

void WirelessCommunication::setFaultValue(uint16_t id, bool value) {
  _faults[id] = value;
}

void WirelessCommunication::sendMessages() {
  uint8_t f1 = 0, f2 = 0;
  for(int i = 0; i < MAX_FAULT_LENGTH; i++) {
    if(i < 8) {
      if(_faults[i])
        f1 |= 1 << i;
    }
    else {
      if(_faults[i])
        f2 |= 1 << i;
    }
  }

  uint8_t buff[100];
  uint8_t len;
  
  buff[0] = 0xFC;
  buff[1] = 0xFF;
  buff[2] = f1;
  buff[3] = f2;
  uint16_t checksum = fletcher16(&buff[1], 3);
  buff[4] = checksum >> 8;
  buff[5] = checksum & 0xFF;
  len = escapeMessage(&buff[1],5);
  buff[len+1] = 0xFD;
  _serial->write(buff, len+2);

  for(uint8_t i = 0; i < MAX_DATA_LENGTH; i++) {
    uint8_t* b = (uint8_t*)&_data[i];
    buff[0] = 0xFC;
    buff[1] = 0xDD;
    buff[2] = i;
    buff[3] = b[0];
    buff[4] = b[1];
    buff[5] = b[2];
    buff[6] = b[3];
    uint16_t checksum = fletcher16(&buff[1], 6);
    buff[7] = checksum >> 8;
    buff[8] = checksum & 0xFF;
    
    len = escapeMessage(&buff[1], 8);
    buff[len+1] = 0xFD;
    _serial->write(buff, len+2);
  }
}

uint8_t WirelessCommunication::escapeMessage(uint8_t *data, uint8_t len) {
  uint8_t buff[100];
  uint8_t k = 0;
  for(int i = 0; i < len; i++) {
    if(data[i] == 0xFA || data[i] == 0xFC || data[i] == 0xFD) {
      buff[k] = 0xFA;
      k++;
    }
    buff[k] = data[i];
    k++;
  }
  data = buff;
  return k;
}

bool WirelessCommunication::receiveMessages(uint8_t* msg) {
  if(_serial->available() < 8)
    return false;

  uint8_t buffer[64];
  int len = _serial->readBytes(buffer, 64);

  int start = -1;
  for(int i = len; i >= 0; i--) {
    if(buffer[i] == 0xFC) {
      start = i;
      break;
    }
  }

  if(start == -1 || len - start < 8) {
    Serial.println("SHORT");
    return false;
  }

  uint8_t *buffn = &buffer[start];
  if(buffn[7] != 0xFD) {
    return false;
  }

  uint16_t check = buffn[6] << 8 | buffn[5];
  if(check != fletcher16(buffn+1, 4)) {
    return false;    
  }

  for(int i = 1; i < 5; i++) {
    msg[i-1] = buffn[i];
  }

  updateButtons(msg[2], msg[3]);
  
  return true;
}

bool WirelessCommunication::buttonState(Button btn, ButtonState state) {
  switch(state) {
    case ButtonState::UP:
      return !_c_btns[btn];
    case ButtonState::DOWN:
      return _c_btns[btn];
    case ButtonState::PRESSED:
      return _c_btns[btn] && !_p_btns[btn];
    case ButtonState::RELEASED:
      return !_c_btns[btn] && _p_btns[btn];
    case ButtonState::CHANGED:
      return _c_btns[btn] != _p_btns[btn];
    default:
      return false;
  }
}

void WirelessCommunication::updateButtons(uint8_t btn1, uint8_t btn2) {
  for(int i = 0; i < 12; i++) {
    _p_btns[i] = _c_btns[i];
  }

  _c_btns[Button::A] = btn1 & 0b1;
  _c_btns[Button::B] = btn1 & 0b10;
  _c_btns[Button::X] = btn1 & 0b100 ;
  _c_btns[Button::Y] = btn1 & 0b1000 ;
  _c_btns[Button::RT] = btn1 & 0b10000;
  _c_btns[Button::LT] = btn1 & 0b100000;

  _c_btns[Button::DUP] = btn2 & 0b1;
  _c_btns[Button::DDOWN] = btn2 & 0b10;
  _c_btns[Button::DLEFT] = btn2 & 0b100;
  _c_btns[Button::DRIGHT] = btn2 & 0b1000;
  _c_btns[Button::RB] = btn2 & 0b10000;
  _c_btns[Button::LB] = btn2 & 0b100000;
}

uint16_t WirelessCommunication::fletcher16(uint8_t *data, size_t len)
{
  uint16_t sum1 = 0xff, sum2 = 0xff;

  while (len) {
    size_t tlen = len > 20 ? 20 : len;
    len -= tlen;
    do {
      sum2 += sum1 += *data++;
    } while (--tlen);
      sum1 = (sum1 & 0xff) + (sum1 >> 8);
      sum2 = (sum2 & 0xff) + (sum2 >> 8);
  }

  sum1 = (sum1 & 0xff) + (sum1 >> 8);
  sum2 = (sum2 & 0xff) + (sum2 >> 8);
  return sum2 << 8 | sum1;
}
