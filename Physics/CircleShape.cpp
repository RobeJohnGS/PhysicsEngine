#include "CircleShape.h"
#include "../Engine/Graphics.h"

void CircleShape::Draw(Graphics* graphics, const glm::vec2& pos)
{
	int r = graphics->WorldToPixels(radius);

	graphics->DrawFilledCircle(graphics->WorldToScreen(pos), (int)radius, color);
}
