#ifndef CAMERA_H
#define CAMERA_H

#include "rt_util.h"
#include "image.h"
#include "hittable.h"
#include "color.h"

class camera {
	public:

		void render(image& image, const hittable& world) {
			initialize(image);

			image.pixels = new uint32_t[image.width * image.height];

			// transparency is opaque for now
			unsigned char alpha = 255;

			Uint8 red = 0;
			Uint8 green = 0;
			Uint8 blue = 0;

			for (int j = 0; j < image.height; ++j) {
				for (int i = 0; i < image.width; ++i) {
					// get the position of each pixel
					point3 pixel_center = image.origin_pixel + (i * image.pixel_du) + (j * image.pixel_dv);

					color pixel_color = vec3(0);
					for (int k = 0; k < image.samples_per_pixel; ++k) {
						ray r = get_sample_ray(pixel_center, image.pixel_du, image.pixel_dv);
						pixel_color += this->ray_color(r, world);
					}

					convert_col_to_RGB(pixel_color, image.samples_per_pixel, red, green, blue);

					// bit shift to place R G B A to pack them into the Uint32
					image.pixels[i + (j * image.width)] = (red << 24) | (green << 16) | (blue << 8) | alpha;

				}
			}
		}

	private:
		point3 center= point3(0);

		// change this for FOV (the greater value, the more zoomed in)
		double focal_length = 1.0;

		// decrease viewport height to zoom in and increase to zoom out (FOV)
		double viewport_height = 2.0;

		double viewport_width = 0; // will calculate from image width / image height ratio

		// vertical displacement from viewport origin to right edge
		vec3 viewport_u;

		// horizontal displacement from viewport origin to left edge
		vec3 viewport_v;

		// top left corner of the viewport
		vec3 viewport_origin;

		// sets up viewport and image origin
		void initialize(image& image) {
			viewport_width = viewport_height * (static_cast<double>(image.width) / image.height);

			// set up displacements to edge of viewport
			viewport_u = vec3(viewport_width, 0, 0);
			viewport_v = vec3(0, -viewport_height, 0);

			// set up distance between two pixels
			image.pixel_du = viewport_u / image.width;
			image.pixel_dv = viewport_v / image.height;

			// setup top left of viewport
			viewport_origin = center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;

			// set up top left pixel of image
			image.origin_pixel = viewport_origin + 0.5 * (image.pixel_du + image.pixel_dv);
		}


		color ray_color(const ray& r, const hittable& world) const {
			// if the ray hits the hittable object, then we want to get the normal of that point on the object
			hit_record rec;

			if (world.intersects(r, interval(0, +infinity), rec)) {
				// map to 0 to 1
				color col = map(rec.normal, vec3(-1), vec3(1), vec3(0), vec3(1));

				return col;
			}

			// color is dependent on y value of ray, we normalize it to [0, 1]
			vec3 unit_dir = r.direction().normalize();
			double alpha = map(unit_dir.y, interval(-1, 1), interval(0, 1));

			return vec3::lerp(color(1.0, 1.0, 1.0), color(0.5, 0.7, 1.0), alpha);
		}

		// we will get a ray in the confines of a pixel [(p.x - 0.5, p.y - 0.5),(p.x + 0.5, p.y + 0.5)]
		ray get_sample_ray(const point3& pixel_center, const vec3& pixel_delta_u, const vec3& pixel_delta_v) const {
			point3 pixel_sample = pixel_center + get_sample_offset(pixel_delta_u, pixel_delta_v);

			vec3 ray_dir = pixel_sample - this->center;

			return ray(this->center, ray_dir);
		}

		vec3 get_sample_offset(const vec3& pixel_delta_u, const vec3& pixel_delta_v) const {
			vec3 du = (random_double() - 0.5) * pixel_delta_u;
			

			vec3 dv = (random_double() - 0.5) * pixel_delta_v;


			return du + dv;

		}



};


#endif