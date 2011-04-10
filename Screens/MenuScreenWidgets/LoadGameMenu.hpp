/*
 * LoadGameMenu.hpp
 *
 *  Created on: Jul 1, 2009
 *      Author: alienjon
 */

#ifndef LOADGAMEMENU_HPP_
#define LOADGAMEMENU_HPP_

#include <string>

#include "../../Listeners/CreatureMovedToPointListener.hpp"
#include "../../Game/Event.hpp"
#include "../../guichan.hpp"
#include "LoadGame/LoadGameListModel.hpp"
#include "../../Widgets/MenuButton.hpp"
#include "MenuWidget.hpp"

class MenuScreen;

/**
 * @brief The main menu widget to allow the layer to load a game.
 */
class LoadGameMenu : public MenuWidget
{
    friend class MenuScreen;

    public:
    virtual ~LoadGameMenu();

    protected:
    /**
     * @brief The load game menu.
     */
    LoadGameMenu();

    /**
     * @brief An event occurred.
     * @param event The event that occurred.
     * @param content Additional content.
     * @param creatureMovedToPointListener A potential creature moved to point listener.
     */
    virtual void eventOccurred(Event event, const std::string& content = "", CreatureMovedToPointListener* creaturedMovedToPointListener = 0);

    private:
    /**
     * The list model for the games list.
     */
    LoadGameListModel mGamesListModel;

    /**
     * The list box to display the games.
     */
    gcn::ListBox mGamesList;

    /**
     * This container holds a list of the currently available games to load.
     */
    gcn::ScrollArea mScrollArea;

    /**
     * This button loads the current game.
     */
    MenuButton mLoadButton;

    /**
     * This button returns to the main menu.
     */
    MenuButton mBackButton;
};

extern const char* ID_LOADGAME_LOAD;

#endif /* LOADGAMEMENU_HPP_ */
