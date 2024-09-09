#include "ray.h"

ray::ray() : orig(), dir() {}

ray::ray(const point3& orig, const vec3& dir, double time) : orig(orig), dir(dir), tm(time) {}

ray::ray(const point3& orig, const vec3& dir) : ray(orig, dir, 0.0) {}

point3 ray::at(double t) const {
	return orig + dir * t;
}

double ray::time() const {
	return tm;
}

