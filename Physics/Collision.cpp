#include "Collision.h"
#include "CircleShape.h"
#include "../Engine/Random.h"

namespace Collision
{
	void CreateContacts(std::vector<Body*> bodies, std::vector<Contact>& contacts)
	{
		for (size_t i = 0; i < bodies.size() - 1; i++)
		{
			for (size_t j = i + 1; j < bodies.size(); j++)
			{
				Body* bodyA = bodies[i];
				Body* bodyB = bodies[j];

				// contact needs at least one dynamic body
				if (bodyA->type != Body::DYNAMIC && bodyB->type != Body::DYNAMIC) continue;

				// check for intersection between bodies
				if (bodyA->Intersects(bodyB))
				{
					// create contact
					Contact contact = Collision::GenerateContact(bodyA, bodyB);
					contacts.push_back(contact);
				}
			}
		}
	}

	Contact GenerateContact(Body* bodyA, Body* bodyB)
	{
		Contact contact;

		contact.bodyA = bodyA;
		contact.bodyB = bodyB;

		glm::vec2 direction = bodyA->position - bodyB->position;
		float distance = glm::length(direction);
		if (distance == 0)
		{
			direction = { randomf(-0.05f, 0.05f), randomf(-0.05f, 0.05f) };
		}

		float radius = ((CircleShape*)bodyA->shape)->radius + ((CircleShape*)bodyB->shape)->radius;
		contact.depth = radius - distance;

		contact.normal = glm::normalize(direction);
		contact.restitution = (bodyA->restitution + bodyB->restitution) * 0.5f;

		return contact;
	}

	void SeparateContacts(std::vector<Contact>& contacts)
	{
		for (auto& contact : contacts)
		{
			float totalInvMass = contact.bodyA->invMass + contact.bodyB->invMass;
			glm::vec2 separation = contact.normal * (contact.depth / totalInvMass);

			contact.bodyA->position += separation * contact.bodyA->invMass;
			contact.bodyB->position -= separation * contact.bodyB->invMass;
		}
	}
	
	void ResolveContacts(std::vector<Contact>& contacts)
	{
		for (auto& contact : contacts)
		{
			glm::vec2 relativeVelocity = contact.bodyA->velocity - contact.bodyB->velocity;
			float normalVelocity = glm::dot(relativeVelocity, contact.normal);
			if (normalVelocity > 0) {
				continue;
			}
			float invMassA = (contact.bodyA->type == Body::DYNAMIC) ? contact.bodyA->invMass : 0;
			float invMassB = (contact.bodyB->type == Body::DYNAMIC) ? contact.bodyB->invMass : 0;
			float totalInverseMass = invMassA + invMassB;
			float impulseMagnitude = -((1 + contact.restitution) * normalVelocity) / totalInverseMass;
			glm::vec2 impulse = contact.normal * impulseMagnitude;
			contact.bodyA->velocity += (impulse * ((invMassA != 0) ? contact.bodyA->mass : 0));
			contact.bodyB->velocity += -(impulse * ((invMassB != 0) ? contact.bodyB->mass : 0));
		}
	}
}