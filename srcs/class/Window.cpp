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
		SDL_GL_DeleteContext(this->_glContext);
		this->_glContext = nullptr;
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

	this->_glContext = SDL_GL_CreateContext(this->_window.get());
	if (!this->_glContext)
		throw std::runtime_error(std::string("Error creating GL context: ") + SDL_GetError());
	SDL_GL_MakeCurrent(this->_window.get(), this->_glContext);
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

	while (this->_running) {
		Character character;
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				this->_running = false;
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
						this->_running = false;
						break;
					case SDLK_1:
						this->_state = AnimationState::Idle;
						break;
					case SDLK_2:
						this->_state = AnimationState::Walk;
						break;
					case SDLK_3:
						this->_state = AnimationState::Jump;
						break;
					case SDLK_4:
						this->_state = AnimationState::Dance;
						break;
					default:
						break;
				}
			} else if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					this->_dragging = true;
					this->_lastMouseX = event.button.x;
				}
			} else if (event.type == SDL_MOUSEBUTTONUP) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					this->_dragging = false;
				}
			} else if (event.type == SDL_MOUSEMOTION) {
				if (this->_dragging) {
					const int dx = event.motion.x - this->_lastMouseX;
					this->_lastMouseX = event.motion.x;
					this->_cameraYaw += static_cast<float>(dx) * 0.01f;
				}
			} else if (event.type == SDL_MOUSEWHEEL) {
				if (event.wheel.y != 0) {
					this->_cameraDistance -= static_cast<float>(event.wheel.y) * 0.5f;
					if (this->_cameraDistance < 3.0f)
						this->_cameraDistance = 3.0f;
					if (this->_cameraDistance > 20.0f)
						this->_cameraDistance = 20.0f;
				}
			}
		}

		const float time_seconds = static_cast<float>(SDL_GetTicks64() - start_ticks) / 1000.0f;
		character.update(time_seconds, this->_state);

		int width = 0;
		int height = 0;
		SDL_GetWindowSize(this->_window.get(), &width, &height);

		begin_frame(width, height);

		const double aspect = width > 0 ? static_cast<double>(width) / static_cast<double>(height) : 1.0;
		constexpr double kPi = std::numbers::pi;
		Matrix4 projection = Matrix4::perspective(45.0 * (kPi / 180.0), aspect, 0.1, 100.0);
		const double cam_x = std::sin(this->_cameraYaw) * this->_cameraDistance;
		const double cam_z = std::cos(this->_cameraYaw) * this->_cameraDistance;
		Matrix4 view = Matrix4::lookAt(Vector4(cam_x, 0, cam_z), Vector4(0.0, 0.0, 0.0), Vector4(0.0, 1.0, 0.0));
		Matrix4 view_proj = projection * view;

		stack.clear();
		stack.push(identity);
		character.draw(stack, view_proj);

		SDL_GL_SwapWindow(this->_window.get());
	}

	shutdown_draw();
}
