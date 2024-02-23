#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "ray.h"
#include "Sphere.h"
#include <iostream>

using color = vec3;

void write_color(std::ostream& out, const color& pixel) {
	// [0, 255]
	out << static_cast<int>(255.999 * pixel.x) << ' '
		<< static_cast<int>(255.999 * pixel.y) << ' '
		<< static_cast<int>(255.999 * pixel.z) << std::endl;
}

color ray_color(const Sphere& s, const ray& r) {
    // if the ray hits the sphere, then we color it red :)
    if (r.intersects(s)) return color(1, 0, 0);
    //if (ray::hit_sphere(vec3(0, 0, -1), 0.5, r)) return color(1, 0, 0);

    // color is dependent on y value of ray, we normalize it to [0, 1]
    vec3 unit_dir = r.direction().normalize();
    double alpha = 0.5 * (unit_dir.y + 1.0);

    return vec3::lerp(color(1.0, 1.0, 1.0), color(0.5, 0.7, 1.0), alpha);
}


#endif COLOR