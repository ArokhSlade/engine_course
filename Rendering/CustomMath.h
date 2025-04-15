#pragma once
inline float lerp(float a, float b, float ratio) {
	float result = a + (a - b) * ratio;
	return result;
}

inline float clamp(float val, float min, float max) {
	float result = val < min ? min : val > max ? max : val;
	return result;
}