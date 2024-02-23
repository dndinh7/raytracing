#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include "Sphere.h"

class ray {
public:
	ray() : orig(), dir() {}

	ray(const point3& orig, const vec3& dir);

	point3 at(double t) const;

	point3 origin() const { return orig; }
	vec3 direction() const { return dir; }

	bool intersects(const Sphere& s) const;
	private:
		point3 orig;
		vec3 dir;

};

#endif
