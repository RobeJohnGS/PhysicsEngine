#include "CircleShape.h"
#include "Graphics.h"

void CircleShape::Draw(Graphics* graphics, const glm::vec2& pos)
{
	graphics->DrawFilledCircle(pos, radius, color);
}
