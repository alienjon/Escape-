/*
 * Portal.cpp
 *
 *  Created on: Oct 27, 2011
 *      Author: alienjon
 */
#include "Portal.hpp"

#include "../Game/Keywords.hpp"
#include "../Game/Level.hpp"
#include "../Engine/VideoManager.hpp"

using std::list;
using std::pair;

const float PORTAL_ANIMATION_STEP = 0.2f;

Portal::Portal(unsigned int width, unsigned int height) ://@todo width and height may not be used any longer.  Evaluate after animation is complete
	mWidth(width),
	mHeight(height),
	mStartRadius(0.f)
{
	mType = ENTITY_PORTAL;
	setCollidable(false);
	mSprite.addFrame(VideoManager::getTexture(IMAGE_PORTAL));
	mSprite.setOrigin(getWidth() / 2, getHeight() / 2);
	mTimer.start();
}

void Portal::addLock(sf::Color color)
{
	pair<sf::Color, float> p;
	p.first  = color;
	p.second = mStartRadius;
	mStartRadius += 10.f;
	mLocks.push_back(p);
}

void Portal::collide(Entity& entity)
{
	// If the player collides with the portal and all the locks are removed, end the level.
	if(entity.getType() == ENTITY_PLAYER && mLocks.empty())
		distributeLevelComplete();
}

void Portal::draw(sf::RenderWindow& renderer)
{
	Entity::draw(renderer);
//	for(list<pair<sf::Color, float> >::iterator it = mLocks.begin(); it != mLocks.end(); ++it)@todo review if I want this
//	{
//		sf::CircleShape shape(mWidth / 2, 32);// getX() + (mWidth / 2), getY() + (mHeight / 2), it->second - 5, it->first, 5, it->first);
//		renderer.draw(shape);
//	}
}

void Portal::logic(Level& level)//@todo how do I want the colors to display (animation) on the portal?
{
	if(mTimer.getTime() >= 10)
	{
		for(list<pair<sf::Color, float> >::iterator it = mLocks.begin(); it != mLocks.end(); ++it)
		{
			it->second += PORTAL_ANIMATION_STEP;
			if(it->second >= mWidth)
				it->second = 0;
		}
		mTimer.start();
	}
}

void Portal::removeLock(sf::Color color)
{
	for(list<pair<sf::Color, float> >::iterator it = mLocks.begin(); it != mLocks.end(); ++it)
		if(it->first == color)
		{
			mLocks.erase(it);
			break;
		}
	mStartRadius -= 0.5f;
}
