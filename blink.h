class Blink {
  private:
    int count;
    int interval;
    uint8_t pin;

  public:
    Blink (uint8_t pin, int interval) {
      this->interval = interval;
      this->pin = pin;
      stop();
    }

    void blink () {
      count ++;

      if (count < interval) {
        digitalWrite(pin, HIGH);
      }
      else {
        if (count > (interval * 2)) {
          count = 0;
        }
        digitalWrite(pin, LOW);
      }
    }

    void stop () {
      if (count != 0) {
        count = 0;
        digitalWrite(pin, LOW);
      }
    }
};
