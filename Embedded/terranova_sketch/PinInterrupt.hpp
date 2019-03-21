#pragma once

class PinInterrupt {
public:
  virtual void pinChanged(uint8_t pin) = 0;

protected:
  bool attachArgInterrupt(uint8_t pin, uint8_t mode) {
    if(pin > 57)
      return false;
    intArg[pin] = this;

    if(pin == 0)
      attachInterrupt(pin, isr<0>, mode);
    else if(pin == 1)
      attachInterrupt(pin, isr<1>, mode);
    else if(pin == 2)
      attachInterrupt(pin, isr<2>, mode);
    else if(pin == 3)
      attachInterrupt(pin, isr<3>, mode);
    else if(pin == 4)
      attachInterrupt(pin, isr<4>, mode);
    else if(pin == 5)
      attachInterrupt(pin, isr<5>, mode);
    else if(pin == 6)
      attachInterrupt(pin, isr<6>, mode);
    else if(pin == 7)
      attachInterrupt(pin, isr<7>, mode);
    else if(pin == 8)
      attachInterrupt(pin, isr<8>, mode);
    else if(pin == 9)
      attachInterrupt(pin, isr<9>, mode);
    else if(pin == 10)
      attachInterrupt(pin, isr<10>, mode);
    else if(pin == 11)
      attachInterrupt(pin, isr<11>, mode);
    else if(pin == 12)
      attachInterrupt(pin, isr<12>, mode);
    else if(pin == 13)
      attachInterrupt(pin, isr<13>, mode);
    else if(pin == 14)
      attachInterrupt(pin, isr<14>, mode);
    else if(pin == 15)
      attachInterrupt(pin, isr<15>, mode);
    else if(pin == 16)
      attachInterrupt(pin, isr<16>, mode);
    else if(pin == 17)
      attachInterrupt(pin, isr<17>, mode);
    else if(pin == 18)
      attachInterrupt(pin, isr<18>, mode);
    else if(pin == 19)
      attachInterrupt(pin, isr<19>, mode);
    else if(pin == 20)
      attachInterrupt(pin, isr<20>, mode);
    else if(pin == 21)
      attachInterrupt(pin, isr<21>, mode);
    else if(pin == 22)
      attachInterrupt(pin, isr<22>, mode);
    else if(pin == 23)
      attachInterrupt(pin, isr<23>, mode);
    else if(pin == 24)
      attachInterrupt(pin, isr<24>, mode);
    else if(pin == 25)
      attachInterrupt(pin, isr<25>, mode);
    else if(pin == 26)
      attachInterrupt(pin, isr<26>, mode);
    else if(pin == 27)
      attachInterrupt(pin, isr<27>, mode);
    else if(pin == 28)
      attachInterrupt(pin, isr<28>, mode);
    else if(pin == 29)
      attachInterrupt(pin, isr<29>, mode);
    else if(pin == 30)
      attachInterrupt(pin, isr<30>, mode);
    else if(pin == 31)
      attachInterrupt(pin, isr<31>, mode);
    else if(pin == 32)
      attachInterrupt(pin, isr<32>, mode);
    else if(pin == 33)
      attachInterrupt(pin, isr<33>, mode);
    else if(pin == 34)
      attachInterrupt(pin, isr<34>, mode);
    else if(pin == 35)
      attachInterrupt(pin, isr<35>, mode);
    else if(pin == 36)
      attachInterrupt(pin, isr<36>, mode);
    else if(pin == 37)
      attachInterrupt(pin, isr<37>, mode);
    else if(pin == 38)
      attachInterrupt(pin, isr<38>, mode);
    else if(pin == 39)
      attachInterrupt(pin, isr<39>, mode);
    else if(pin == 40)
      attachInterrupt(pin, isr<40>, mode);
    else if(pin == 41)
      attachInterrupt(pin, isr<41>, mode);
    else if(pin == 42)
      attachInterrupt(pin, isr<42>, mode);
    else if(pin == 43)
      attachInterrupt(pin, isr<43>, mode);
    else if(pin == 44)
      attachInterrupt(pin, isr<44>, mode);
    else if(pin == 45)
      attachInterrupt(pin, isr<45>, mode);
    else if(pin == 46)
      attachInterrupt(pin, isr<46>, mode);
    else if(pin == 47)
      attachInterrupt(pin, isr<47>, mode);
    else if(pin == 48)
      attachInterrupt(pin, isr<48>, mode);
    else if(pin == 49)
      attachInterrupt(pin, isr<49>, mode);
    else if(pin == 50)
      attachInterrupt(pin, isr<50>, mode);
    else if(pin == 51)
      attachInterrupt(pin, isr<51>, mode);
    else if(pin == 52)
      attachInterrupt(pin, isr<52>, mode);
    else if(pin == 53)
      attachInterrupt(pin, isr<53>, mode);
    else if(pin == 54)
      attachInterrupt(pin, isr<54>, mode);
    else if(pin == 55)
      attachInterrupt(pin, isr<55>, mode);
    else if(pin == 56)
      attachInterrupt(pin, isr<56>, mode);
    else if(pin == 57)
      attachInterrupt(pin, isr<57>, mode);
    return true;
  }
  
private:
  static PinInterrupt* intArg[58];

  template <uint8_t p>
  static void isr() {
    intArg[p]->pinChanged(p);
  }
};
