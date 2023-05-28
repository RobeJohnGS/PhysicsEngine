#include "JointTest.h"
#include "../Physics/CircleShape.h"
#include "../Physics/World.h"
#include "../Physics/Body.h"
#include "../Physics/Joint.h"
//#define CHAIN // Will Be Used To Turn Chain On/Off To Make Chain Or Grid

#define SPRING_STIFFNESS 100
#define SPRING_LENGTH	 1
#define BODY_DAMPING	 5
#define CHAIN_SIZE		 3

void JointTest::Initialize()
{
	Test::Initialize();

	m_anchor = new Body(new CircleShape(1, { 1, 1, 1, 1 }), { 0, 0 }, { 0, 0 }, 0, Body::KINEMATIC);
	m_world->AddBody(m_anchor);


#if defined(CHAIN) // Use This For Chain

	auto prevBody = m_anchor; // Anchor
	// chain
	for (int i = 0; i < CHAIN_SIZE; i++) // Make To Desired Size
	{
		auto body = new Body(new CircleShape(0.5f, { 1, 1, 1, 1 }), { 0, 0 }, { 0, 0 }, 1, Body::DYNAMIC); // New Body
		body->damping = BODY_DAMPING; // Set Damping
		m_world->AddBody(body); // Put In World

		auto joint = new Joint(prevBody, body, SPRING_STIFFNESS, SPRING_LENGTH); // Attach To Chain
		m_world->AddJoint(joint); // Give Joint

		prevBody = body; // Set New Body To PrevBody For Next Iteration
	}

#else // Use This For Grid

	Body* prevBodyA = nullptr; // One Side
	Body* prevBodyB = nullptr; // Other Side
	Joint* joint = nullptr; // Adjoining Joint

	for (int i = 0; i < CHAIN_SIZE; i++) // Make To Desired Size
	{
		// Set Up One Body
		auto bodyA = new Body(new CircleShape(20, { 1, 1, 1, 1 }), { 350, 200 }, { 0, 0 }, 1, Body::DYNAMIC);
		bodyA->gravityScale = 150;
		bodyA->damping = BODY_DAMPING;
		m_world->AddBody(bodyA);

		// Set Up Other Body
		auto bodyB = new Body(new CircleShape(20, { 1, 1, 1, 1 }), { 450, 200 }, { 0, 0 }, 1, Body::DYNAMIC);
		bodyB->gravityScale = 150;
		bodyB->damping = BODY_DAMPING;
		m_world->AddBody(bodyB);

		// Connect With Joint
		joint = new Joint(bodyA, bodyB, SPRING_STIFFNESS, SPRING_LENGTH);
		m_world->AddJoint(joint);

		// If Size Is Zero
		if (i == 0)
		{
			joint = new Joint(m_anchor, bodyA, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint);

			joint = new Joint(m_anchor, bodyB, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint);
		}
		else // If Greater Than Zero, Connect Bodies With Numerous Joints
		{
			joint = new Joint(prevBodyA, bodyA, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint);

			joint = new Joint(prevBodyA, bodyB, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint);

			joint = new Joint(prevBodyB, bodyB, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint);

			joint = new Joint(prevBodyB, bodyA, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint);
		}

		// Move Current Bodies To PrevBodies
		prevBodyA = bodyA;
		prevBodyB = bodyB;
	}

#endif // fin
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