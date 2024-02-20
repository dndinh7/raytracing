#include "ray.h"

ray::ray(const point3& orig, const vec3& dir) : orig(orig), dir(dir) {}

point3 ray::at(double t) const {
	return orig + dir * t;
}

