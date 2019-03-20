#pragma once

class PinInterrupt {
public:
  virtual void pinChanged(uint8_t pin) = 0;

protected:
  bool attachArgInterrupt(uint8_t pin, uint8_t mode) {
    intArg[pin] = this;
    switch(pin) {
      case 0:
        attachInterrupt(0, isr0, mode);
        break;
      case 1:
        attachInterrupt(1, isr1, mode);
        break;
      case 2:
        attachInterrupt(2, isr2, mode);
        break;
      case 3:
        attachInterrupt(3, isr3, mode);
        break;
      default:
        return false;
    }
    return true;
  }
  
private:
  static PinInterrupt* intArg[58];

  static void isr0() {
    intArg[0]->pinChanged(0);
  }
  static void isr1() {
    intArg[1]->pinChanged(1);
  }
  static void isr2() {
    intArg[2]->pinChanged(2);
  }
  static void isr3() {
    intArg[3]->pinChanged(3);
  }
};
