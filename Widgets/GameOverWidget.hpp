/*
 * GameOverWidget.hpp
 *
 *  Created on: Aug 6, 2009
 *      Author: alienjon
 */

#ifndef GAMEOVERWIDGET_HPP_
#define GAMEOVERWIDGET_HPP_

#include <list>
#include <string>

#include "../Listeners/CreatureMovedToPointListener.hpp"
#include "../guichan.hpp"
#include "MenuButton.hpp"

#include "../Listeners/EventListener.hpp"

/**
 * @brief A widget that tells the user that the game has ended.
 */
class GameOverWidget : public gcn::Container, public EventListener
{
    public:
    /**
     * @brief A widget that contains buttons for options to do after the player has died.
     */
    GameOverWidget();
    ~GameOverWidget();

    /**
     * @brief Add an event listener.
     * @param listener The listener to add.
     */
    virtual void addEventListener(EventListener* listener);

    /**
     * @brief An event occurred.
     * @param event The event that occurred.
     * @param content Additional content.
     * @param creatureMovedToPointListener A potential creature moved to point listener.
     */
    virtual void eventOccurred(Event event, const std::string& content = "", CreatureMovedToPointListener* creaturedMovedToPointListener = 0);

    /**
     * @brief Remove an event listener.
     * @param listener The listener to remove.
     */
    virtual void removeEventListener(EventListener* listener);

    /**
     * @brief Sets the message to explain the cause of the game over.
     * @param message The reason why the game ended.
     */
    virtual void setMessage(const std::string& message);

    private:
    /**
     * @brief Adjust the size and position of the widget.
     */
    void mAdjustSize();

    /**
     * The message box.
     */
    gcn::TextBox mMessage;

    /**
     * The buttons for the widget.
     */
    MenuButton mMenu;
    MenuButton mQuit;

    /**
     * The list of event listeners.
     */
    std::list<EventListener*> mEventListeners;
};

#endif /* GAMEOVERWIDGET_HPP_ */
