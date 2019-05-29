class Blink {
  private:
    int count;
    int interval;

  public:
    Blink (int interval) {
      count = 0;
      this->interval = interval;
    }

    bool blink () {
      count ++;

      if (count < interval) {
        return true;
      }
      else if (count > (interval * 2)) {
        count = 0;
      }
      return false;
    }
};
