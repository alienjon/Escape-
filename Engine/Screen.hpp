/*
 * Screen.hpp
 *
 *  Created on: Jun 24, 2009
 *      Author: alienjon
 */
#ifndef SCREEN_HPP_
#define SCREEN_HPP_

#include <SFML/Graphics.hpp>

#include "../Interfaces/EventInterface.hpp"
#include "../Listeners/EventListener.hpp"
#include "../Listeners/InputListener.hpp"
#include "../Engine/Logger.hpp"
#include "../Engine/RendererContext.hpp"
#include "../Engine/RendererContextInterface.hpp"

/*
 * @brief A screen is an abstract way of looking at what's going on.
 */
class Screen : public EventInterface, public EventListener, public InputListener
{
    public:
    virtual ~Screen()
    {}

    /**
     * @brief An action occurred.
     * @param actionId The action ID.
     */
    virtual void action(const std::string& actionId)
    {}

    /**
     * @brief Draw the screen.
     * @param renderer The renderer with which to draw.
     */
    virtual void draw(sf::RenderWindow& renderer) = 0;

    /**
     * @brief Checks to see if the screen is still doing stuff.
     * @return True only if the screen has finished what it is doing.
     */
    inline bool isDone() const
    {
        return mDone;
    }

    /**
     * @brief Handle input.
     * @param event The input event.
     * @return True if the event was consumed (used).
     */
    virtual bool handleInput(const sf::Event& event) = 0;

    /**
     * @brief Perform anything necessary to prepare this screen for displaying what it needs to.
     * @param view The view in which the screen is displayed.
     */
    virtual void load(const sf::View& view) {};

    /**
     * @brief Perform logic.
     * @param delta The time since the last frame displayed.
     */
    virtual void logic(int delta) = 0;

    /**
     * @brief Set the currently used context interface.
     * @param contextInterface The currently used context interface.
     */
    inline void setRendererContextInterface(RendererContextInterface* contextInterface)
    {
    	mContextInterface = contextInterface;
    }

    /**
     * @brief This unloads the screen and finalizes any further actions to allow the screen to be safetly deleted.
     */
    virtual void unload(){};

    protected:
    /**
     * @brief Construct a screen.
     * @note You need to call setSize() or setWidth()/setHeight() prior to using the screen.
     */
    Screen() :
    	mDone(false),
    	mContextInterface(0)
    {
    }

    /**
     * The state of the screen (false if it is still doing stuff)
     * @note This needs to be set to true when the screen has finished what it is doing (CANNOT be called in unload())
     */
    bool mDone;

    // The context interface.
    RendererContextInterface* mContextInterface;
};

#endif /* SCREEN_HPP_ */
