/*
 * DisplayAnimationAction.cpp
 *
 *  Created on: May 21, 2009
 *      Author: alienjon
 */
#include "DisplayAnimationAction.hpp"

#include "../Entities/Entity.hpp"

DisplayAnimationAction::DisplayAnimationAction(Entity& entity, const Sprite& sprite, unsigned int count) : mEntity(entity),
	mSprite(sprite),
	mCount(count),
	mInfinite((mCount == 0) ? true : false)
{
}

DisplayAnimationAction::~DisplayAnimationAction()
{
    mEntity.removeAnimationCycleListener(this);
}

void DisplayAnimationAction::activate(EnvironmentData& eData)
{
    // If the action has not yet been activated, then set the initial information.
    if(!mActivated)
    {
        // Set the animation for the sprite.
        mEntity.mSetAnimation(mSprite);

        // Add this as a listener.
        mEntity.addAnimationCycleListener(this);

        // The action is activated.
        mActivated = true;
    }

    // If the animation has cycled enough times, quit.
    if(mCount == 0)
    {
        mPerformed = true;

        // If this animation is not repeating indefinitely, then stop the animation on the last frame.
        if(!mInfinite)
        {
            mEntity.setAnimating(false);
            mEntity.mSprite.setFrame(mEntity.mSprite.getNumberOfFrames() - 1);
        }
    }
}

void DisplayAnimationAction::animationCycled()
{
    mCount--;
}
