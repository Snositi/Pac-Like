#pragma once
#include "Behavior.h"
#include <Vector2.h>

class SteeringBehavior : public Behavior
{
public:
	virtual MathLibrary::Vector2 calculateForce(Agent* agent) = 0;
	virtual float getForceScale() { return m_forceScale; }
	virtual float setForceScale(float value) { m_forceScale = value; return m_forceScale; }
private:
	float m_forceScale = 1;
};