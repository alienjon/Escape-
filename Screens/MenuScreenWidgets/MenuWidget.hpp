/*
 * MenuWidget.hpp
 *
 *  Created on: Jul 1, 2009
 *      Author: alienjon
 */

#ifndef MENUWIDGET_HPP_
#define MENUWIDGET_HPP_

#include <list>

#include "../../Listeners/CreatureMovedToPointListener.hpp"
#include "../../Engine/Colors.hpp"
#include "../../Game/Event.hpp"
#include "../../guichan.hpp"
#include "../../Listeners/EventListener.hpp"
#include "../../Managers/VideoManager.hpp"

class MenuScreen;

/**
 * @brief A base class for a main menu widget.
 */
class MenuWidget : public gcn::Container, public EventListener
{
    public:
    virtual ~MenuWidget()
    {}

    /**
     * @brief Add an event listener.
     * @param listener The listener to add.
     */
    virtual void addEventListener(EventListener* listener)
    {
        mEventListeners.push_back(listener);
    }

    /**
     * @brief Tell any listeners that an event occurred
     * @param event The event that occurred.
     * @param content Additional content that may be needed with the event.
     */
    virtual void pushEvent(Event event, const std::string& content = "", CreatureMovedToPointListener* creatureMovedToPointListener = 0)
    {
        for(std::list<EventListener*>::iterator it = mEventListeners.begin(); it != mEventListeners.end(); ++it)
        {
            (*it)->eventOccurred(event, content, creatureMovedToPointListener);
        }
    }

    /**
     * @brief Remove an event listener.
     * @param listener The listener to remove.
     */
    virtual void removeEventListener(EventListener* listener)
    {
        mEventListeners.remove(listener);
    }

    protected:
    /**
     * @brief Defines properties common to all menu widgets.
     */
    MenuWidget()
    {
        // All menu's have the same base color.
        setBaseColor(COLOR_MENU_DARK);

        // Set the size to the size of one screen.
        setSize(SCREEN_WIDTH, SCREEN_HEIGHT);

        // Set other basic attributes.
        setOpaque(false);
    }

    /**
     * This widget's event listeners.
     */
    std::list<EventListener*> mEventListeners;
};

#endif /* MENUWIDGET_HPP_ */
