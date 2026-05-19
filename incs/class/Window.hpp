
#ifndef HUMANDGL_WINDOW_HPP
# define HUMANDGL_WINDOW_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include "class/Character.hpp"

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
	SDL_GLContext													_glContext = nullptr;
	bool															_running = false;
	AnimationState													_state = AnimationState::Idle;
	// TODO AI --------
	float															_cameraDistance = 8.0f;
	float															_cameraYaw = 0.0f;
	bool															_dragging = false;
	int																_lastMouseX = 0;
	// TODO ENDOF AI --------
};

#endif
