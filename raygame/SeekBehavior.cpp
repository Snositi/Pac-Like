#include "SeekBehavior.h"
#include "Maze.h"
#include "raylib.h"

void SeekBehavior::update(Agent* owner, float deltaTime)
{
	//Don't update if disabled or no target
	if (!getEnabled() || !m_target)
		return;

	MathLibrary::Vector2 position = owner->getWorldPosition();
	MathLibrary::Vector2 destination = m_target->getWorldPosition();

	//If owner is at the destination, exit
	if (position == destination)
		return;

	//Find the direction
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(destination - position);

	//Calculate the force
	MathLibrary::Vector2 desiredVelocity = direction * (owner->getMaxSpeed() * getForceScale());
	MathLibrary::Vector2 steeringForce = desiredVelocity - owner->getVelocity();

	//Apply the force
	owner->applyForce(steeringForce);
}

void SeekBehavior::draw(Agent* owner)
{
	if (m_target == nullptr || owner == nullptr)
		return;
	//draw line connecting this agent to the target
	DrawLine(owner->getWorldPosition().x ,
		owner->getWorldPosition().y,
		m_target->getWorldPosition().x,
		m_target->getWorldPosition().y,
		RED);
	//draw line to represent the steering force applied
	DrawLine(owner->getWorldPosition().x,
		owner->getWorldPosition().y,
		(owner->getWorldPosition().x) + (getSteeringForce().x),
		(owner->getWorldPosition().y) + (getSteeringForce().y),
		BLUE);
}

