#pragma once
#include "Actor.h"
#include "Pac.h"

class Door : public Actor
{
public:
	Door(float x, float y, Pac* player);
	virtual void onCollision(Actor* other) override;
	Pac* m_player;
};
