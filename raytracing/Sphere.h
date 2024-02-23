#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Sphere : public Shape {
	public:
		Sphere() : Shape() {}
		Sphere(point3 origin) : Shape(origin), radius(1) {}
		Sphere(point3 origin, double radius) : Shape(origin), radius(radius) {}

		// gets radius
		double getRadius() const {
			return radius;
		}

	private:
		double radius;
};



#endif CIRCLE_H