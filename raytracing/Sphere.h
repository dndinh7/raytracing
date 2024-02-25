#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Sphere : public Shape {
	public:
		Sphere() : Shape(), radius(1) {}
		Sphere(point3 origin) : Shape(origin), radius(1) {}
		Sphere(point3 origin, color col) : Shape(origin, col), radius(1) {}
		Sphere(point3 origin, double radius) : Shape(origin), radius(radius) {}
		Sphere(point3 origin, double radius, color col) : Shape(origin, col), radius(radius) {}

		// gets radius
		double getRadius() const {
			return radius;
		}

	private:
		double radius;
};



#endif CIRCLE_H