#ifndef HITTABLE_H
#define HITTABLE_H

#include "rt_util.h"

class hit_record {
	public:
		point3 p;
		vec3 normal;
		double t;
		bool front_face;

		// outward_normal should be unit vector
		void set_face_normal(const ray& r, const vec3& outward_normal) {
			// dot product : dot(u, v) = ||u|| * ||v|| * cos(theta)
			// positive means u and v are pointing in the same direciton
			// negative means u and v are pointing in the opposite direction
			front_face = vec3::dot(r.direction(), outward_normal) < 0;

			// normal should always be opposite to the ray, so that we render the face correctly
			normal = front_face ? outward_normal : -outward_normal;
		}

};

// abstract class for "surfaces"
class hittable {
	public:
		virtual ~hittable() = default;

		virtual bool intersects(const ray& r, interval ray_t, hit_record& hit) const = 0;
};





#endif