class Delay {
	private:
		uint32_t timeout;
		uint32_t tick;
	
	public:
	  Delay () {}
	  
	  void init (float seconds) {
	    tick = 0;
	    timeout = seconds * 1000;
	  }
	  
	  bool wait () {
	    tick++;
	    if (tick >= timeout) {
	      return true;
	    }
	    return false;
	  }
};
