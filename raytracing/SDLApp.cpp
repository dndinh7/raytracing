#include "SDLApp.h"

SDLApp::SDLApp() {}

void SDLApp::setupImage(double aspect_ratio, int width) {
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
    texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
        image.width, image.height);
    
    if (!texture) {
        std::cerr << "Could not setup texture!" << std::endl;
        return false;
    }

    return true;
}

void SDLApp::setup() {
    // change arguments to change image size
    this->setupImage(16.0 / 9.0, 400);

    // change arguments to change FOV
    this->setupViewport(1.0, 2.0);


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
}

void SDLApp::update() {
    while (loop) {
        this->handleEvents();
        this->render();
    }
}

SDLApp::~SDLApp() {
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

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF); // Red

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
    
}