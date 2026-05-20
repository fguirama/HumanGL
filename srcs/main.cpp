#include "class/Window.hpp"
#include <iostream>

void init_sdl();
void close_sdl();
void initCube();
void drawCube();

int main() {
    int exit_val = EXIT_SUCCESS;

    try {
        init_sdl();
        Window window;
        window.init();
        window.run();
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        exit_val = EXIT_FAILURE;
    }
    close_sdl();
    return (exit_val);
}

void init_sdl() {
    if (SDL_Init(SDL_INIT_EVERYTHING))
        throw std::runtime_error(std::string("Error initialize SDL2: ") + SDL_GetError());
}

void close_sdl() { SDL_Quit(); }
