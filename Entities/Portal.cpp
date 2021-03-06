/*
 * Portal.cpp
 *
 *  Created on: Oct 27, 2011
 *      Author: alienjon
 */
#include "Portal.hpp"

#include "../Game/Keywords.hpp"
#include "../Engine/VideoManager.hpp"

using std::list;

Portal::Portal() :
	mIsLocked(true)
{
	mType = ENTITY_PORTAL;
	setCollidable(false);
	mSprite.addFrame(VideoManager::getTexture(IMAGE_PORTAL));
	mSprite.setOrigin(getWidth() / 2, getHeight() / 2);
}

void Portal::collide(Entity& entity)
{
	// If the player collides with the portal and all the locks are removed, end the level.
	if(entity.getType() == ENTITY_PLAYER && !mIsLocked)
		distributeLevelComplete();
}

void Portal::keyPickedUp()
{
	mIsLocked = false;
}
