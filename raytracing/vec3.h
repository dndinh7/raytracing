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

		// for division do * 1/t
		vec3 operator*(double t) const;

		vec3 operator/(double t) const;

		vec3& operator+=(const vec3& v);

		vec3& operator-=(const vec3& v);

		vec3& operator*=(const vec3& v);

		vec3& operator/=(const vec3& v);

		vec3& operator*=(double t);

		vec3& operator/=(double t);

		vec3 dot(const vec3& v);

		vec3 cross(const vec3& v);

		double length();

		double length_squared();

		vec3 normalize();

		static double distance_squared(const vec3& a, const vec3& b);

		static double distance(const vec3& a, const vec3& b);

		static vec3 lerp(const vec3& a, const vec3& b, double t);

};

using point3 = vec3;

inline vec3 operator*(double t, const vec3& v) {
	return vec3(v.x * t, v.y * t, v.z * t);
}

inline std::ostream& operator<<(std::ostream& os, const vec3& v) {
	return os << v.x << ' ' << v.y << ' ' << v.z;
}

#endif