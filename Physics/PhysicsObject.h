#pragma once
#include "Body.h"
#include "Shape.h"
#include "../Engine/Graphics.h"

class PhysicsObject
{
public:

	PhysicsObject(Body* body, Shape* shape) : m_body{ body }, m_shape{ shape } {}
	~PhysicsObject();

	void Step(float dt);
	void Draw(Graphics* m_graphics);


	Body* GetBody() { return m_body; }
	Shape* GetShape() { return m_shape; }

protected:

	Body* m_body{ nullptr };
	Shape* m_shape{ nullptr };

};
