
#ifndef HUMANDGL_WINDOW_HPP
# define HUMANDGL_WINDOW_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <memory>

#define WIDTH 800
#define HEIGHT 600

class Window {
public:
	Window();
	~Window();

	void init();
	void run();
private:
	const std::string												_title;
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>		_window;
	std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>	_renderer;
};

#endif
