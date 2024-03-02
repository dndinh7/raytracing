#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
	public:
		double min, max;

		interval() : min(+infinity), max(-infinity) {}
		
		interval(double min, double max) : min(min), max(max) {}

		bool contains(double x) const {
			return min <= x && x <= max;
		}

		bool surrounds(double x) const {
			return min < x && x < max;
		}

		double clamp(double x) {
			if (x < min) return min;
			if (x > max) return max;
			return x;
		}

		static const interval empty, universe;
};

const static interval empty(+infinity, -infinity); // will never contain any number
const static interval universe(-infinity, +infinity); // will contain every number


#endif