#pragma once
inline float lerp(float a, float b, float ratio) {
	float result = a + (a - b) * ratio;
	return result;
}