/*
 * Nullify.cpp
 *
 *  Created on: Dec 10, 2011
 *      Author: alienjon
 */
#include "Nullify.hpp"

#include "../Entities/Creature.hpp"
#include "../Game/Keywords.hpp"
#include "../Game/Level.hpp"
#include "../Engine/VideoManager.hpp"

Nullify::Nullify(Level& level) :
	mLevel(level)
{
	mType = ENTITY_NULLIFY;
	mSprite.addFrame(VideoManager::getTexture(IMAGE_ITEM_NULLIFY));
	mSprite.setOrigin(getWidth() / 2, getHeight() / 2);
}

void Nullify::mPerform(Creature& creature)
{
	mLevel.nullify(creature);
}

const std::string& Nullify::getImageFilename() const
{
	return IMAGE_ITEM_NULLIFY;
}
