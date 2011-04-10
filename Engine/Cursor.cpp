/*
 * Cursor.cpp
 *
 *  Created on: Sep 25, 2009
 *      Author: alienjon
 */

#include "Cursor.hpp"

#include <string>

#include "../Managers/AnimationManager.hpp"

using std::string;

const string CURSOR_KEYWORD = "CURSOR";

Cursor::Cursor()
{}

void Cursor::draw(Renderer& renderer)
{
	if(mSprite.isVisible())
	{
		mSprite.draw(renderer, mPoint.x - (mSprite.getWidth() / 2), mPoint.y - (mSprite.getHeight() / 2));
	}
}

inline bool Cursor::isVisible() const
{
	return mSprite.isVisible();
}

void Cursor::load()
{
    mSprite = Sprite(AnimationManager::get(CURSOR_KEYWORD));
}

void Cursor::logic()
{
    mSprite.logic();
}

void Cursor::setPosition(int x, int y)
{
	mPoint.x = x;
	mPoint.y = y;
}

inline void Cursor::setVisible(bool state)
{
	mSprite.setVisible(state);
}
