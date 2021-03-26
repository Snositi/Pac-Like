#pragma once
#include "SteeringBehavior.h"

class Actor;

class WanderBehavior : public SteeringBehavior
{
public:
	WanderBehavior();
	WanderBehavior(float wanderForce = 1, float radius = 1, float jitter = 1);

	MathLibrary::Vector2 calculateForce(Agent* agent) override;
	void update(Agent* agent, float deltaTime) override;
	void draw(Agent* agent) override;
private:
	//The agent that the behavior is seeking
	MathLibrary::Vector2 m_target;
	float m_radius;
	float m_jitter;
	MathLibrary::Vector2 m_randPerPos;
	MathLibrary::Vector2 m_randVecPos;
	MathLibrary::Vector2 m_normPerPos;
};