#include <GL/glew.h>
#include <array>
#include <iostream>
#include "class/Color.hpp"
#include "class/Matrix4.hpp"

namespace {
	GLuint g_program = 0;
	GLuint g_vao = 0;
	GLuint g_vbo = 0;
	GLint g_mvp_location = -1;
	GLint g_color_location = -1;
}

GLuint	compile_shader(const GLenum type, const char* source) {
	const GLuint	shader = glCreateShader(type);
	GLint			status = 0;

	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		char	log[512];

		glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
		std::cerr << "Shader compile error: " << log << std::endl;
	}
	return (shader);
}

GLuint	create_program() {
	const char* vertex_src =
		"#version 410 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"uniform mat4 uMVP;\n"
		"void main() {\n"
		"    gl_Position = uMVP * vec4(aPos, 1.0);\n"
		"}\n";

	const char* fragment_src =
		"#version 410 core\n"
		"out vec4 FragColor;\n"
		"uniform vec3 uColor;\n"
		"void main() {\n"
		"    FragColor = vec4(uColor, 1.0);\n"
		"}\n";

	const GLuint	vs = compile_shader(GL_VERTEX_SHADER, vertex_src);
	const GLuint	fs = compile_shader(GL_FRAGMENT_SHADER, fragment_src);
	const GLuint	program = glCreateProgram();
	GLint			status = 0;

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		char	log[512];

		glGetProgramInfoLog(program, sizeof(log), nullptr, log);
		std::cerr << "Program link error: " << log << std::endl;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
	return (program);
}

void init_draw() {
	g_program = create_program();
	g_mvp_location = glGetUniformLocation(g_program, "uMVP");
	g_color_location = glGetUniformLocation(g_program, "uColor");

	constexpr std::array<float, 108> cube = {{
		-0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f,

		 0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f
	}};

	glGenVertexArrays(1, &g_vao);
	glGenBuffers(1, &g_vbo);

	glBindVertexArray(g_vao);
	glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cube.size(), cube.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void	shutdown_draw() {
	if (g_vbo) {
		glDeleteBuffers(1, &g_vbo);
		g_vbo = 0;
	}
	if (g_vao) {
		glDeleteVertexArrays(1, &g_vao);
		g_vao = 0;
	}
	if (g_program) {
		glDeleteProgram(g_program);
		g_program = 0;
	}
}

void	begin_frame(const int width, const int height) {
	const Color c = Color("#030303");

	glViewport(0, 0, width, height);
	glClearColor(c.getRed(), c.getGreen(), c.getBlue(), 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void drawCube(const Matrix4 &mvp, const Color &color) {
	float	mvp_data[16];
	mvp.toFloatArray(mvp_data);

	glUseProgram(g_program);
	glUniformMatrix4fv(g_mvp_location, 1, GL_TRUE, mvp_data);
	glUniform3f(g_color_location, color.getRed(), color.getGreen(), color.getBlue());

	glBindVertexArray(g_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}
