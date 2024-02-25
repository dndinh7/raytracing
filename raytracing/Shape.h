#ifndef SHAPE_H
#define SHAPE_H

#include "vec3.h"
#include "ray.h"

using color = vec3;

class Shape {
	protected:
		point3 origin;
		color col= vec3(1);

	public:
		Shape() : origin(point3(0)) {}
		Shape(point3 origin) : origin(origin) {}
		Shape(point3 origin, vec3 color) : origin(origin), col(color) {}

		point3 getOrigin() const {
			return origin;
		}

		void setOrigin(point3 origin) {
			origin = origin;
		}

		color getColor() const {
			return col;
		}

};


#endif SHAPE_H