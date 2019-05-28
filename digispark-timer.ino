#include <SoftRcPulseOut.h>

SoftRcPulseOut servo1;
unsigned int pos;
bool dir;

void setup() {                
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);

  servo1.attach(0);
  pos = 1000;
  dir = true;
}


// 1 millisecond tick
uint32_t _tick;
bool tick () {
  uint32_t t = millis();
  if (t != _tick) {
    _tick = t;
    return true;
  }
  return false;
}

void loop() {
  if (tick()) {
    if (dir) {
      if (pos < 2000) {
        pos += 2;
      }
      else {
        dir = false;
      }
    }
    else {
      if (pos > 1000) {
        pos -= 2;
      }
      else {
        dir = true;
      }
    }
    servo1.write_us(pos);
  }    

  SoftRcPulseOut::refresh();
}
