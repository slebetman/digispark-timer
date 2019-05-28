class Ramp {
	private:
		int from;
		int to;
		float increment;
    float _value;
		
	public:
		int value;
		
		Ramp () {}
	
	  // assuming 1ms tick
		void init (int vFrom, int vTo, float seconds) {
			from = vFrom;
			to = vTo;
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
