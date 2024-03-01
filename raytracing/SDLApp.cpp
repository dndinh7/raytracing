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

void SDLApp::setupWorld() {
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
}


void SDLApp::updateTexture() {
    SDL_UpdateTexture(texture, nullptr, image.pixels, image.width * 4);
}

void SDLApp::setup() {
    // change arguments to change image size
    this->setupImageSize(16.0 / 9.0, 400);

    // set up the scene of objects
    this->setupWorld();

    // this initializes camera and does an initial rendering of the scene
    camera.render(image, world);

    this->saveToPPM("lol.ppm");

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

void SDLApp::saveToPPM(const std::string& filename) {
    std::ofstream output(filename, std::ios::out);

    if (output.is_open()) {
        output << "P3\n" << image.width << ' ' << image.height << "\n255\n";

        int buffer_size = image.width * image.height;


        for (int i = 0; i < buffer_size; ++i) {
            Uint32 pixel = image.pixels[i];
            Uint8 red = pixel >> 24;
            Uint8 green= pixel >> 16;
            Uint8 blue = pixel >> 8;

            output << static_cast<unsigned int>(red) << ' ' << 
                    static_cast<unsigned int>(green) << ' ' << 
                    static_cast<unsigned int>(blue) << '\n';

        }

        output.close();
    }
}