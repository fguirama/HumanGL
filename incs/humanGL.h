#ifndef HUMANDGL_HUMANGL_H
# define HUMANDGL_HUMANGL_H

#include "class/Matrix4.hpp"

void init_draw();
void shutdown_draw();
void begin_frame(int width, int height);
void drawCube(const Matrix4 &mvp, const Color &color);

#endif
