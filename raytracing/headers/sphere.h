#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"
#include "hittable.h"

class sphere : public shape, public hittable {
	public:

		sphere(const point3& origin, double radius, shared_ptr<material> material);

		sphere(const point3& origin1, const point3& origin2, double radius, shared_ptr<material> material);

		// gets radius
		double getRadius() const;

		bool intersects(const ray& r, interval ray_t, hit_record& rec) const override;

		ray getOrigin() const;

		void setOrigin(ray origin);
		

	private:
		ray origin;
		double radius;
		shared_ptr<material> mat;
};



#endif