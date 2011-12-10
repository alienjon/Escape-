/*
 * AlphaCycleAction.cpp
 *
 *  Created on: Dec 6, 2011
 *      Author: alienjon
 */
#include "AlphaCycleAction.hpp"

AlphaCycleAction::AlphaCycleAction(sf::Drawable& drawable) :
	mDrawable(drawable),
	mIsAddingAlpha(false)
{

}

void AlphaCycleAction::activate(Level& level)
{
mPerformed = true;//@todo how long should the alpha cycle last? (set a listener for it?)
//	// If the alpha level has maxed out, then switch directions.
//	if(mIsAddingAlpha && mDrawable.GetColor().a == 255)
//		mIsAddingAlpha = false;
//	else if(!mIsAddingAlpha && mDrawable.GetColor().a == 0)
//		mIsAddingAlpha = true;
//
//	// Change the alpha.
//	sf::Color c = mDrawable.GetColor();
//	c.a += (mIsAddingAlpha) ? 1 : -1;
//	mDrawable.SetColor(c);
}
