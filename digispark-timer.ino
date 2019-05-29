#include <SoftRcPulseOut.h>
#include "tick.h"
#include "ramp.h"
#include "delay.h"

SoftRcPulseOut throttle;
Tick timer;
Ramp rampUp;
Ramp rampDown;
Delay pause;

void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);

  throttle.attach(0);
  initialize();
}

void initialize () {
  rampUp    .init(1000, 2000,   1 SECOND   );
  pause     .init(              5 SECONDS  );
  rampDown  .init(2000, 1000,  10 SECONDS  );
}

// Main loop
void loop() {
  if (timer.tick()) {
    if (rampUp.run()) {
      throttle.write_us(rampUp.value);
    }
    else if (pause.wait() && rampDown.run()) {
      throttle.write_us(rampDown.value);
    }
    // ELSE TIMER ENDS
  }

  SoftRcPulseOut::refresh();
}
