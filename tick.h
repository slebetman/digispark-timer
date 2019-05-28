#define SECOND
#define SECONDS

// 1 millisecond tick
class Tick {
  private:
	uint32_t _tick;
  public:
  
	Tick () {
	  _tick = 0;
	}
  
	bool tick() {
	  uint32_t t = millis();
	  if (t != _tick) {
  		_tick = t;
  		return true;
	  }
	  return false;
	}
};
