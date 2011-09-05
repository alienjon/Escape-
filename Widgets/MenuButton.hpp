/*
 * MenuButton.hpp
 *
 *  Created on: Jul 1, 2009
 *      Author: alienjon
 */

#ifndef MENUBUTTON_HPP_
#define MENUBUTTON_HPP_

#include <list>
#include <string>

#include "../guichan.hpp"

#include "../Game/Event.hpp"
#include "../Listeners/EventListener.hpp"

/**
 * @brief An in-game button.
 */
class MenuButton : public gcn::Label, public gcn::KeyListener, public gcn::MouseListener, public gcn::FocusListener
{
    public:
    /**
     * @brief A MenuButton is a button for the game's menus.  It has an enabled and a disabled image.
     * @param button The name of the button (also acts as the button's action event id so that listeners know which button was pressed)
     * @param event The event to perform when this button is pressed.
     */
    MenuButton(const std::string& name, Event event);
    virtual ~MenuButton();

    /**
     * @brief Add an event listener.
     * @param listener The event listener.
     */
    virtual void addEventListener(EventListener* listener);

    /**
     * @brief Draw the button.
     * @param graphics The graphics object with which to draw.
     */
    virtual void draw(gcn::Graphics* graphics);

    /**
     * @brief The button has gained focus.
     * @param event The focus event.
     */
    virtual void focusGained(gcn::Event& event);

    /**
     * @brief The button has lost focus.
     * @param event The focus event.
     */
    virtual void focusLost(gcn::Event& event);

    /**
     * @brief The mouse is now over the widget.
     * @param mouseEvent The mouse event.
     */
    virtual void mouseEntered(gcn::MouseEvent& mouseEvent);

    /**
     * @brief The mouse is now off the widget.
     * @param mouseEvent The mouse event.
     */
    virtual void mouseExited(gcn::MouseEvent& mouseEvent);

    /**
     * @brief A mouse button was pressed.
     * @param mouseEvent The mouse event.
     */
    virtual void mousePressed(gcn::MouseEvent& mouseEvent);

    /**
     * @brief A mouse button was released.
     * @param mouseEvent The mouse event.
     */
    virtual void mouseReleased(gcn::MouseEvent& mouseEvent);

    /**
     * @brief A key was pressed.
     * @param keyEvent The key event.
     */
    virtual void keyPressed(gcn::KeyEvent& keyEvent);

    /**
     * @brief A key was released.
     * @param keyEvent The key event.
     */
    virtual void keyReleased(gcn::KeyEvent& keyEvent);

    /**
     * @brief Remove an event listener.
     * @param listener The listener to remove.
     */
    virtual void removeEventListener(EventListener* listener);

    /**
     * @brief Set the event to perform when this button is pressed.
     * @param event The event to set.
     */
    virtual void setEvent(Event event);

    /**
     * @brief Set this button's state to hover.
     */
    virtual void setHover();

    /**
     * @brief Set this button's state to inactive.
     */
    virtual void setInactive();

    /**
     * @brief Set this button's state to pressed.
     */
    virtual void setPressed();

    protected:
    /**
     * @brief Tell the listeners that an event occurred.
     */
    virtual void mPushEvent();

    private:
    /**
     * The enabled and disabled images.
     */
    gcn::Font* mInactiveFont;
    gcn::Font* mHoverFont;
    gcn::Font* mPressedFont;

    /**
     * The event to perform when the button is pressed.
     */
    Event mEvent;

    /**
     * The list of event listeners.
     */
    std::list<EventListener*> mEventListeners;
};

#endif /* MENUICON_HPP_ */
