#include "ray.h"

ray::ray(const point3& orig, const vec3& dir) : orig(orig), dir(dir) {}

point3 ray::at(double t) const {
	return orig + dir * t;
}

bool ray::intersects(const Sphere& s) const {
	// equation is (P - C) dot (P - C) = radius * radius to get a point on the sphere
	// P = A + tB, it is a ray that will be equivalent to P at some t
	// giving equation t^2*B dot B + 2 * t * B dot (A - C) + (A - C) dot (A - C) - r^2 = 0
	// then we solve for t and if a root exists, we have hit the sphere (quadratic formula)
	// -b +- sqrt(b^2 - 4ac) / 2a -> map coefficents to be a, b, c (only need determinant to be >= 0 to have real roots)
	// Givens: B is the ray dir, A is the ray origin, C is the center of sphere

	vec3 AC = this->orig - s.getOrigin();

	double a = vec3::dot(this->dir, this->dir);
	double b = 2.0 * vec3::dot(this->dir, AC);
	double c = vec3::dot(AC, AC) - s.getRadius() * s.getRadius();

	double discriminant = b * b - 4 * a * c;
	return discriminant >= 0;
}