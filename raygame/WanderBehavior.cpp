#include "WanderBehavior.h"
#include "Agent.h"
#include "Actor.h"

WanderBehavior::WanderBehavior()
{
	m_target = MathLibrary::Vector2(NULL, NULL);
	setForceScale(1);
	m_jitter = 1;
}

WanderBehavior::WanderBehavior(float wanderForce,float jitter)
{
	m_target = MathLibrary::Vector2(0, 0);
	setForceScale(wanderForce);
	m_jitter = jitter;
}
void WanderBehavior::update(Agent* agent, float deltaTime)
{
	if (!agent)
		return;
	//create a random degree between 0 and 360 then converts it to radians
	float theta = (rand() / (RAND_MAX / 360)) * (3.14159265359 / 180);
	//Start with Random Target somewhere congruent with the radius of this agent
	m_randPerPos = MathLibrary::Vector2(cosf(theta) * m_radius, sinf(theta) * m_radius);
	//Add a random vector to the the Random Target with a magnitude specified by a jitter amount
	theta = (rand() / (RAND_MAX / 360)) * (3.14159265359 / 180);
	m_randVecPos = MathLibrary::Vector2(m_randPerPos.x + (cosf(theta) * m_jitter), m_randPerPos.y + (sinf(theta) * m_jitter));
	//Bring the Random Target to be congruent with the perimeter of the radius by normalizing and scaling by radius
	m_normPerPos = (m_randVecPos / m_randVecPos.getMagnitude()) * m_radius;
	//Add the agents current vector multiplied by a random distance to the random target
	theta = rand() / (RAND_MAX / 11);
	setSteeringForce(m_normPerPos + (agent->getForward() * theta) * (getForceScale() * agent->getMaxSpeed()));
	//Return the random target with the force applied
	agent->applyForce(getSteeringForce());
}

void WanderBehavior::draw(Agent* agent)
{
	//Draw Agents Radius
	DrawCircle(agent->getWorldPosition().x,
		agent->getWorldPosition().y,
		m_radius * 32,
		WHITE);
	DrawCircle(agent->getWorldPosition().x,
		agent->getWorldPosition().y,
		m_radius * 32 - 2,
		BLACK);

	//Draw Radius For Potential Final Position Vectors
	DrawCircle((agent->getWorldPosition().x) + (((getSteeringForce().x - m_normPerPos.x)) * 32),
		agent->getWorldPosition().y + ((getSteeringForce().y - m_normPerPos.y) * 32),
		m_radius * 32,
		WHITE);
	DrawCircle((agent->getWorldPosition().x) + ((getSteeringForce().x - m_normPerPos.x) * 32),
		agent->getWorldPosition().y + ((getSteeringForce().y - m_normPerPos.y) * 32),
		m_radius * 32 - 2,
		BLACK);

	//Draw a random position m_radius units away in a random direction
	DrawCircle((agent->getWorldPosition().x) + (m_randPerPos.x * 32),
		(agent->getWorldPosition().y) + (m_randPerPos.y * 32),
		2,
		RED);
	//Draw a line to show the vector applied to this random position
	DrawLine((agent->getWorldPosition().x) + (m_randPerPos.x * 32),
		(agent->getWorldPosition().y) + (m_randPerPos.y * 32),
		(agent->getWorldPosition().x) + (m_randVecPos.x * 32),
		(agent->getWorldPosition().y) + (m_randVecPos.y * 32),
		RED);
	//Draw the location of the random position after applying the vector to it
	DrawCircle((agent->getWorldPosition().x) + (m_randVecPos.x * 32),
		(agent->getWorldPosition().y) + (m_randVecPos.y * 32),
		2,
		ORANGE);
	//Draw a line to show the normalization of this position to be m_radius away
	DrawLine((agent->getWorldPosition().x) + (m_randVecPos.x * 32),
		(agent->getWorldPosition().y) + (m_randVecPos.y * 32),
		(agent->getWorldPosition().x) + (m_normPerPos.x * 32),
		(agent->getWorldPosition().y) + (m_normPerPos.y * 32),
		ORANGE);
	//Draw a the location of the random position after it has been normalized
	DrawCircle((agent->getWorldPosition().x) + (m_normPerPos.x * 32),
		(agent->getWorldPosition().y) + (m_normPerPos.y * 32),
		2,
		YELLOW);
	//Draw the vector applied to the normalized random position
	DrawLine((agent->getWorldPosition().x) + (m_normPerPos.x * 32),
		(agent->getWorldPosition().y) + (m_normPerPos.y * 32),
		(agent->getWorldPosition().x) + (getSteeringForce().x * 32),
		(agent->getWorldPosition().y) + (getSteeringForce().y * 32),
		YELLOW);
	//Draw the location of the target that the agent will wander to
	DrawCircle((agent->getWorldPosition().x) + (getSteeringForce().x * 32),
		(agent->getWorldPosition().y) + (getSteeringForce().y * 32),
		2,
		GREEN);
	//Draw the path the agent attempts to take
	DrawLine((agent->getWorldPosition().x) + (agent->getForward().x * 32),
		(agent->getWorldPosition().y) + (agent->getForward().y * 32),
		(agent->getWorldPosition().x) + (getSteeringForce().x * 32),
		(agent->getWorldPosition().y) + (getSteeringForce().y * 32),
		GREEN);
}
