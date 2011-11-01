/*
 * SpriteCreditScreen.hpp
 *
 *  Created on: Jun 24, 2009
 *      Author: alienjon
 */
#ifndef SPRITECREDITSCREEN_HPP_
#define SPRITECREDITSCREEN_HPP_

#include <string>

#include "../Game/GUI.hpp"
#include "../Engine/Renderer.hpp"
#include "Screen.hpp"
#include "../Engine/Sprite.hpp"
#include "../Engine/Timer.hpp"

/**
 * @brief A screen that only displays a single sprite and is intended for credits.
 */
class SpriteCreditScreen : public Screen
{
    public:
    /**
     * @brief Displays a sprite on the screen for a period of time.
     * @param sprite This will show a single framed animation (a single image).
     * @param displayTime The amount of time to display the sprite.
     * @param fadeIn The length of time to fade in the sprite.
     * @param fadeOut The length of time to fade out the sprite.
     */
    SpriteCreditScreen(const Sprite& surface, unsigned int displayTime, unsigned int fadeIn = 0, unsigned int fadeOut = 0);

    /**
     * @brief Input handling.
     * @param input The input.
     * @note Should be used for non-gui input.
     */
    virtual void handleInput(const Input& input);

    /**
     * @brief The logic function.
     */
    virtual void logic();

    /**
     * @brief Draw the screen.
     * @param renderer The graphics object with which to draw.
     */
    virtual void draw(Renderer& renderer);

    /**
     * @brief Perform anything necessary to prepare this screen for displaying what it needs to.
     * @param gui The gui object.
     */
    virtual void load(GUI* gui);

    /**
     * @brief This unloads the screen and finalizes any further actions to allow the screen to be safetly deleted.
     */
    virtual void unload();

    protected:
    /**
     * The widget to display the image.
     */
    Sprite mSprite;

    /**
     * The fade out color.
     */
    gcn::Color mFadeColor;

    /**
     * The timer for the screen's various events.
     */
    Timer mTimer;

    /**
     * The times for the various events.
     */
    const unsigned int mFadeInDuration;
    const unsigned int mDisplayDuration;
    const unsigned int mFadeOutDuration;

    /**
     * The rate at which the image is shown or hidden.
     */
    static const unsigned int mALPHA_RATE;

    /**
     * The various actions the Trust Screen performs.
     */
    enum SpriteScreenAction
    {
        SPRITESCREEN_NULL,
        SPRITESCREEN_FADE_IN,
        SPRITESCREEN_DISPLAY_PAUSE,
        SPRITESCREEN_FADE_OUT
    };

    /**
     * The current action this screen is performing.
     */
    SpriteScreenAction mCurrentAction;
};

#endif /* SPRITECREDITSCREEN_HPP_ */
