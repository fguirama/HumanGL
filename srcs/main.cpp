#include <SDL2/SDL.h>
#include <iostream>

void init_sdl();
void close_sdl();

#define WIDTH 800
#define HEIGHT 600

class Game { // todo replace and move in a class
    public:
        Game();

        void init();
        void run();
    private:
        const std::string   _title;
        std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>         _window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>         _renderer;
};


Game::Game () : _title("Open window"), _window(NULL, SDL_DestroyWindow), _renderer(NULL, SDL_DestroyRenderer) {}

void    Game::init() {
    this->_window.reset(SDL_CreateWindow(this->_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 600, 0));
    if (!this->_window) {
        throw std::runtime_error(std::string("Error creating Window: ") + SDL_GetError());
    }
    this->_renderer.reset(SDL_CreateRenderer(this->_window.get(), -1, SDL_RENDERER_ACCELERATED));
    if (!this->_renderer) {
        throw std::runtime_error(std::string("Error creating Renderer: ") + SDL_GetError());
    }
}

void    Game::run() {
    SDL_RenderClear(this->_renderer.get());
    SDL_RenderPresent(this->_renderer.get());
    SDL_Delay(5000);
}

void init_sdl() {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        throw std::runtime_error(std::string("Error initialize SDL2: ") + SDL_GetError());
    }
}

void close_sdl() { SDL_Quit(); }

int main() {
    int exit_val = EXIT_SUCCESS;

    try {
        init_sdl();
        Game game;
        game.init();
        game.run();
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        exit_val = EXIT_FAILURE;
    }
    close_sdl();
    return (exit_val);
}
