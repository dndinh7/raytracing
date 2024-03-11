#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>


class vec3 {
	public:
		double x;
		double y;
		double z;

		vec3();
		vec3(double t);
		vec3(double x, double y, double z);

		vec3 operator-() const;

		vec3 operator+(const vec3& v) const;

		vec3 operator-(const vec3& v) const;

		vec3 operator* (const vec3& v) const;

		// for division do * 1/t
		vec3 operator*(double t) const;

		vec3 operator/(double t) const;

		vec3& operator+=(const vec3& v);

		vec3& operator-=(const vec3& v);

		vec3& operator*=(const vec3& v);

		vec3& operator/=(const vec3& v);

		vec3& operator*=(double t);

		vec3& operator/=(double t);

		double length();

		double length_squared() const;

		bool near_zero() const;

		vec3 normalize();

		static double distance_squared(const vec3& a, const vec3& b);

		static double distance(const vec3& a, const vec3& b);

		static vec3 lerp(const vec3& a, const vec3& b, double t);

		static double dot(const vec3& a, const vec3& b);

		static vec3 cross(const vec3& a, const vec3& b);

		static vec3 random();

		static vec3 random(double min, double max);

		static bool same_dir(const vec3& a, const vec3& b);

		static vec3 reflect(const vec3& v, const vec3& n);

		static vec3 refract(const vec3& v, const vec3& n, double etai_over_etat);
};

using point3 = vec3;

inline vec3 operator*(double t, const vec3& v) {
	return vec3(v.x * t, v.y * t, v.z * t);
}

inline std::ostream& operator<<(std::ostream& os, const vec3& v) {
	return os << v.x << ' ' << v.y << ' ' << v.z;
}

inline vec3 random_in_unit_sphere() {
	while (true) {
		vec3 p = vec3::random(-1, 1);
		if (p.length_squared() < 1) return p;
	}
}

inline vec3 random_unit_vector() {
	return random_in_unit_sphere().normalize();
}

inline vec3 random_on_hemisphere(const vec3& normal) {
	vec3 on_unit_sphere = random_unit_vector();
	if (vec3::same_dir(on_unit_sphere, normal)) {
		return on_unit_sphere;
	}
	return -on_unit_sphere;
}


#endif