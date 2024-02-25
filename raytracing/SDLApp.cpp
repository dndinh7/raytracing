#include "SDLApp.h"

SDLApp::SDLApp() {}

void SDLApp::setupImageSize(double aspect_ratio, int width) {
    image.aspect_ratio = aspect_ratio;
    image.width = width;

    // aspect_ratio = width / height
    int height = static_cast<int>(width / aspect_ratio);

    // make sure that height cannot be less than 1
    image.height = height < 1 ? 1 : height;
}

void SDLApp::setupViewport(double focal_length, double height, vec3 camera_center) {
    viewport.focal_length = focal_length;

    // decrease height to zoom in and increase to zoom out (FOV)
    viewport.height = height;

    // using image width / height instead of apsect ratio b/c height may be truncated to nearest int and can't be less than 1
    float width = height * (static_cast<float>(image.width) / image.height);
    viewport.width = width;

    viewport.camera_center = camera_center;

    // Get the vectors to viewport edges
    // right is +x, up is +y, towards viewport is -z
    viewport.u = vec3(width, 0, 0);

    // negative because we are going from top to bottom
    viewport.v = vec3(0, -height, 0);

    // calculate the delta of the displacement between pixels
    viewport.pixel_du = viewport.u / image.width;
    viewport.pixel_dv = viewport.v / image.height;

    // calculate position of the origin (top left) of viewport and pixel
    viewport.origin = camera_center - vec3(0, 0, focal_length) - viewport.u / 2 - viewport.v / 2;

    // offset by the deltas to get the center of pixel
    viewport.origin_pixel = viewport.origin + 0.5 * (viewport.pixel_du, viewport.pixel_dv);
}

bool SDLApp::setupWindow() {
    window = SDL_CreateWindow("SDL2 Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        image.width, image.height,
        SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        return false;
    }

    return true;
}

bool SDLApp::setupRenderer() {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        std::cerr << "Could not create renderer!" << std::endl;
        return false;
    }

    return true;
}

bool SDLApp::setupTexture() {
    // change this value to change pixel format format (CURRENT IS RGBA)
    texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
        image.width, image.height);
    
    if (!texture) {
        std::cerr << "Could not setup texture!" << std::endl;
        return false;
    }

    return true;
}

void SDLApp::setupPixels() {
    image.pixels = new Uint32[image.width * image.height * 4];

    // create the objects in the scene
    Sphere s(point3(0, 0, -1), 0.5, vec3(1, 0, 0));

    // transparency is opaque for now
    unsigned char alpha = 255;
    
    Uint8 red = 0;
    Uint8 green = 0;
    Uint8 blue = 0;

    for (int j = 0; j < image.height; ++j) {
        for (int i = 0; i < image.width; ++i) {
            // get the position of each pixel
            point3 pixel_center = viewport.origin_pixel + (i * viewport.pixel_du) + (j * viewport.pixel_dv);
            
            // vector subtraction to get ray to the pixel center
            vec3 ray_dir = pixel_center - viewport.camera_center;

            ray r(viewport.camera_center, ray_dir);

            // get the color of the pixels
            color pixel_color = ray_color(s, r);

            convert_col_to_RGB(pixel_color, red, green, blue);

            // bit shift to place R G B A to pack them into the Uint32
            image.pixels[i + (j * image.width)] = (red << 24) | (green << 16) | (blue << 8) | alpha;

        }
    }
}

void SDLApp::updateTexture() {
    SDL_UpdateTexture(texture, nullptr, image.pixels, image.width * 4);
}

void SDLApp::setup() {
    // change arguments to change image size
    this->setupImageSize(16.0 / 9.0, 400);

    // change arguments to change FOV
    this->setupViewport(1.0, 2.0);

    // set up pixels based on image size and viewport size
    this->setupPixels();


    // set up window
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("SDL could not initialize!");
    }

    if (!setupWindow()) {
        SDL_Quit();
        throw std::runtime_error("Window could not be created!");
    }

    if (!setupRenderer()) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error("Renderer could not be created!");
    }

    if (!setupTexture()) {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        throw std::runtime_error("Texture could not be created!");
    }

    updateTexture();
}

void SDLApp::update() {
    while (loop) {
        this->handleEvents();
        this->render();
    }
}

SDLApp::~SDLApp() {
    delete[] image.pixels;
    image.pixels = nullptr;
    if (renderer) SDL_DestroyRenderer(this->renderer);
    if (window) SDL_DestroyWindow(this->window);
    if (texture) SDL_DestroyTexture(this->texture);
    SDL_Quit();
}

void SDLApp::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            loop = false;
        }
    }
}

void SDLApp::render() {



    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, texture, nullptr, nullptr);

    SDL_RenderPresent(renderer);
    
}