#pragma once
#include "Actor.h"

class Door : public Actor
{
public:
	Door(float x, float y);
	void onCollision(Actor* other) override;
};
