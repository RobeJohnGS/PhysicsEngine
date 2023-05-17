#pragma once
#include <glm/glm.hpp>

class Body {
public:
	//matthan
	enum Type {
		STATIC,
		KINEMATIC,
		DYNAMIC
	};

	Body(class Shape* shape, const glm::vec2& pos, const glm::vec2& vel = { 0, 0 }, float mass = 1, Type type = Type::DYNAMIC) : shape{ shape }, position { pos }, velocity{ vel }, mass{ mass }, type{ type } {
		//if (type == Type::STATIC) {
		//	mass = 0;
		//}
		if (mass == 0) {
			invMass = 0;
		}
		else {
			invMass = 1 / mass;
		}
	}

	void ApplyForce(const glm::vec2& force);
	void Step(float dt);
	void Draw(class Graphics* graphics);

	void ClearForce() { force = glm::vec2{ 0, 0 }; }

	bool Intersects(class Body* body);

	//Variables
	class Shape* shape{ nullptr };

	Type type{ Type::DYNAMIC };

	glm::vec2 position{ 0, 0 };
	glm::vec2 velocity{ 0, 0 };
	glm::vec2 force{ 0, 0 };
	float mass{ 1 };
	//Inverse Mass: a = F * (1/m)
	float invMass{ 1 };

	float damping{ 3 };

	//matthan
	float gravityScale{ 1 };
};