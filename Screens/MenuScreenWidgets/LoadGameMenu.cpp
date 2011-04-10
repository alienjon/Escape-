/*
 * LoadGameMenu.cpp
 *
 *  Created on: Jul 1, 2009
 *      Author: alienjon
 */
#include "LoadGameMenu.hpp"

#include <string>

#include "../../Engine/Logger.hpp"
#include "../MenuScreen.hpp"
#include "../../Managers/VideoManager.hpp"

using std::string;

LoadGameMenu::LoadGameMenu() : mLoadButton(ID_LOADGAME_LOAD, EVENT_LOAD),
                               mBackButton(ID_MAINMENU_BUTTON_MAIN, EVENT_SLIDE_MAINMENU)
{
    // Configure the container.
    mScrollArea.setContent(&mGamesList);
    mScrollArea.setBaseColor(COLOR_MENU_DARK);
    mScrollArea.setBackgroundColor(COLOR_MENU_LIGHT);
    mScrollArea.setScrollPolicy(gcn::ScrollArea::SHOW_NEVER, gcn::ScrollArea::SHOW_ALWAYS);
    mScrollArea.setFrameSize(2);
    mScrollArea.setSize(600, 350);
    add(&mScrollArea, 100, 150);

    // Configure the list box.
    mGamesList.setListModel(&mGamesListModel);
    mGamesList.adjustSize();
    mGamesList.setWidth(mScrollArea.getWidth() - mScrollArea.getScrollbarWidth());
    mGamesList.setBaseColor(COLOR_MENU_DARK);
    mGamesList.setBackgroundColor(COLOR_MENU_LIGHT);

    // Add the buttons.
    add(&mLoadButton, 5, getHeight() - mLoadButton.getHeight() - 5);
    add(&mBackButton, getWidth() - mBackButton.getWidth() - 5, getHeight() - mBackButton.getHeight() - 5);
    mLoadButton.addEventListener(this);
    mBackButton.addEventListener(this);
}

LoadGameMenu::~LoadGameMenu()
{
    mLoadButton.removeEventListener(this);
    mBackButton.removeEventListener(this);

    remove(&mScrollArea);
    remove(&mLoadButton);
    remove(&mBackButton);
}

void LoadGameMenu::eventOccurred(Event event, const string& content, CreatureMovedToPointListener* creatureMovedToPointListener)
{
    // If the action is to load the requested game, then create a new action event and push that to the listeners.
    if(event == EVENT_LOAD)
    {
        // Make sure that an entry is currently selected.
    	//@todo implement loading/saving games.
    	Logger::warn("Loading and saving games not yet implemented.");
//        int i = mGamesList.getSelected();
//        if(i < 0 || i > mGamesListModel.getNumberOfElements())
//        {
//            pushEvent(event, DIR_SAVEDGAME + mGamesListModel.getElementAt(i));
//        }
    }
    else
    {
        pushEvent(event, content, creatureMovedToPointListener);
    }
}

const char* ID_LOADGAME_LOAD = "LOAD GAME";
