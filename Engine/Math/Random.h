#pragma once
#include <random>

namespace JREngine {
	inline void SeedRandom(int seed) { srand(seed); }

	inline int Random() { return rand(); }
	inline int Random(int max) { return Random() % max; }
	inline int Random(int min, int max) { return min + Random() % ((max - min) + 1); }

	inline float Randomf() { return rand() / (float)RAND_MAX; } // 0.0 - 1.0
	inline float Randomf(float max) { return Randomf() * max; } // between 0.0 and max
	inline float Randomf(float min, float max) { return min + Randomf(max - min); }
}