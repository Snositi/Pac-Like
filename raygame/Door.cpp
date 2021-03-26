#include "Door.h"
#include "Maze.h"

Door::Door(float x, float y, Pac* player): Actor(x, y, Maze::TILE_SIZE / 2.0f, 0, 0x3333CCFF)
{
	setStatic(false);
	m_player = player;
	setColor(11614112);
}

 void Door::onCollision(Actor* other)
{	 
	if (other == m_player)
	{
		if (m_player->getWorldPosition().x > 28 * 32)
		{
			m_player->setDesiredTransitions(1);
			m_player->setShouldTransition(true);
			m_player->setWorldPostion({m_player->getWorldPosition().x - 32, m_player->getWorldPosition().y});
			m_player->setVelocity({ -1 * m_player->getVelocity().getMagnitude(),0 });
		}
		else if (m_player->getWorldPosition().x < 0 * 32)
		{
			m_player->setDesiredTransitions(-1);
			m_player->setShouldTransition(true);
			m_player->setWorldPostion({ m_player->getWorldPosition().x + 32, m_player->getWorldPosition().y });
				m_player->setVelocity({ m_player->getVelocity().getMagnitude(),0 });
		}
	}
}
