#include "PointForce.h"
#include "Body.h"

void PointForce::Apply(std::vector<class Body*> bodies)
{
	for (auto body : bodies) {
		if (!m_body->Intersects(body)) {
			continue;
		}

		glm::vec2 diretion = m_body->position - body->position;
		glm::vec2 force = glm::normalize(diretion);

		body->ApplyForce(force * m_forceMagnitude);
	}
}
