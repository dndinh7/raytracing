#ifndef SHAPE_H
#define SHAPE_H

#include "vec3.h"
#include "ray.h"

class Shape {
	protected:
		point3 origin;

	public:
		Shape() : origin(point3(0)) {}
		Shape(point3 origin) : origin(origin) {}

		point3 getOrigin() const {
			return origin;
		}

		void setOrigin(point3 origin) {
			origin = origin;
		}

};


#endif SHAPE_H