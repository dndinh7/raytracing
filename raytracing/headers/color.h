#ifndef COLOR_H
#define COLOR_H


#include "hittable_list.h"
#include <iostream>

typedef uint8_t Uint8;

using color = vec3;

class sphere;


inline double linear_to_gamma(double linear_component) {
	return sqrt(linear_component);
}

inline void write_color(std::ostream& out, const color& pixel) {
	// [0, 255]
	out << static_cast<int>(256 * pixel.x) << ' '
		<< static_cast<int>(256 * pixel.y) << ' '
		<< static_cast<int>(256 * pixel.z) << std::endl;
}

inline void convert_col_to_RGB(const color& col_sum, int samples_per_pixel, Uint8& red, Uint8& green, Uint8& blue) {
	
	double scale = 1.0 / samples_per_pixel;

	interval intensity(0.0, 0.999);

	double r = intensity.clamp(col_sum.x * scale);
	double g = intensity.clamp(col_sum.y * scale);
	double b = intensity.clamp(col_sum.z * scale);

	// fast gamma correct by square rooting instead of raising to 1/2.2
	r = linear_to_gamma(r);
	g = linear_to_gamma(g);
	b = linear_to_gamma(b);

	
	// r, g, b < 1, and the cast will truncate the value 
	red = static_cast<Uint8>(256 * r);
    green = static_cast<Uint8>(256 * g);
    blue = static_cast<Uint8>(256 * b);
} 


#endif