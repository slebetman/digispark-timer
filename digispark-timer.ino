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
Ramp shortRampDown(SERVO_MAX, SERVO_MIN);
Ramp rampDown(SERVO_MAX, SERVO_MIN);
Ramp longRampDown(SERVO_MAX, SERVO_MIN);
Delay esc;
Delay shortPause;
Delay pause;
Delay longPause;
Button button;
Blink escBlink(100);
Blink runBlink(500);

void setup() {
  pinMode(PIN0, OUTPUT);
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, INPUT_PULLUP);

  throttle.attach(PIN0);
  esc.init( 2.5 SECONDS );
  initialize();
}

void initialize () {
  rampUp        .init( 1.5 SECONDS );
  pause         .init(   5 SECONDS );
  rampDown      .init(   5 SECONDS );

  shortPause    .init( 3.5 SECONDS );
  shortRampDown .init( 1.5 SECONDS );

  longPause     .init(  10 SECONDS );
  longRampDown  .init(  10 SECONDS );

  throttle.write_us(SERVO_MIN);
  button.init();
}

// Main loop
void loop() {
  if (timer.tick()) {
      if (esc.wait()) { // wait for ESC to initialize
        digitalWrite(PIN1, escBlink.blink());
      }
      else {
        digitalWrite(PIN1, LOW);
        int input = digitalRead(PIN2);
        
        if (button.click(input)) {
          if (rampUp.run()) {
            throttle.write_us(rampUp.value);
            digitalWrite(PIN1, runBlink.blink());
          }
          else if (pause.wait()) {
            digitalWrite(PIN1, runBlink.blink());
          }
          else if (rampDown.run()) {
            throttle.write_us(rampDown.value);
            digitalWrite(PIN1, runBlink.blink());
          }
          else {
            digitalWrite(PIN1, LOW);
            initialize();
          }
        }
        else if (button.longClick(input)) {
          if (rampUp.run()) {
            throttle.write_us(rampUp.value);
            digitalWrite(PIN1, runBlink.blink());
          }
          else if (longPause.wait()) {
            digitalWrite(PIN1, runBlink.blink());
          }
          else if (longRampDown.run()) {
            throttle.write_us(longRampDown.value);
            digitalWrite(PIN1, runBlink.blink());
          }
          else {
            digitalWrite(PIN1, LOW);
            initialize();
          }
        }
        else if (button.doubleClick(input)) {
          if (rampUp.run()) {
            throttle.write_us(rampUp.value);
            digitalWrite(PIN1, runBlink.blink());
          }
          else if (shortPause.wait()) {
            digitalWrite(PIN1, runBlink.blink());
          }
          else if (shortRampDown.run()) {
            throttle.write_us(shortRampDown.value);
            digitalWrite(PIN1, runBlink.blink());
          }
          else {
            digitalWrite(PIN1, LOW);
            initialize();
          }
        }
      }
  }

  SoftRcPulseOut::refresh();
}
