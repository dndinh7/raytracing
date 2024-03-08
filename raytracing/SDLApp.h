#ifndef SDLAPP_H
#define SDLAPP_H

#include <SDL.h>
#include <fstream>
#include "color.h"
#include "hittable_list.h"
#include "hittable.h"
#include "sphere.h"
#include "camera.h"
#include "rt_util.h"
#include "image.h"
#include "settings.h"
#include "material.h"




struct Viewport {
	float focal_length= -1;
	float height= -1;
	float width= -1;
	vec3 camera_center;
	vec3 u; // displacement to the right edge of viewport
	vec3 v; // displacement to the bottom edge of viewport

	// distance between pixels on image (delta pixel)
	vec3 pixel_du; // left to right
	vec3 pixel_dv; // top to bottom

	// upper left of viewport (0,0,-focal_length)
	vec3 origin;

	// pixel on the upper left
	point3 origin_pixel;
};

class SDLApp {
	public:
		SDLApp();
		~SDLApp();

		void setup();
		void update();
	private:
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		SDL_Texture* texture = nullptr;

		// initial settings for setup
		double aspect_ratio= 16.0 / 9.0;
		double image_width= 400;
		int samples_per_pixel= 75;

		camera camera;

		// objects in the world
		hittable_list world;

		// flag to continue rendering and displaying the window
		bool loop = true;

		image image;
		Viewport viewport;

		// will need a width and aspect ratio, then we calculate the height
		void setupImageSize(double aspect_ratio, int width, int samples_per_pixel);


		bool setupWindow();
		bool setupRenderer();
		bool setupTexture();
		void updateTexture();
		void setupWorld();
		void setupSettings();

		void handleEvents();
		void render();

		void saveToPPM(const std::string& filename= "default.ppm");

};




#endif