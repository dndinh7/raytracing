// raytracing.cpp : Defines the entry point for the application.
//

#include "raytracing.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"

#include <iostream>
#include <SDL.h>
#undef main

bool hit_sphere(const point3& center, double radius, const ray& r) {
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

color ray_color(const ray& r) {
    // if the ray hits the sphere, then we color it red :)
    if (hit_sphere(vec3(0, 0, -1), 0.5, r)) return color(1, 0, 0);

    // color is dependent on y value of ray, we normalize it to [0, 1]
    vec3 unit_dir = r.direction().normalize();
    double alpha = 0.5 * (unit_dir.y + 1.0);

    return vec3::lerp(color(1.0, 1.0, 1.0), color(0.5, 0.7, 1.0), alpha);
}

int calculateHeight(double aspect_ratio, int width) {
    // insight: aspect_ratio= width/height

    int height = static_cast<int>(width / aspect_ratio);

    // make sure height is never less than 1
    return height < 1 ? 1 : height;
}

int main(int argc, char* argv[]) {
    SDL_SetMainReady();

    // Change width and aspect_ratio, then we will calculate the height based on those values
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = calculateHeight(aspect_ratio, image_width);


    // Camera
    float focal_length = 1.0;

    // decrease to zoom in and increase to zoom out (FOV)
    float viewport_height = 2.0;

    // using width / height instead of aspect ratio because height is truncated to nearest ratio and it can't be less than 1
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


    // set up window
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize the SDL2 library" << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        image_width, image_height,
        SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        SDL_Quit();
        return -1;
    }

    // set up renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Could not create renderer!" << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    bool loop= true;
    SDL_Event event;
    
    while (loop) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                loop = false;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF); // Red

        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    // Render

    /*
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
    */
    std::clog << "\rDone.                          \n";

    return 0;
}
