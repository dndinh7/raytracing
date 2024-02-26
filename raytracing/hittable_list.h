#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable {
	public:
		std::vector<shared_ptr<hittable>> objects;

		hittable_list() {}
		hittable_list(shared_ptr<hittable> object) { add(object); }

		void clear() { objects.clear(); }

		void add(shared_ptr<hittable> object) { objects.push_back(object); }

		bool intersects(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
			hit_record closest_rec;
			bool intersected_anything = false;
			double closest_t = ray_tmax;

			for (const auto& object : this->objects) {
				if (object->intersects(r, ray_tmin, closest_t, closest_rec)) {
					intersected_anything = true;
					closest_t = closest_rec.t;
					rec = closest_rec;
				}
			}

			return intersected_anything;
		}


};


#endif