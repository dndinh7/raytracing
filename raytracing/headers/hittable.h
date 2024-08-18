#ifndef HITTABLE_H
#define HITTABLE_H

#include "rt_util.h"

class material;

class hit_record {
	public:
		point3 p; // hit point
		vec3 normal; // normal to surface
		shared_ptr<material> mat;
		double t; // "time" at which it hit
		bool front_face; // determines if the normal is part of the front face

		// outward_normal should be unit vector
		void set_face_normal(const ray& r, const vec3& outward_normal) {
			
			// if the ray comes from inside the sphere, then the front_face is the inside
			front_face = !vec3::same_dir(r.direction(), outward_normal);
			

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