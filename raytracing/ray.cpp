#include "ray.h"

ray::ray(const point3& orig, const vec3& dir) : orig(orig), dir(dir) {}

point3 ray::at(double t) const {
	return orig + dir * t;
}

bool ray::hit_sphere(const point3& center, double radius, const ray& r) {
    // equation is (P - C) dot (P - C) = radius * radius to get sphere
    // P = A + tb, it is a ray that will be equivalent to P at some t
    // giving equation t^2*b dot b + 2 * t * b dot (A - C) + (A - C) dot (A - C) - r^2 = 0
    // then we solve for t and if a root exists, we have hit the sphere (quadratic formula)
    // Givens: b is the ray dir, A is the ray origin, C is the center of sphere

    vec3 AC = r.origin() - center;

    double a = vec3::dot(r.direction(), r.direction());
    double b = 2.0 * vec3::dot(r.direction(), AC);
    double c = vec3::dot(AC, AC) - radius * radius;

    double discriminant = b * b - 4 * a * c;
    return discriminant >= 0;
}