class Ramp {
	private:
		int from;
		int to;
		float increment;
    float _value;
		
	public:
		int value;
		
		Ramp (int from, int to) {
		  this->from = from;
		  this->to = to;
		}
	
	  // assuming 1ms tick
		void init (float seconds) {
			increment = 1/seconds;
			value = from;
      _value = value;
		}
		
		bool run () {
			if (from < to) {
				if (value < to) {
					_value += increment;
          value = _value;
					return true;
				}
				else {
					return false;
				}
			}
			else {
				if (value > to) {
					_value -= increment;
          value = _value;
					return true;
				}
				else {
					return false;
				}
			}
		}
};
