#include "class/Window.hpp"
#include "class/MatrixStack.hpp"
#include <GL/glew.h>
#include <cmath>
#include <stdexcept>

// CONSTRUCTOR - DESTRUCTOR ---------------------------------------------------
Window::Window()
	: _title("HumanGL"), _window(nullptr, SDL_DestroyWindow) {}

Window::~Window() {
	if (this->_glContext) {
		SDL_GL_DeleteContext(_glContext);
		_glContext = nullptr;
	}
}


// METHOD ---------------------------------------------------------------------
void	Window::init() {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	this->_window.reset(SDL_CreateWindow(
		this->_title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE));
	if (!this->_window)
		throw std::runtime_error(std::string("Error creating Window: ") + SDL_GetError());

	_glContext = SDL_GL_CreateContext(this->_window.get());
	if (!_glContext)
		throw std::runtime_error(std::string("Error creating GL context: ") + SDL_GetError());
	SDL_GL_MakeCurrent(this->_window.get(), _glContext);
	SDL_GL_SetSwapInterval(1);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw std::runtime_error("Error initializing GLEW.");

	init_draw();
}

void	Window::run() {
	MatrixStack	stack;
	Matrix4		identity;
	identity.identity();
	this->_running = true;

	const Uint64 start_ticks = SDL_GetTicks64();

	while (_running) {
		Character character;
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				_running = false;
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						_running = false;
						break;
					case SDLK_1:
						_state = AnimationState::Idle;
						break;
					case SDLK_2:
						_state = AnimationState::Walk;
						break;
					case SDLK_3:
						_state = AnimationState::Jump;
						break;
					default:
						break;
				}
			} else if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					_dragging = true;
					_lastMouseX = event.button.x;
				}
			} else if (event.type == SDL_MOUSEBUTTONUP) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					_dragging = false;
				}
			} else if (event.type == SDL_MOUSEMOTION) {
				if (_dragging) {
					const int dx = event.motion.x - _lastMouseX;
					_lastMouseX = event.motion.x;
					_cameraYaw += static_cast<float>(dx) * 0.01f;
				}
			} else if (event.type == SDL_MOUSEWHEEL) {
				if (event.wheel.y != 0) {
					_cameraDistance -= static_cast<float>(event.wheel.y) * 0.5f;
					if (_cameraDistance < 3.0f)
						_cameraDistance = 3.0f;
					if (_cameraDistance > 20.0f)
						_cameraDistance = 20.0f;
				}
			}
		}

		const float time_seconds = static_cast<float>(SDL_GetTicks64() - start_ticks) / 1000.0f;
		character.update(time_seconds, _state);

		int width = 0;
		int height = 0;
		SDL_GetWindowSize(_window.get(), &width, &height);

		begin_frame(width, height);

		const double aspect = width > 0 ? static_cast<double>(width) / static_cast<double>(height) : 1.0;
		constexpr double kPi = std::numbers::pi;
		Matrix4 projection = Matrix4::perspective(45.0 * (kPi / 180.0), aspect, 0.1, 100.0);
		const double cam_x = std::sin(_cameraYaw) * _cameraDistance;
		const double cam_z = std::cos(_cameraYaw) * _cameraDistance;
		Matrix4 view = Matrix4::lookAt(Vector4(cam_x, 2.5, cam_z), Vector4(0.0, 1.0, 0.0), Vector4(0.0, 1.0, 0.0));
		Matrix4 view_proj = projection * view;

		stack.clear();
		stack.push(identity);
		character.draw(stack, view_proj);

		SDL_GL_SwapWindow(this->_window.get());
	}

	shutdown_draw();
}
