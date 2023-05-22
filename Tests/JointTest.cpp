#include "JointTest.h"
#include "../Physics/CircleShape.h"
#include "../Physics/World.h"
#include "../Physics/Body.h"
#include "../Physics/Joint.h"

#define SPRING_STIFFNESS 100
#define SPRING_LENGTH 0.5
#define BODY_DAMPING 1
#define CHAIN_SIZE 3

void JointTest::Initialize()
{
	Test::Initialize();

	m_anchor = new Body(new CircleShape(10, { 1, 1, 1, 1 }), { 0, 0 }, { 0, 0 }, 0, Body::KINEMATIC);
	m_world->AddBody(m_anchor);

	auto prevBody = m_anchor;

	auto body = new Body(new CircleShape(5, { 1, 1, 1, 1 }), { 0, 0 }, { 0, 0 }, 1, Body::DYNAMIC);
	body->damping = BODY_DAMPING;
	m_world->AddBody(body);

	auto joint = new Joint(prevBody, body, SPRING_STIFFNESS, SPRING_LENGTH);
	m_world->AddJoint(joint);

	
	for (int i = 0; i < CHAIN_SIZE; i++) {
		prevBody = body;

		auto body = new Body(new CircleShape(5, { 1, 1, 1, 1 }), { 0, 0 }, { 0, 0 }, 1, Body::DYNAMIC);
		body->damping = BODY_DAMPING;
		m_world->AddBody(body);

		auto joint = new Joint(prevBody, body, SPRING_STIFFNESS, SPRING_LENGTH);
		m_world->AddJoint(joint);

	}
}

void JointTest::Update()
{
	Test::Update();
	m_anchor->position = m_graphics->ScreenToWorld(m_input->GetMousePosition());
}

void JointTest::FixedUpdate()
{
	m_world->Step(m_time->GetFixedDeltaTime());
}

void JointTest::Render()
{
	m_world->Draw(m_graphics);
	m_graphics->DrawCircle(m_input->GetMousePosition(), 10, { randomf(), randomf(), randomf(), 1 });
}