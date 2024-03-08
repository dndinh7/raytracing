#ifndef MATERIAL_H
#define MATERIAL_H

#include "rt_util.h"

class hit_record;

using color = vec3;

class material {
	public:
		virtual ~material() = default;

		virtual bool scatter(
			const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};


class lambertian : public material {
	public:
		lambertian(const color& a) : albedo(a) {}

		bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
			// ray_in doesn't matter because light is scattered everywhere
			
			vec3 scatter_direction = rec.normal + random_unit_vector();

			// if the scatter direction is the negative vector, then we just use the normal
			if (scatter_direction.near_zero()) {
				scatter_direction = rec.normal;
			}

			scattered = ray(rec.p, scatter_direction);

			attenuation = albedo;
			return true;
		}

	private:
		color albedo;
};

class metal : public material {
	public:
		metal(const color& a) : albedo(a) {}

		bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
			// metal will scatter the light by reflecting it over the normal
			vec3 reflected = vec3::reflect(r_in.direction(), rec.normal);

			scattered = ray(rec.p, reflected);

			attenuation = albedo;
			return true;
		}

	private:
		color albedo;
};


#endif