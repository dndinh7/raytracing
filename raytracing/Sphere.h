#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#include "hittable.h"

class sphere : public shape, public hittable {
	public:
		sphere() : shape(), radius(1) {}
		sphere(point3 origin) : shape(origin), radius(1) {}
		sphere(point3 origin, double radius) : shape(origin), radius(radius) {}

		// gets radius
		double getRadius() const {
			return radius;
		}
		/**
		* ray_tmin and ray_tmax is the range we will look for the root, insight is that we will
		* don't want to render roots behind the closest objects
		*/
		bool intersects(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
			// equation is (P - C) dot (P - C) = radius * radius to get a point on the sphere
			// P = A + tB, it is a ray that will be equivalent to P at some t
			// giving equation t^2*B dot B + 2 * t * B dot (A - C) + (A - C) dot (A - C) - r^2 = 0
			// then we solve for t and if a root exists, we have hit the sphere (quadratic formula)
			// -b +- sqrt(b^2 - 4ac) / 2a -> map coefficents to be a, b, c (only need determinant to be >= 0 to have real roots)
			// Givens: B is the ray dir, A is the ray origin, C is the center of sphere

			// however, we can factor out a two from B so that we have 2 * h where h= B dot (A - C)
			// we well get -(2h) +- sqrt(4h^2 - 4ac) / 2a ---> -2h +- 2sqrt(h^2 - ac) / 2a ---> -h +- sqrt(h^2 - ac) / a


			vec3 AC = r.origin() - this->origin;

			// B dot B = b.length_squared
			double a = r.direction().length_squared();

			//double b = 2.0 * vec3::dot(this->dir, AC); h will now be half of b to simplify equation
			double h = vec3::dot(r.direction(), AC);

			// (A - C) dot (A - C) = AC.length_squared
			double c = AC.length_squared() - this->radius * this->radius;

			double discriminant = h * h - a * c;
			

			if (discriminant < 0) {
				return false;
			}

			double sqrt_disc = sqrt(discriminant);

			// we want to find the closest point (nearest root in the range)
			double root = (-h - sqrt_disc) / a;
			if (root < ray_tmin || root > ray_tmax) { // check if in range
				root = (-h + sqrt_disc) / a;
				if (root < ray_tmin || root > ray_tmax) {
					// if both roots are out of range, ray does not hit the sphere
					return false;
				}
			}

			rec.t = root;
			rec.p = r.at(rec.t);

			// unit vector because the length of vector is radius
			vec3 outward_normal = (rec.p - this->origin) / this->radius;

			rec.set_face_normal(r, outward_normal);

			return true;
		}

	private:
		double radius;
};



#endif