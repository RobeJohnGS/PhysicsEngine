#include "PhysicsObject.h"

PhysicsObject::~PhysicsObject()
{
	delete m_body;
	delete m_shape;
}

void PhysicsObject::Step(float dt)
{
	m_body->Step(dt);
}

void PhysicsObject::Draw(Graphics* m_graphics)
{
	m_shape->Draw(m_graphics, m_body->position);
}
