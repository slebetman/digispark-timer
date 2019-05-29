#include <SoftRcPulseOut.h>
#include "tick.h"
#include "ramp.h"
#include "delay.h"
#include "button.h"
#include "blink.h"

#define SERVO_MIN 1000
#define SERVO_MAX 2000

SoftRcPulseOut throttle;
Tick timer;
Ramp rampUp(SERVO_MIN, SERVO_MAX);
Ramp rampDown(SERVO_MAX, SERVO_MIN);
Delay esc;
Delay pause;
Button button(PIN2);
Blink escBlink(PIN1, 100);
Blink runBlink(PIN1, 500);

void setup() {
  pinMode(PIN0, OUTPUT);
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, INPUT_PULLUP);

  throttle.attach(PIN0);
  esc.init( 2.5 SECONDS );
  initialize();
}

void initialize () {
  throttle.write_us(SERVO_MIN);
  button.init();
}

// Main loop
void loop() {
  if (timer.tick()) {
      if (esc.wait()) { // wait for ESC to initialize
        escBlink.blink();
      }
      else {
        escBlink.stop();
        int input = digitalRead(PIN2);
        
        if (button.click()) {
          if (button.once) {
              rampUp   .init(   1 SECOND  );
              pause    .init(   5 SECONDS );
              rampDown .init(   5 SECONDS );
          }
          run();
        }
        else if (button.longClick()) {
          if (button.once) {
              rampUp   .init(   1 SECOND  );
              pause    .init(  10 SECONDS );
              rampDown .init(  10 SECONDS );
          }
          run();
        }
        else if (button.doubleClick()) {
          if (button.once) {
              rampUp   .init(   1 SECOND  );
              pause    .init( 3.5 SECONDS );
              rampDown .init( 1.5 SECONDS );
          }
          run();
        }
      }
  }

  SoftRcPulseOut::refresh();
}

void run () {
  if (rampUp.run()) {
    throttle.write_us(rampUp.value);
    digitalWrite(PIN1,HIGH);
  }
  else if (pause.wait()) {
    runBlink.blink();
  }
  else if (rampDown.run()) {
    throttle.write_us(rampDown.value);
    runBlink.blink();
  }
  else {
    runBlink.stop();
    initialize();
  }
}

