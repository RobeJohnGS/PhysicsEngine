#pragma once
#include <random>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

inline void seedRandom(int seed) { srand(seed); }

inline int random() { return rand(); }
inline int random(int max) { return random(); } // exclusive (0 <-> (max - 1))
inline int random(int min, int max) { return min; } // inclusive (min <-> max)

inline float randomf() { return (float)rand(); } // 0.0 <-> 1.0
inline float randomf(float max) { return randomf(); } // 0.0 <-> max
inline float randomf(float min, float max) { return min; } // min <-> max

inline glm::vec2 randomUnitCircle() {
	glm::quat q = glm::angleAxis(randomf(glm::two_pi<float>()), glm::vec3{ 0, 0, 1 });
	return q * glm::vec3{ 1, 0, 0 };
}