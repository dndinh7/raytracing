#ifndef COLOR_H
#define COLOR_H

#include "map.h"
#include "hittable_list.h"
#include <iostream>

typedef uint8_t Uint8;

using color = vec3;

class sphere;

inline void write_color(std::ostream& out, const color& pixel) {
	// [0, 255]
	out << static_cast<int>(255.999 * pixel.x) << ' '
		<< static_cast<int>(255.999 * pixel.y) << ' '
		<< static_cast<int>(255.999 * pixel.z) << std::endl;
}

inline void convert_col_to_RGB(const color& col, Uint8& red, Uint8& green, Uint8& blue) {
    red = static_cast<Uint8>(255.999 * col.x);
    green = static_cast<Uint8>(255.999 * col.y);
    blue = static_cast<Uint8>(255.999 * col.z);
} 

inline color ray_color(const ray& r, const hittable& world) {
    // if the ray hits the sphere, then we want to get the normal of that point on the surface
    hit_record rec;

    if (world.intersects(r, interval(0, +infinity), rec)) {
        // map to 0 to 1
        color col = map(rec.normal, vec3(-1), vec3(1), vec3(0), vec3(1));

        return col;
    }

    // color is dependent on y value of ray, we normalize it to [0, 1]
    vec3 unit_dir = r.direction().normalize();
    double alpha = map(unit_dir.y, -1, 1, 0, 1);

    return vec3::lerp(color(1.0, 1.0, 1.0), color(0.5, 0.7, 1.0), alpha);
}


#endif