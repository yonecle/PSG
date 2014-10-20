#ifndef REGISTER_SETTER_H
#define REGIATER_SETTER_H

class RegisterSetter {
public:
  virtual void set(byte data) = 0;
};


class ShiftRegisterSetter : public RegisterSetter {
public:
  ShiftRegisterSetter(byte data, byte latch, byte clock)
  : data_pin(data), latch_pin(latch), clock_pin(clock)
  {
  }

  void set(byte data){
    digitalWrite(latch_pin, LOW);
    shiftOut(data_pin, clock_pin, MSBFIRST, data);
    digitalWrite(latch_pin, HIGH);
  }

private:
  byte data_pin;
  byte latch_pin;
  byte clock_pin;
};

#endif

