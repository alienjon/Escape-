/*
 * AnimatedSprite.cpp
 *
 *  Created on: Jan 31, 2013
 *      Author: alienjon
 */
#include "AnimatedSprite.hpp"

#include <cstdlib>

using std::abs;
using std::list;
using std::pair;

AnimatedSprite::AnimatedSprite(unsigned int speed) :
	mAnimationSpeed(speed)
{
	// Set the first animation frame.
	mAnimationFrame = mAnimation.begin();

	// Start the timer.
	mAnimationTimer.start();
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::mUpdatePositions()
{
	// This is a copy from SFML.
    sf::FloatRect bounds = getLocalBounds();

    mVertices[0].position = sf::Vector2f(0, 0);
    mVertices[1].position = sf::Vector2f(0, bounds.height);
    mVertices[2].position = sf::Vector2f(bounds.width, bounds.height);
    mVertices[3].position = sf::Vector2f(bounds.width, 0);
}

void AnimatedSprite::mUpdateTexCoords()
{
    float left   = static_cast<float>(mAnimationFrame->second.left);
    float right  = left + mAnimationFrame->second.width;
    float top    = static_cast<float>(mAnimationFrame->second.top);
    float bottom = top + mAnimationFrame->second.height;

    mVertices[0].texCoords = sf::Vector2f(left, top);
    mVertices[1].texCoords = sf::Vector2f(left, bottom);
    mVertices[2].texCoords = sf::Vector2f(right, bottom);
    mVertices[3].texCoords = sf::Vector2f(right, top);
}

void AnimatedSprite::addFrame(const sf::Texture& frame)
{
	addFrame(frame, sf::IntRect(0, 0, frame.getSize().x, frame.getSize().y));
}

void AnimatedSprite::addFrame(const sf::Texture& frame, const sf::IntRect& drawArea)
{
	mAnimation.push_back(pair<const sf::Texture&, sf::IntRect>(frame, drawArea));
	if(mAnimationFrame == mAnimation.end())
	{
		mAnimationFrame = mAnimation.begin();
		mUpdatePositions();
		mUpdateTexCoords();
	}
}

void AnimatedSprite::clear()
{
	// Clear the animation list.
	mAnimation.clear();

	// Reset the initial frame.
	mAnimationFrame = mAnimation.begin();
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// If the animation is empty, don't do anything.
	if(mAnimation.empty())
		return;

	// Draw the current frame.
	states.transform *= getTransform();
	states.texture = &(mAnimationFrame->first);
	target.draw(mVertices, 4, sf::Quads, states);
}

unsigned int AnimatedSprite::getAlpha() const
{
	return mAlpha;
}

unsigned int AnimatedSprite::getAnimationSpeed() const
{
	return mAnimationSpeed;
}

const sf::Color& AnimatedSprite::getColor() const
{
	return mVertices[0].color;
}

sf::FloatRect AnimatedSprite::getLocalBounds() const
{
	// This is a direct copy from SFML.
    float width = static_cast<float>(abs(mAnimationFrame->second.width));
    float height = static_cast<float>(abs(mAnimationFrame->second.height));

    return sf::FloatRect(0.f, 0.f, width, height);
}

sf::FloatRect AnimatedSprite::getGlobalBounds() const
{
	// This is a direct copy from SFML.
	return getTransform().transformRect(getLocalBounds());
}

unsigned int AnimatedSprite::getHeight() const
{
	return mAnimationFrame->second.height;
}

const sf::Texture& AnimatedSprite::getTexture() const
{
	return mAnimationFrame->first;
}

const sf::IntRect& AnimatedSprite::getTextureRect() const
{
	return mAnimationFrame->second;
}

unsigned int AnimatedSprite::getWidth() const
{
	return mAnimationFrame->second.width;
}

void AnimatedSprite::logic()
{
	// If the animation is empty, don't do anything.
	if(mAnimation.empty())
		return;

	// If the frame has finished displaying, go to the next frame.
	if(mAnimationTimer.getTime() >= mAnimationSpeed)
	{
		// Increment the animation frame and check range.
		mAnimationFrame++;
		if(mAnimationFrame == mAnimation.end())
			mAnimationFrame = mAnimation.begin();

		// Update the position information.
		mUpdatePositions();
		mUpdateTexCoords();

		// Restart the timer.
		mAnimationTimer.start();
	}
}

void AnimatedSprite::setAlpha(unsigned int alpha)
{
	mAlpha = alpha;
}

void AnimatedSprite::setAnimationSpeed(unsigned int speed)
{
	mAnimationSpeed = speed;
}

void AnimatedSprite::setColor(const sf::Color& color)
{
	mVertices[0].color = color;
	mVertices[1].color = color;
	mVertices[2].color = color;
	mVertices[3].color = color;
}
