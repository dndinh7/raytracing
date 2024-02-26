#ifndef MAP_H
#define MAP_H

#include "vec3.h"

/**
* t is the value in the range start_old <= t <= end_old
* 
* 
* and then will be mapped into the new range start_new <= u <= end_new
*/
inline double map(double t, double start_old, double end_old, double start_new, double end_new) {
	double u = ((t - start_old) / (end_old - start_old) * (end_new - start_new)) + start_new;

	return u;
}

inline vec3 map(const vec3& t, const vec3& start_old, const vec3& end_old, const vec3& start_new, const vec3& end_new) {
	double x = map(t.x, start_old.x, end_old.x, start_new.x, end_new.x);
	double y = map(t.y, start_old.y, end_old.y, start_new.y, end_new.y);
	double z = map(t.z, start_old.z, end_old.z, start_new.z, end_new.z);

	return vec3(x, y, z);
}


#endif