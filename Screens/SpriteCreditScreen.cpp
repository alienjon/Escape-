/*
 * SpriteCreditScreen.cpp
 *
 *  Created on: Jun 24, 2009
 *      Author: alienjon
 */
#include "SpriteCreditScreen.hpp"

#include <stdexcept>

#include "../Game/Game.hpp"
#include "../Engine/Renderer.hpp"

using std::logic_error;

SpriteCreditScreen::SpriteCreditScreen(const Sprite& sprite,
                                       unsigned int displayTime,
                                       unsigned int fadeIn,
                                       unsigned int fadeOut) : mSprite(sprite),
	mFadeColor(0, 0, 0, (fadeIn > 0) ? 255 : 0),
	mFadeInDuration(fadeIn),
	mDisplayDuration(displayTime),
	mFadeOutDuration(fadeOut),
	mCurrentAction(SPRITESCREEN_FADE_IN)
{
}

void SpriteCreditScreen::draw(Renderer& renderer)
{
    mSprite.draw(renderer, (mSprite.getWidth() / 2) - (SCREEN_WIDTH / 2),
						   (mSprite.getHeight() / 2) - (SCREEN_HEIGHT / 2));

    // Draw the transparency.
    if(mFadeColor.a != 0)
    {
    	renderer.setColor(mFadeColor);
    	renderer.fillRectangle(mBase.getDimension());
    }
}

void SpriteCreditScreen::eventOccurred(Event event, const std::string& content, CreatureMovedToPointListener* creatureMovedToPointListener)
{
    pushEvent(event, content, creatureMovedToPointListener);
}

void SpriteCreditScreen::handleInput(const Input& input)
{
	if(Game::isDebug() && (input.isKeyPressed(SDLK_SPACE) || input.isMousePressed(SDL_BUTTON_LEFT)))
	{
		mCurrentAction = SPRITESCREEN_FADE_OUT;
	}
}

void SpriteCreditScreen::load(GUI* gui)
{
	// @note Nothing to load for this screen.
	(void)gui;

    // Start the timer.
    mTimer.start();

    // Show the cursor.
    SDL_ShowCursor(false);
}

void SpriteCreditScreen::logic()
{
    // Determine and perform the current action for this screen.
    switch(mCurrentAction)
    {
        case SPRITESCREEN_FADE_IN:
        {
            // If the image has faded in completely, then just display that image for a while.
            if(mFadeColor.a <= 0 || mFadeInDuration <= 0)
            {
                // ... start the pause time.
                mCurrentAction = SPRITESCREEN_DISPLAY_PAUSE;
                mTimer.start();
            }
            else
            {
                // Increment the alpha, if it has not already reached 0.
                int temp = 255 * (float(mALPHA_RATE) / float(mFadeInDuration));
                mFadeColor.a = (mFadeColor.a - temp > 0) ? mFadeColor.a - temp : 0;
            }

            break;
        }
        case SPRITESCREEN_DISPLAY_PAUSE:
        {
            // If the timer has exceeded the display pause time ...
            if(mTimer.getTime() >= mDisplayDuration)
            {
                // ... start fading out and restart the timer.
                mCurrentAction = SPRITESCREEN_FADE_OUT;
                mTimer.start();
            }
            break;
        }
        case SPRITESCREEN_FADE_OUT:
        {
            // Just fade out until the image has disappeared.
            if(mFadeColor.a >= 255 || mFadeOutDuration <= 0)
            {
                // Stop altogether.
                mCurrentAction = SPRITESCREEN_NULL;
                mDone = true;
            }
            else
            {
                // Decrement the alpha.
                int temp = 255 * (float(mALPHA_RATE) / float(mFadeOutDuration));
                mFadeColor.a = (mFadeColor.a + temp < 255) ? mFadeColor.a + temp : 255;
            }
            break;
        }
        default:
        {
            throw logic_error("SpriteCreditScreen::logic() -> logic called after the screen finished fading out.");
        }
    }
}

void SpriteCreditScreen::unload()
{
}

const unsigned int SpriteCreditScreen::mALPHA_RATE = 25;
