/*
 * Phase.cpp
 *
 *  Created on: Dec 4, 2011
 *      Author: alienjon
 */
#include "Phase.hpp"

#include "../Entities/Creature.hpp"
#include "../Game/Keywords.hpp"
#include "../Game/Level.hpp"
#include "../Engine/VideoManager.hpp"

Phase::Phase(Level& level) :
	mLevel(level)
{
	mType = ENTITY_PHASE;
	mSprite = sf::Sprite(VideoManager::getTexture(IMAGE_ITEM_PHASE));
	mSprite.setOrigin(getWidth() / 2, getHeight() / 2);
}

void Phase::mPerform(Creature& creature)
{
	mLevel.phaseCreature(creature);
}

const std::string& Phase::getImageFilename() const
{
	return IMAGE_ITEM_PHASE;
}
