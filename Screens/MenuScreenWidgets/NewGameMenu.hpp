/*
 * NewGameMenu.hpp
 *
 *  Created on: Jul 1, 2009
 *      Author: alienjon
 */

#ifndef NEWGAMEMENU_HPP_
#define NEWGAMEMENU_HPP_

#include <string>

#include "../../Listeners/CreatureMovedToPointListener.hpp"
#include "../../Game/Event.hpp"
#include "../../guichan.hpp"
#include "../../Widgets/MenuButton.hpp"
#include "MenuWidget.hpp"

class MenuScreen;

/**
 * @brief A main menu widget to allow the player to start a new game.
 */
class NewGameMenu: public MenuWidget
{
    // Only the menu screen should be able to create a new game menu (or derivitive classes)
    friend class MenuScreen;

    public:
    virtual ~NewGameMenu();

    protected:
    /**
     * @brief Menu allowing the player to start a new game.
     */
    NewGameMenu();

    /**
     * @brief An event occurred.
     * @param event The event that occurred.
     * @param content Additional content.
     * @param creatureMovedToPointListener A potential creature moved to point listener.
     */
    virtual void eventOccurred(Event event, const std::string& content = "", CreatureMovedToPointListener* creaturedMovedToPointListener = 0);

    private:
    /**
     * The start buttons.
     */
    MenuButton mEasyButton;
    MenuButton mNormalButton;
    MenuButton mHardButton;

    /**
     * The username label.
     */
    gcn::Label mUsernameLabel;

    /**
     * The username text-box.
     */
    gcn::TextField mUsernameTextbox;

    /**
     * The back button.
     */
    MenuButton mBackButton;
};

extern const char* ID_STARTGAME_EASY;
extern const char* ID_STARTGAME_NORMAL;
extern const char* ID_STARTGAME_HARD;

#endif /* NEWGAMEMENU_HPP_ */
