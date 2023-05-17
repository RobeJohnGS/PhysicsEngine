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

	static glm::vec2 gravity;


private:
	std::list<Body*> m_bodies;
	std::vector<class ForceGenerator*> m_forces;
};