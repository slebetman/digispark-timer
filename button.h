class Button {
  private:
    int count;
    int longCount;
    bool clicked;
        
  public:
    Button () {
      init();
    }

    void init () {
      count = 0;
      longCount = 0;
      clicked = false;
    }

    bool click (int value) {
      if (value == LOW && !clicked) {
        count++;
      }
      else {
        if (count > 3 && count < 2000) {
          clicked = true;
          return true;
        }
        else {
          count = 0;
        }
      }
      return false;
    }

    bool longClick (int value) {
      if (value == LOW && !clicked && longCount < 2000) {
        longCount++;
      }
      else {
        if (longCount >= 2000) {
          clicked = true;
          return true;
        }
        else {
          longCount = 0;
        }
      }
      return false;
    }
};
