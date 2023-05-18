#include "JointTest.h"
#include "CircleShape.h"
#include "World.h"
#include "Body.h"
#include "Joint.h"

#define SPRING_STIFFNESS 200
#define SPRING_LENGTH 50
#define BODY_DAMPING 10

void JointTest::Initialize()
{
	Test::Initialize();

	m_anchor = new Body(new CircleShape(20, { 1, 1, 1, 1 }), { 400, 100 }, { 0, 0 }, 0, Body::KINEMATIC);
	m_world->AddBody(m_anchor);

	auto body = new Body(new CircleShape(20, { 1, 1, 1, 1 }), { 400, 200 }, { 0, 0 }, 1, Body::DYNAMIC);
	body->gravityScale = 250;
	body->damping = BODY_DAMPING;
	m_world->AddBody(body);

	auto joint = new Joint(m_anchor, body, SPRING_STIFFNESS, SPRING_LENGTH);
	m_world->AddJoint(joint);

	auto prevBody = body;

	body = new Body(new CircleShape(20, { 1, 1, 1, 1 }), { 400, 200 }, { 0, 0 }, 1, Body::DYNAMIC);
	body->gravityScale = 250;
	body->damping = BODY_DAMPING;
	m_world->AddBody(body);

	joint = new Joint(body, prevBody, SPRING_STIFFNESS, SPRING_LENGTH);
	m_world->AddJoint(joint);
}

void JointTest::Update()
{
	Test::Update();
	m_anchor->position = m_input->GetMousePosition();
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