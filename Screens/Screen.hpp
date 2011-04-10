/*
 * Screen.hpp
 *
 *  Created on: Jun 24, 2009
 *      Author: alienjon
 */

#ifndef SCREEN_HPP_
#define SCREEN_HPP_

#include <list>
#include <string>

#include "SDL/SDL.h"

#include "guichan.hpp"

#include "../Game/Game.hpp"
#include "../Game/GUI.hpp"
#include "../Game/Event.hpp"
#include "../Interfaces/EventInterface.hpp"
#include "../Listeners/EventListener.hpp"
#include "../Game/Input.hpp"
#include "../Managers/VideoManager.hpp"
#include "../Engine/Viewport.hpp"

/*
 * @brief A screen is an abstract way of looking at what's going on.
 *
 * Different screens possess different responsabilities, so that the MenuScreen will display
 *  the main menu while a *Credits screen will display credits (possibly in the form of an animation
 *  or video).
 */
class Screen : public EventListener, public EventInterface
{
    public:
    virtual ~Screen()
    {}

    /**
     * @brief Draw the screen.
     * @param renderer The renderer with which to draw.
     */
    virtual void draw(Renderer& renderer) = 0;

    /**
     * @brief Input handling.
     * @param input The input.
     * @note Should be used for non-gui input.
     */
    virtual void handleInput(const Input& input)
    {}

    /**
     * @brief Checks to see if the screen is still doing stuff.
     * @return True only if the screen has finished what it is doing.
     */
    bool isDone() const
    {
        return mDone;
    }

    /**
     * @brief Perform anything necessary to prepare this screen for displaying what it needs to.
     * @param gui The gui is provided for screen GUI management.
     */
    virtual void load(GUI* gui) = 0;

    /**
     * @brief Perform logic.
     */
    virtual void logic() = 0;

    /**
     * @brief This unloads the screen and finalizes any further actions to allow the screen to be safetly deleted.
     */
    virtual void unload() = 0;

    protected:
    Screen() :
    	mDone(false)
    {
        // All screens are the size of the (surprise surprise) screen!
        mBase.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);

        // They should not, however, draw anything superfluous to hide the root GUI widget.
        mBase.setOpaque(false);

        // Lastly, make sure the screen can receive focus.
        mBase.setFocusable(true);
    }

    /**
     * The state of the screen (false if it is still doing stuff)
     * @note This needs to be set to true when the screen has finished what it is doing (CANNOT be called in unload())
     */
    bool mDone;

    /**
     * The base widget for this screen.
     */
    gcn::Container mBase;

    /**
     * The screen's viewport (handled elsewhere).
     */
    Viewport mViewport;
};

#endif /* SCREEN_HPP_ */
