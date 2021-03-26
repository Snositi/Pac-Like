#include "Ghost.h"
#include "Maze.h"
#include "Wall.h"
#include "raylib.h"

Ghost::Ghost(float x, float y, float maxSpeed, int color, Maze* maze)
	: Agent(x, y, Maze::TILE_SIZE / 2.5f, maxSpeed, maxSpeed, color)
{
	m_maze = maze;
}

Ghost::~Ghost()
{
	delete m_seekPathBehavior;
	delete m_wanderBehavior;
}

bool Ghost::checkTargetInSight()
{
	//check if the target is null if so return false
	if (getTarget() == nullptr)
		return false;
	//find the direction vector that represents where the target is relative to the enemy
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(getTarget()->getWorldPosition() - getWorldPosition());
	//Find the dot product of the enemy's forward and the direction vector
	float dotProduct = MathLibrary::Vector2::dotProduct(getForward(), direction);
	//Find the angle using the dot product
	float dotProductAngle = acosf(dotProduct);
	//Check if that angle is greater than the enemy's viewing angle(any value you see fit is fine) (0.523599 = 30°)
	if (dotProductAngle < m_visionAngle)
		//Return if the enemy saw the target
		return true;
	return false;
}

void Ghost::update(float deltaTime)
{
	switch (checkTargetInSight())
	{
	case false:
		getBehaviorList()[0]->setEnabled(true);
		getBehaviorList()[1]->setEnabled(false);
		break;
	case true:
		getBehaviorList()[0]->setEnabled(false);
		getBehaviorList()[1]->setEnabled(true);
		break;
	}
	Agent::update(deltaTime);
}

void Ghost::draw()
{
	if (m_seekPathBehavior->getEnabled())
		m_seekPathBehavior->draw(this);
	if (m_wanderBehavior->getEnabled())
		m_wanderBehavior->draw(this);
	Agent::draw();
}

void Ghost::onCollision(Actor* other)
{
	if (Wall* wall = dynamic_cast<Wall*>(other)) {
		MathLibrary::Vector2 halfTile = { Maze::TILE_SIZE / 2.0f, Maze::TILE_SIZE / 2.0f };
		MathLibrary::Vector2 position = getWorldPosition();
		position = position + halfTile;
		MathLibrary::Vector2 tilePosition = {
			roundf(position.x / Maze::TILE_SIZE) * Maze::TILE_SIZE,
			roundf(position.y / Maze::TILE_SIZE) * Maze::TILE_SIZE
		};
		tilePosition = tilePosition - halfTile;
		setWorldPostion(tilePosition);

		setVelocity({ 0, 0 });
	}
}

void Ghost::setTarget(Actor* target)
{
	m_target = target;
	m_seekPathBehavior->setTarget(target);
}

Actor* Ghost::getTarget()
{
	return m_target;
}
