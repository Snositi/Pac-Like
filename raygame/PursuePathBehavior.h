#pragma once
#include "PathfindBehavior.h"

class PursuePathBehavior : public PathfindBehavior
{
public:
	PursuePathBehavior(Maze* maze, Actor* target) :PathfindBehavior(maze,target) {}

protected:
	virtual MathLibrary::Vector2 findDestination(Agent* owner) override;
};

