#ifndef HUMANGL_ENUM_H
# define HUMANGL_ENUM_H

enum Axis {
	X,
	Y,
	Z,
};

enum class AnimationState {
	Idle,
	Walk,
	Jump,
	Dance
};

struct AnimationFrame {
	int idx0;
	int idx1;
	float t;
};

#endif