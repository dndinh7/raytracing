#ifndef RT_UTIL_H
#define RT_UTIL_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// headers
#include "ray.h"
#include "vec3.h"
#include "interval.h"


// functions
inline double degrees_to_rad(double degrees) {
	return degrees * 180 / pi;
}

// 0 to 1
inline double random_double() {
	return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
	return (max - min) * random_double() + min;
}

/**
* t is the value in the range start_old <= t <= end_old
*
*
* and then will be mapped into the new range start_new <= u <= end_new
*/
inline double map(double t, interval old_interval, interval new_interval) {
	double u = ((t - old_interval.min) / (old_interval.max - old_interval.min) * 
		(new_interval.max - new_interval.min)) + new_interval.min;

	return u;
}

inline vec3 map(const vec3& t, const vec3& start_old, const vec3& end_old, const vec3& start_new, const vec3& end_new) {
	double x = map(t.x, interval(start_old.x, end_old.x), interval(start_new.x, end_new.x));
	double y = map(t.y, interval(start_old.y, end_old.y), interval(start_new.y, end_new.y));
	double z = map(t.z, interval(start_old.z, end_old.z), interval(start_new.z, end_new.z));

	return vec3(x, y, z);
}




#endif