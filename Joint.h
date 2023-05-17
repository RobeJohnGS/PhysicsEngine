#pragma once
//weed

class Joint {
public:
	Joint(class Body* bodyA, class Body* bodyB, float stiff, float restLength = 0);

	void Step(float dt);
	void Draw(class Graphics* graphics);

protected:
	float m_restLength{ 0 };
	float m_kStiffness{ 0 };

	class Body* m_bodyA = nullptr;
	class Body* m_bodyB = nullptr;
};