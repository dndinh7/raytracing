#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
	public:
		ray() : orig(), dir() {}

		ray(const point3& orig, const vec3& dir);

		point3 at(double t) const;

		point3 origin() const { return orig; }
		vec3 direction() const { return dir; }

		static bool hit_sphere(const point3& center, double radius, const ray& r);

	private:
		point3 orig;
		vec3 dir;

};

#endif
