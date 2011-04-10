/*
 * DisplaySpriteAction.cpp
 *
 *  Created on: Aug 14, 2009
 *      Author: alienjon
 */

#include "DisplaySpriteAction.hpp"

#include <stdexcept>

using std::invalid_argument;

DisplaySpriteAction::DisplaySpriteAction(const Sprite& sprite, const Vector& loc, gcn::Container* container, unsigned int loops) : mSprite(sprite),
                                                                                                                                   mPoint(loc),
                                                                                                                                   mContainer(container),
                                                                                                                                   mSpriteWidget(sprite),
                                                                                                                                   mCounter(loops)
{
    // Make sure the container was provided.
    if(!mContainer)
    {
        throw invalid_argument("DisplaySpriteAction::DisplaySpriteAction() -> Null container provided.");
    }
}

DisplaySpriteAction::~DisplaySpriteAction()
{
    // Stop listening.
    mSprite.removeAnimationCycleListener(this);

    // Ensure to remove the sprite widget from the correct object.
    mContainer->remove(&mSpriteWidget);
}

void DisplaySpriteAction::activate(EnvironmentData& eData)
{
    // If not activated, then this is the first run.
    if(!mActivated)
    {
        // Add the sprite widget to the container.
        mContainer->add(&mSpriteWidget, mPoint.x, mPoint.y);

        // Start listening to the sprite.
        mSprite.addAnimationCycleListener(this);
    }

    // If the counter is zero, we are done.
    if(mCounter == 0)
    {
        mPerformed = true;
    }
}

void DisplaySpriteAction::animationCycled()
{
    mCounter = ((int)mCounter - 1 <= 0) ? 0 : mCounter - 1;
}
