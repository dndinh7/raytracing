#ifndef SDLAPP_H
#define SDLAPP_H

#include <SDL.h>
#include "vec3.h"
#include "ray.h"
#include "color.h"


struct Image {
	double aspect_ratio= -1;
	int width= -1;
	int height= -1;

	// buffer of pixels to render to the screen
	Uint32* pixels= nullptr;
};

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


		// flag to continue rendering and displaying the window
		bool loop = true;

		Image image;
		Viewport viewport;

		// will need a width and aspect ratio, then we calculate the height
		void setupImageSize(double aspect_ratio, int width);

		// will calculate the origin and origin pixel based on focal_length and height
		void setupViewport(double focal_length, double height, vec3 camera_center= vec3(0));

		bool setupWindow();
		bool setupRenderer();
		bool setupTexture();
		void setupPixels();
		void updateTexture();

		void handleEvents();
		void render();

};




#endif SDLAPP_H