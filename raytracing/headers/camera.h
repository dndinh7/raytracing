#ifndef CAMERA_H
#define CAMERA_H

#include "rt_util.h"
#include "image.h"
#include "hittable.h"
#include "color.h"
#include "settings.h"
#include "material.h"

class camera {
	public:
		point3 center = point3(0, 0, -1);

		// this will determine how many times we allow diffusing
		int max_depth = 10;

		double vfov = 90; // vertical view angle in degrees

		// point for the camera to look at
		point3 look_at = vec3(0);

		double defocus_angle = 0; // variation of angle of rays through each pixel
		double focus_dist = 10; // distance from center of camera to plane of focus

		void render(image& image, const hittable& world,
			point3 cam_pos, point3 look_pos, double v_fov,
			double defocus_ang, double focus_dis);

	private:
		vec3 u, v, w; // camera axes
		vec3 world_up = vec3(0, 1, 0);

		double viewport_width = 0; // will calculate from image width / image height ratio

		// vertical displacement from viewport origin to right edge
		vec3 viewport_u;

		// horizontal displacement from viewport origin to left edge
		vec3 viewport_v;

		// top left corner of the viewport
		vec3 viewport_origin;

		vec3 defocus_disk_u;
		vec3 defocus_disk_v;

		// sets up viewport and image origin
		void initialize(image& image);


		color ray_color(const ray& r, int depth, const hittable& world) const;

		// we will get a ray in the confines of a pixel [(p.x - 0.5, p.y - 0.5),(p.x + 0.5, p.y + 0.5)]
		ray get_sample_ray(const point3& pixel_center, const vec3& pixel_delta_u, const vec3& pixel_delta_v) const;

		// gets ray origin from the lens disk to shoot a ray to plane
		point3 defocus_disk_sample() const;

		// randomly get point in the pixel square
		vec3 get_sample_offset(const vec3& pixel_delta_u, const vec3& pixel_delta_v) const;
};


#endif