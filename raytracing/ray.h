#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
	public:
		ray() {}

		ray(const point3& origin, const vec3& dir) : origin(origin), dir(dir) {}

		point3 at(double t) const {
			return origin + dir * t;
		}

	private:
		point3 origin;
		vec3 dir;

};

#endif
