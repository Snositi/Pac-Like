#include "Door.h"
#include "Maze.h"

Door::Door(float x, float y): Actor(x, y, Maze::TILE_SIZE / 2.0f, 0, 0x3333CCFF)
{
	setStatic(true);
}

void Door::onCollision(Actor* other)
{
	if(other->getWorldPosition().x > 28 * 32)

}
