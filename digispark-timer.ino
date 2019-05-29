#include <SoftRcPulseOut.h>
#include "tick.h"
#include "ramp.h"
#include "delay.h"

#define SERVO_MIN 1000
#define SERVO_MAX 2000

SoftRcPulseOut throttle;
SoftRcPulseOut deThermaliser;
Tick timer;
Ramp rampUp;
Ramp rampDown;
Delay pause;

void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);

  throttle.attach(0);
  deThermaliser.attach(1);
  initialize();
}

void initialize () {
  deThermaliser.write_us(SERVO_MAX);
  rampUp    .init(SERVO_MIN, SERVO_MAX,   1 SECOND   );
  pause     .init(                       10 SECONDS  );
  rampDown  .init(SERVO_MAX, SERVO_MIN,  10 SECONDS  );
}

// Main loop
void loop() {
  if (timer.tick()) {
    if (rampUp.run()) {
      throttle.write_us(rampUp.value);
    }
    else if (pause.wait()) {
      // do nothing
    }
    else if (rampDown.run()) {
      throttle.write_us(rampDown.value);
    }
    else {
      deThermaliser.write_us(SERVO_MIN);
    }
  }

  SoftRcPulseOut::refresh();
}
