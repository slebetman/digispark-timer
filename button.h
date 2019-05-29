class Button {
  private:
    int count;
    int timer;
    bool clicked;
        
  public:
    Button () {
      init();
    }

    void init () {
      count = 0;
      timer = 0;
      clicked = false;
    }

    bool click (int value) {
      if (value == LOW && !clicked) {
        count++;
      }
      else {
        if (count > 3 && count < 2000) {
          if (!clicked) {
            timer ++;
          }
          if (timer > 500) {
            clicked = true;
            return true;
          }
        }
      }
      return false;
    }

    bool longClick (int value) {
      if (value == LOW && !clicked && count < 2000) {
        count++;
      }
      else {
        if (count >= 2000) {
          clicked = true;
          return true;
        }
      }
      return false;
    }
};
