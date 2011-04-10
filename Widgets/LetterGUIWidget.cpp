/*
 * LetterGUIWidget.cpp
 *
 *  Created on: Aug 19, 2009
 *      Author: alienjon
 */

#include "LetterGUIWidget.hpp"

#include "../Managers/AnimationManager.hpp"
#include "../Entities/Non-Creatures/Letter.hpp"

using std::string;

LetterGUIWidget::LetterGUIWidget()
{
    // Listen to the sprite for animation cycling.
    addAnimationCycleListener(this);

    // Initially invisible.
    setVisible(false);
}

LetterGUIWidget::~LetterGUIWidget()
{
    // Remove this widget as a listener.
    removeAnimationCycleListener(this);
}

void LetterGUIWidget::animationCycled()
{
    // Finished showing the image, hide the widget and stop animating.
    setVisible(false);

    // Stop animating.
    mSprite.setAnimating(false);

}

void LetterGUIWidget::letterReceived()
{
    // Show the widget.
    setVisible(true);

    // Set the sprite to the correct animation.
// @todo need to implement letters    setSprite(AnimationManager::getGameAnimation(GAMEANIMATIONTYPE_LETTER_RECEIVED));

    // Start the animation from the first position.
    mSprite.setAnimating(true);
}
