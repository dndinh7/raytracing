// raytracing.cpp : Defines the entry point for the application.
//

#include "raytracing.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"

#include <iostream>
#include "SDLApp.h"



int main(int argc, char* argv[]) {

    {
        SDLApp app;
        app.setup();
        app.update();
    }

    
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
