// raytracing.cpp : Defines the entry point for the application.
//

#include "raytracing.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"

#include <iostream>

color ray_color(const ray& r) {
    vec3 unit_dir = r.direction().normalize();
    double alpha = 0.5 * (unit_dir.y + 1.0);
    return vec3::lerp(color(1.0, 1.0, 1.0), color(0.5, 0.7, 1.0), alpha);
}

int main() {
    // Image

    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = image_height < 1 ? 1 : image_height;

    // Camera

    float focal_length = 1.0;
    float viewport_height = 2.0;
    float viewport_width = viewport_height * (static_cast<float>(image_width) / image_height);
    vec3 camera_center = point3(0);

    // Get the vectors to viewport edges
    // right is +x, up is +y, towards viewport is -z
    vec3 viewport_u = vec3(viewport_width, 0, 0);

    // negative because the we are going from top to bottom
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    // calculate width and length of each pixel (delta pixel)
    vec3 pixel_du = viewport_u / image_width;
    vec3 pixel_dv = viewport_v / image_height;

    // calculate position of upper left pixel p00
    vec3 viewpoint_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    point3 pixel00_loc = viewpoint_upper_left + 0.5 * (pixel_du + pixel_dv); // offset by the half the size to get the mid point of pixel


    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n"; 

    for (int j = 0; j < image_height; ++j) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            point3 pixel_center = pixel00_loc + (i * pixel_du) + (j * pixel_dv);
            vec3 ray_dir = pixel_center - camera_center;
            ray r(camera_center, ray_dir); // ray from camera to each pixel

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                          \n";
}
