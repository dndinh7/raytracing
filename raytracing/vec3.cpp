#include "vec3.h"
#include "rt_util.h"

// Default constructor (zero vector)
vec3::vec3() : x(0), y(0), z(0) {}
vec3::vec3(double t) : x(t), y(t), z(t) {}
vec3::vec3(double x, double y, double z) : x(x), y(y), z(z) {}

vec3 vec3::operator-() const {
	return vec3(-x, -y, -z);
}

vec3 vec3::operator*(double t) const {
	return vec3(x * t, y * t, z * t);
}

vec3 vec3::operator/(double t) const {
	return *this * (1.0 / t);
}

vec3 vec3::operator+(const vec3& v) const {
	return vec3(x + v.x, y + v.y, z + v.z);
}

vec3 vec3::operator-(const vec3& v) const {
	return vec3(x - v.x, y - v.y, z - v.z);
}

vec3 vec3::operator*(const vec3& v) const {
	return vec3(x * v.x, y * v.y, z * v.z);
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

double vec3::length_squared() const {
	return x * x + y * y + z * z;
}

bool vec3::near_zero() const {
	return this->length_squared() < 1e-16;
}

double vec3::length() {
	return sqrt(this->length_squared());
}

double vec3::dot(const vec3& a, const vec3& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec3 vec3::cross(const vec3& a, const vec3& b) {
	return vec3(a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x);
}

vec3 vec3::normalize() {
	return *this * (1.0 / length());
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

vec3 vec3::random() {
	return vec3(random_double(), random_double(), random_double());
}

vec3 vec3::random(double min, double max) {
	return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

vec3 vec3::reflect(const vec3& v, const vec3& n) {

	// we dot(v, n) to get the magnitude of v in the direction of n (subtract since it's opposite of the direction of v)
	// this will reflect v across the n vector (as v's direction should be opposite to n)
	return v - 2 * dot(v, n) * n;
}

vec3 vec3::refract(const vec3& v, const vec3& n, double etai_over_etat) {
	double cos_theta = fmin(dot(-v, n), 1.0);

	// vector decomposition
	vec3 r_perpendicular = etai_over_etat * (v + cos_theta * n);
	vec3 r_parallel = -sqrt(fabs(1 - r_perpendicular.length_squared())) * n;
	return r_perpendicular + r_parallel;
}

// dot product : dot(u, v) = ||u|| * ||v|| * cos(theta)
// positive means u and v are pointing in the same direction
// negative means u and v are pointing in the opposite direction
bool vec3::same_dir(const vec3& a, const vec3& b) {
	return dot(a, b) > 0.0;
}

vec3 vec3::random_in_unit_disk() {
	while (true) {
		vec3 p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
		if (p.length_squared() < 1) return p;
	}
}