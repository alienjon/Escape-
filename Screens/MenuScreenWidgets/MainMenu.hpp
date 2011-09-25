/*
 * MainMenu.hpp
 *
 *  Created on: Jul 1, 2009
 *      Author: alienjon
 */

#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_

#include <string>

#include "../../Listeners/CreatureMovedToPointListener.hpp"
#include "../../Game/Event.hpp"
#include "../../guichan.hpp"
#include "../../Widgets/MenuButton.hpp"
#include "MenuWidget.hpp"

/**
 * @brief The main menu widget provides access to every other main menu widget on the main menu screen.
 */
class MainMenu : public MenuWidget
{
    public:
    /**
     * @brief A menu to allow the user to traverse to other menus.
     */
    MainMenu();
    virtual ~MainMenu();

    /**
     * @brief An event occurred.
     * @param event The event that occurred.
     * @param content Additional content.
     * @param creatureMovedToPointListener A potential creature moved to point listener.
     */
    virtual void eventOccurred(Event event, const std::string& content = "", CreatureMovedToPointListener* creaturedMovedToPointListener = 0);

    private:
    /**
     * The buttons to traverse to the various menus.
     */
    MenuButton mStartButton;
    MenuButton mOptionsButton;
    MenuButton mCreditsButton;
    MenuButton mQuitButton;
};

#endif /* MAINMENU_HPP_ */
