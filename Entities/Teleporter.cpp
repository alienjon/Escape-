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
#include "../Engine/VideoManager.hpp"

Teleporter::Teleporter(unsigned int width, unsigned int height, Level& level) ://@todo remove teleporter entirely?  If not, then how is it implemented?
	mLevel(level)
{
	mType = ENTITY_TELEPORTER;
//	mSprite.setTexture(VideoManager::getTexture(IMAGE_TELEPORTER));
//	mSprite.setOrigin(getWidth() / 2, getHeight() / 2);
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
