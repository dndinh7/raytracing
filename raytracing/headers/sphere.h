#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"
#include "hittable.h"

class sphere : public shape, public hittable {
	public:

		sphere(point3 origin, double radius, shared_ptr<material> material);

		// gets radius
		double getRadius() const;

		bool intersects(const ray& r, interval ray_t, hit_record& rec) const override;

		point3 getOrigin() const;

		void setOrigin(point3 origin);
		

	private:
		point3 origin;
		double radius;
		shared_ptr<material> mat;
};



#endif