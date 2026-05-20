#include <cmath>
#include "enum.h"

float lerp(const float a, const float b, const float t) {
	return (a + (b - a) * t);
}

AnimationFrame calculateFrame(const float time_seconds, const float fps, const int frameCount) {
	float	frame = time_seconds * fps;
	frame = std::fmod(frame, static_cast<float>(frameCount));
	const int	idx0 = static_cast<int>(std::floor(frame));
	const int	idx1 = (idx0 + 1) % frameCount;
	float		t = frame - idx0;
	t = t * t * (3.0f - 2.0f * t);

	return {idx0, idx1, t};
}
