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
		metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

		bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
			// metal will scatter the light by reflecting it over the normal
			vec3 reflected = vec3::reflect(r_in.direction(), rec.normal);

			scattered = ray(rec.p, reflected + fuzz * random_unit_vector());

			attenuation = albedo;
			return vec3::dot(rec.normal, scattered.direction()) > 0;
		}

	private:
		color albedo;
		double fuzz;
};


class dielectric : public material {
	public:
		dielectric(double index_of_refraction) : ir(index_of_refraction) {}

		bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
			// simplicity for refractive material
			attenuation = color(1.0);

			// if entering from outside to in, then inner angle is found as the reciprocal
			double refract_ratio = rec.front_face ? (1.0 / ir) : ir;
			vec3 unit_dir = r_in.direction().normalize();

			double cos_theta = fmin(vec3::dot(-unit_dir, rec.normal), 1.0);
			double sin_theta = sqrt(1 - cos_theta * cos_theta);

			// if less than 1, we refract, else we reflect
			bool reflect = refract_ratio * sin_theta > 1.0;

			vec3 dir;

			if (reflect || reflectance(cos_theta, refract_ratio) > random_double()) {
				dir = vec3::reflect(unit_dir, rec.normal);
			}
			else {
				dir = vec3::refract(unit_dir, rec.normal, refract_ratio);
			}


			scattered = ray(rec.p, dir);

			return true;
		}

	private:
		double ir;

		static double reflectance(double cosine, double ref_idx) {
			// Use Schlick's approximation for reflectance.
			auto r0 = (1 - ref_idx) / (1 + ref_idx);
			r0 = r0 * r0;
			return r0 + (1 - r0) * pow((1 - cosine), 5);
		}
};

#endif