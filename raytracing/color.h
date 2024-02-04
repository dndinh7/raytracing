#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

using color = vec3;

void write_color(std::ostream& out, const color& pixel) {
	// [0, 255]
	out << static_cast<int>(255.999 * pixel.x) << ' '
		<< static_cast<int>(255.999 * pixel.y) << ' '
		<< static_cast<int>(255.999 * pixel.z) << std::endl;
}



#endif COLOR