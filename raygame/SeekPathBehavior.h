#pragma once
#include "PathfindBehavior.h"

class SeekPathBehavior : public PathfindBehavior
{
public:
	SeekPathBehavior(Maze* maze, Actor* target) :PathfindBehavior(maze, target) {}

protected:
	virtual MathLibrary::Vector2 findDestination(Agent* owner) override;
};

