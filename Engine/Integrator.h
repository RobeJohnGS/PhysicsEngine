#pragma once
#include "../Physics/Body.h"
namespace Integrator {
	void ExplicitEuler(Body& body, float dt);
	void SemiImplicitEuler(Body& body, float dt);
}