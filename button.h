class Button {
  private:
    uint8_t pin;
    int count;
    int state;
    int longCount;
    int doubleCount;
    int doubleState;
    bool clicked;
        
  public:
    bool once;

    Button (uint8_t pin) {
      this->pin = pin;
      init();
    }

    void init () {
      count = 0;
      state = 0;
      longCount = 0;
      doubleCount = 0;
      doubleState = 0;
      clicked = false;
      once = false;
    }

    bool click () {
      int value = digitalRead(pin);

      switch (state) {
        case 0:
          if (value == LOW && !clicked) {
            state = 1;
            count = 0;
          }
          break;
        case 1:
          count++;
          if (value == HIGH) {
            if (count < 1000 && !clicked) {
              state = 2;
            }
            else {
              state = 0;
            }
            count = 0;
          }
          break;
        case 2:
          count++;
          if (value == LOW) {
            state = 0;
            count = 0;
          }
          if (count > 600  && !clicked) {
              state = 3;
          }
          break;
        case 3:
          once = !clicked;
          clicked = 1;
          return true;
      }
      return false;
    }

    bool longClick () {
      int value = digitalRead(pin);

      if (value == LOW && !clicked && longCount < 2000) {
        longCount++;
      }
      else {
        if (longCount >= 2000) {
          once = !clicked;
          clicked = true;
          return true;
        }
        else {
          longCount = 0;
        }
      }
      return false;
    }

    bool doubleClick () {
      int value = digitalRead(pin);

      switch (doubleState) {
        case 0:
          if (value == LOW && !clicked) {
            doubleState = 1;
            doubleCount = 0;
          }
          break;
        case 1:
          doubleCount++;
          if (value == HIGH) {
            if (doubleCount < 500 && !clicked) {
              doubleState = 2;
            }
            else {
              doubleState = 0;
            }
            doubleCount = 0;
          }
          break;
        case 2:
          doubleCount++;
          if (value == LOW) {
            if (doubleCount < 500 && !clicked) {
              doubleState = 3;
            }
            else {
              doubleState = 0;
            }
            doubleCount = 0;
          }
          break;
        case 3:
          doubleCount++;
          if (value == HIGH) {
            if (doubleCount < 1000 && !clicked) {
              doubleState = 4;
            }
            else {
              doubleState = 0;
            }
            doubleCount = 0;
          }
          break;
        case 4:
          if (!clicked) {
            doubleCount++;
          }

          if (doubleCount > 500) {
            once = !clicked;
            clicked = 1;
            return true;
          }
      }
      return false;
    }
};
