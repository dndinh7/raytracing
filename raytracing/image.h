#ifndef IMAGE_H
#define IMAGE_H

#include "vec3.h"

struct image {
	// image dimensions
	double aspect_ratio = -1;
	int width = -1;
	int height = -1;

	// pixel information
	vec3 pixel_du; // horizontal distance between pixels
	vec3 pixel_dv; // vertical distance between pixels

	point3 origin_pixel; // top leftmost pixel

	// buffer of pixels to render to the screen
	uint32_t* pixels = nullptr;
};


#endif