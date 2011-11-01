/*
 * Cursor.cpp
 *
 *  Created on: Sep 25, 2009
 *      Author: alienjon
 */
#include "Cursor.hpp"

#include <string>

#include "../Engine/Colors.hpp"

using std::string;

Cursor::Cursor()
{}

void Cursor::draw(Renderer& renderer)//@todo how is the cursor handled.
{
	renderer.setColor(COLOR_WHITE);
	renderer.drawPoint(mPoint.x, mPoint.y);
//	if(mSprite.isVisible())
//	{
//		mSprite.draw(renderer, mPoint.x - (mSprite.getWidth() / 2), mPoint.y - (mSprite.getHeight() / 2));
//	}
}

inline bool Cursor::isVisible() const
{
	return mSprite.isVisible();
}

void Cursor::load()
{
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
