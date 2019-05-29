#include <SoftRcPulseOut.h>
#include "tick.h"
#include "ramp.h"
#include "delay.h"
#include "button.h"

#define SERVO_MIN 1000
#define SERVO_MAX 2000

SoftRcPulseOut throttle;
Tick timer;
Ramp rampUp(SERVO_MIN, SERVO_MAX);
Ramp rampDown(SERVO_MAX, SERVO_MIN);
Button button;
Delay pause;

void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, INPUT);

  throttle.attach(0);
  button.init();
  initialize();
}

void initialize () {
  rampUp    .init( 1 SECOND  );
  pause     .init( 5 SECONDS );
  rampDown  .init( 5 SECONDS );
}

// Main loop
void loop() {
  if (timer.tick()) {
    if (button.click(digitalRead(1))) {
      if (rampUp.run()) {
        throttle.write_us(rampUp.value);
      }
      else if (pause.wait()) {
        // do nothing
      }
      else if (rampDown.run()) {
        throttle.write_us(rampDown.value);
      }
    }
  }

  SoftRcPulseOut::refresh();
}
