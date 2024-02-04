#include "vec3.h"

// Default constructor (zero vector)
vec3::vec3() : x(0), y(0), z(0) {}

vec3::vec3(double x, double y, double z) : x(x), y(y), z(z) {}

vec3 vec3::operator-() const {
	return vec3(-x, -y, -z);
}

vec3 vec3::operator*(double t) const {
	return vec3(x * t, y * t, z * t);
}

vec3 vec3::operator+(const vec3& v) const {
	return vec3(x + v.x, y + v.y, z + v.z);
}

vec3 vec3::operator-(const vec3& v) const {
	return vec3(x - v.x, y - v.y, z - v.z);
}

vec3& vec3::operator+=(const vec3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

vec3& vec3::operator-=(const vec3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

vec3& vec3::operator*=(const vec3& v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

vec3& vec3::operator/=(const vec3& v) {
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

vec3& vec3::operator*=(double t) {
	x *= t;
	y *= t;
	z *= t;
	return *this;
}

vec3& vec3::operator/=(double t) {
	return *this *= 1 / t;
}

double vec3::length_squared() {
	return x * x + y * y + z * z;
}

double vec3::length() {
	return sqrt(this->length_squared());
}

vec3 vec3::dot(const vec3& v) {
	return vec3(x * v.x, y * v.y, z * v.z);
}

vec3 vec3::cross(const vec3& v) {
	return vec3(y * v.z - z * v.y,
				z * v.x - x * v.z,
				x * v.y - y * v.x);
}

vec3 vec3::normalize() {
	return *this * (1 / length());
}

double vec3::distance_squared(const vec3& a, const vec3& b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z);
}

double vec3::distance(const vec3& a, const vec3& b) {
	return sqrt(distance_squared(a, b));
}

vec3 vec3::lerp(const vec3& a, const vec3& b, double t) {
	return a * (1 - t) + b * t;
}
