#pragma once
#include "Shape.h"

class CircleShape : public Shape {
public:
	CircleShape(float radius, glm::vec4 color) : radius{ radius }, Shape{ color }{}
	virtual void Draw(Graphics* graphics, const glm::vec2& pos) override;

	float radius{ 1 };

};