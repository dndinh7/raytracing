#include "SDLApp.h"

SDLApp::SDLApp() {}

void SDLApp::setupImageSize(double aspect_ratio, int width, int samples_per_pixel) {
    image.aspect_ratio = aspect_ratio;
    image.width = width;
    image.samples_per_pixel = samples_per_pixel;

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
    
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = make_shared<dielectric>(1.5);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.3);

    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.40, material_left));
    world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));
    

    /*
    auto R = cos(pi / 4);
    auto material_left = make_shared<lambertian>(color(0, 0, 1));
    auto material_right = make_shared<lambertian>(color(1, 0, 0));

    world.add(make_shared<sphere>(point3(0, -R, -1), R, material_left));
    world.add(make_shared<sphere>(point3(0,  R, -1), R, material_right));
    */
}


void SDLApp::updateTexture() {
    SDL_UpdateTexture(texture, nullptr, image.pixels, image.width * 4);
}

void SDLApp::setupSettings() {
    settings* settings = settings::getInstance();

    this->aspect_ratio = 16.0 / 9.0;
    this->image_width = 400;
    this->samples_per_pixel = 75;
    camera.max_depth = 50;

    if (!settings->getAntiAliasing()) {
        this->samples_per_pixel = 1;
    }
}

void SDLApp::setup() {
    this->setupSettings();

    // change arguments to change image size, and the number of samples for anti-aliasing
    this->setupImageSize(this->aspect_ratio, this->image_width, this->samples_per_pixel);

    // set up the scene of objects
    this->setupWorld();

    // this initializes camera and does an initial rendering of the scene
    camera.render(image, world, point3(-2, 2, 1), point3(0, 0, -1), 20, 10.0, 3.4);

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