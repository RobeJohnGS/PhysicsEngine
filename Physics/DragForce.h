#pragma once
#include "ForceGenerator.h"

class DragForce : public ForceGenerator {
public:
	DragForce(class Body* body, float dragAmt) : ForceGenerator{ body }, m_drag{ dragAmt } {}

	void Apply(std::vector<class Body*> bodies) override;

private:
	float m_drag{ 0 };
};