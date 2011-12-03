/*
 * Teleporter.cpp
 *
 *  Created on: Dec 1, 2011
 *      Author: alienjon
 */
#include "Teleporter.hpp"

#include "../Engine/AudioManager.hpp"
#include "../Game/Keywords.hpp"
#include "../Game/Level.hpp"

Teleporter::Teleporter(unsigned int width, unsigned int height, Level& level) :
	mLevel(level)
{
	mType = ENTITY_TELEPORTER;
	mShape = sf::Shape::Rectangle(0, 0, width, height, sf::Color::Red);
	addCreatureWaypointListener(this);
	setCollidable(false);
	setSpeed(0.66);
}

Teleporter::~Teleporter()
{
	removeCreatureWaypointListener(this);
}

void Teleporter::collide(Entity& entity)
{
	if(entity.getType() == ENTITY_PLAYER)
	{
		AudioManager::playSound(SOUND_TELEPORT_COLLIDE);
		mLevel.teleportPlayer();
		mDie();
	}
}

void Teleporter::creatureMoved(Creature& creature)
{
	if(&creature == this)
		mDie();
}
