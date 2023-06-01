#include "World.h"
#include "ForceGenerator.h"
#include "Body.h"
#include "Joint.h"
#include "Collision.h"
#include <vector>

glm::vec2 World::gravity{ 0, -9.81f };

World::~World()
{
	for (auto object : m_bodies) {
		delete object;
	}

	m_bodies.clear();
}

void World::Step(float dt)
{
	
	std::vector<Body*> bodies(m_bodies.begin(), m_bodies.end());
	if (m_bodies.empty()) {
		return;
	}
	if (!m_bodies.empty() && !m_forces.empty()) {
		for (auto forces : m_forces) {
			forces->Apply(bodies);
		}
	}

	for (auto joint : m_joints) {
		joint->Step(dt);
	}

	for (auto body : m_bodies) {
		body->Step(dt);
	}

	std::vector<Contact> contacts;
	Collision::CreateContacts(bodies, contacts);
	Collision::SeparateContacts(contacts);
	Collision::ResolveContacts(contacts);

}

void World::Draw(Graphics* graphics)
{
	//draws the joints
	for (auto joint : m_joints) {
		joint->Draw(graphics);
	}
	//draws the force generator circles
	for (auto forceGen : m_forces) {
		forceGen->Draw(graphics);
	}
	for (auto body : m_bodies) {
		body->Draw(graphics);
	}
}

void World::AddBody(Body* po)
{
	m_bodies.push_back(po);
}

void World::RemoveBody(Body* po)
{
	m_bodies.remove(po);
}

void World::AddForceGenerator(ForceGenerator* forceGenerator)
{
	m_forces.push_back(forceGenerator);
}

void World::AddJoint(Joint* joint)
{
	m_joints.push_back(joint);
}

void World::RemoveJoint(Joint* joint)
{
	m_joints.remove(joint);
}
