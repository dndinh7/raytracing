#include "camera.h"

void camera::render(image& image, 
					const hittable& world,
					point3 cam_pos = vec3(0, 0, -1), point3 look_pos = vec3(0),
					double v_fov = 90, double defocus_ang = 10.0, double focus_dis = 10.0) {
	
	this->center = cam_pos;
	this->look_at = look_pos;
	this->vfov = v_fov;
	this->defocus_angle = defocus_ang;
	this->focus_dist = focus_dis;


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
			// if anti-aliasing turned off then we only get the ray to the center
			if (!settings::getInstance()->getAntiAliasing()) {
				vec3 ray_dir = pixel_center - this->center;
				ray r(this->center, ray_dir);

				pixel_color = this->ray_color(r, max_depth, world);
			}
			else {
				for (int k = 0; k < image.samples_per_pixel; ++k) {
					ray r = get_sample_ray(pixel_center, image.pixel_du, image.pixel_dv);
					pixel_color += this->ray_color(r, max_depth, world);
				}
			}

			convert_col_to_RGB(pixel_color, image.samples_per_pixel, red, green, blue);

			// bit shift to place R G B A to pack them into the Uint32
			image.pixels[i + (j * image.width)] = (red << 24) | (green << 16) | (blue << 8) | alpha;

		}
	}
}

void camera::initialize(image& image) {

	// given the fov, we can calculate the viewport height
	double theta = degrees_to_rad(vfov);
	double h = focus_dist * tan(theta / 2);

	double viewport_height = 2 * h;

	viewport_width = viewport_height * (static_cast<double>(image.width) / image.height);

	// forward camera axis
	this->w = (center - look_at).normalize();

	// right camera axis (note we are doing up cross z since z is "backwards")
	this->u = vec3::cross(world_up, this->w).normalize();

	// up camera axis (similarly, z cross x cause z is "backwards")
	this->v = vec3::cross(this->w, this->u);


	// set up displacements to edge of viewport
	viewport_u = viewport_width * this->u;

	// top to bottom
	viewport_v = viewport_height * -this->v;

	// set up distance between two pixels
	image.pixel_du = viewport_u / image.width;
	image.pixel_dv = viewport_v / image.height;

	// setup top left of viewport
	viewport_origin = center - (focus_dist * this->w) - viewport_u / 2 - viewport_v / 2;

	// set up top left pixel of image
	image.origin_pixel = viewport_origin + 0.5 * (image.pixel_du + image.pixel_dv);

	// calculate defocus disk basis vectors
	double defocus_theta = degrees_to_rad(defocus_angle / 2);
	double defocus_radius = focus_dist * tan(defocus_theta);
	this->defocus_disk_u = this->u * defocus_radius;
	this->defocus_disk_v = this->v * defocus_radius;
}

color camera::ray_color(const ray& r, int depth, const hittable& world) const {
	if (depth <= 0) return color(0);

	// if the ray hits the hittable object, then we want to get the normal of that point on the object
	hit_record rec;

	// slightly offset to account for floating point error that might hit the same surface again
	if (world.intersects(r, interval(0.001, +infinity), rec)) {
		ray scattered;
		color attenuation;

		// if the point hit is of material that can scatter, then we'll continue diffusing light
		if (rec.mat->scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, depth - 1, world);

		// if there is no scattering, then we return black (no light)
		return color(0);
	}

	// background color is dependent on y value of ray, we normalize it to [0, 1]
	vec3 unit_dir = r.direction().normalize();
	double alpha = map(unit_dir.y, interval(-1, 1), interval(0, 1));

	return vec3::lerp(color(1.0, 1.0, 1.0), color(0.5, 0.7, 1.0), alpha);
}

ray camera::get_sample_ray(const point3& pixel_center, const vec3& pixel_delta_u, const vec3& pixel_delta_v) const {
	point3 pixel_sample = pixel_center + get_sample_offset(pixel_delta_u, pixel_delta_v);

	point3 ray_origin = (this->defocus_angle <= 0) ? center : defocus_disk_sample();
	vec3 ray_dir = pixel_sample - ray_origin;
	double time = random_double();	

	return ray(ray_origin, ray_dir, time);
}

point3 camera::defocus_disk_sample() const {
	vec3 p = vec3::random_in_unit_disk();
	return center + (p.x * this->defocus_disk_u) + (p.y * this->defocus_disk_v);
}

vec3 camera::get_sample_offset(const vec3& pixel_delta_u, const vec3& pixel_delta_v) const {
	vec3 du = (random_double() - 0.5) * pixel_delta_u;

	vec3 dv = (random_double() - 0.5) * pixel_delta_v;

	return du + dv;
}