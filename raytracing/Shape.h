#ifndef SHAPE_H
#define SHAPE_H

#include "vec3.h"
#include "ray.h"

using color = vec3;

class shape {
	protected:
		point3 origin;

	public:
		shape() : origin(point3(0)) {}
		shape(point3 origin) : origin(origin) {}

		point3 getOrigin() const {
			return origin;
		}

		void setOrigin(point3 origin) {
			origin = origin;
		}

};


#endif