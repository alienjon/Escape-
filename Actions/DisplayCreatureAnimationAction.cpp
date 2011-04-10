/*
 * DisplayCreatureAnimationAction.cpp
 *
 *  Created on: Aug 17, 2010
 *      Author: the-saint
 */
#include "DisplayCreatureAnimationAction.hpp"

#include "../Entities/Creatures/Creature.hpp"
#include "../Engine/Sprite.hpp"

DisplayCreatureAnimationAction::DisplayCreatureAnimationAction(Creature& creature, CreatureAnimationState state, unsigned int count) :
	mCreature(creature),
	mState(state),
	mCount(count),
	mInfinite((mCount == 0) ? true : false)
{
}

DisplayCreatureAnimationAction::~DisplayCreatureAnimationAction()
{
    mCreature.removeAnimationCycleListener(this);
}

void DisplayCreatureAnimationAction::activate(EnvironmentData& eData)
{
    // If the action has not yet been activated, then set the initial information.
    if(!mActivated)
    {
        // Set the animation for the sprite.
    	mCreature.mSetAnimation(mState);

        // Add this as a listener.
        mCreature.addAnimationCycleListener(this);

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
            mCreature.setAnimating(false);
            mCreature.mSprite.setFrame(mCreature.mSprite.getNumberOfFrames() - 1);
        }
    }
}

void DisplayCreatureAnimationAction::animationCycled()
{
    mCount--;
}
