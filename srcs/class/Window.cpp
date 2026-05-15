#include "class/Window.hpp"

// CONSTRUCTOR - DESTRUCTOR ---------------------------------------------------
Window::Window() : _title("Open window"), _window(NULL, SDL_DestroyWindow), _renderer(NULL, SDL_DestroyRenderer) {}

Window::~Window() {}


// METHDO ---------------------------------------------------------------------
void	Window::init() {
	this->_window.reset(SDL_CreateWindow(this->_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 600, 0));
	if (!this->_window) {
		throw std::runtime_error(std::string("Error creating Window: ") + SDL_GetError());
	}
	this->_renderer.reset(SDL_CreateRenderer(this->_window.get(), -1, SDL_RENDERER_ACCELERATED));
	if (!this->_renderer) {
		throw std::runtime_error(std::string("Error creating Renderer: ") + SDL_GetError());
	}
}

void	Window::run() {
	SDL_RenderClear(this->_renderer.get());
	SDL_RenderPresent(this->_renderer.get());
	SDL_Delay(5000);
}
