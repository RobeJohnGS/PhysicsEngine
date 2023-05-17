#pragma once
#include "PhysicsObject.h"
#include <list>
#include <vector>
#include <glm/glm.hpp>

class World {
public:
	~World();

	void Step(float dt);
	void Draw(class Graphics* graphics);

	void AddBody(Body* po);
	void RemoveBody(Body* po);

	void AddForceGenerator(class ForceGenerator* forceGenerator);

	void AddJoint(class Joint* joint);
	void RemoveJoint(class Joint* joint);

	static glm::vec2 gravity;


private:
	std::list<Body*> m_bodies;
	std::list<class Joint*> m_joints;
	std::vector<class ForceGenerator*> m_forces;
};