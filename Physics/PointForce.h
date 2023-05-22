#pragma once
#include <vector>
#include "ForceGenerator.h"

class PointForce : public ForceGenerator {
public:
	PointForce(class Body* body, float forceMag) : ForceGenerator{ body }, m_forceMagnitude{ forceMag } {}

	virtual void Apply(std::vector<class Body*> bodies) override;
	
protected:
	float m_forceMagnitude{ 1 };
};