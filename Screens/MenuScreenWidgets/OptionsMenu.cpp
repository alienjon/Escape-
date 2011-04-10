/*
 * OptionsMenu.cpp
 *
 *  Created on: Jul 1, 2009
 *      Author: alienjon
 */
#include "OptionsMenu.hpp"

#include "../MenuScreen.hpp"
#include "../../Managers/VideoManager.hpp"

using std::string;

OptionsMenu::OptionsMenu() : mBackButton(ID_MAINMENU_BUTTON_MAIN, EVENT_SLIDE_MAINMENU)
{
    // Add widgets to the container.
    // @todo Add widgets

    // Configure the container.
    mContainer.setBaseColor(COLOR_MENU_DARK);
    mContainer.setBackgroundColor(COLOR_MENU_LIGHT);
    mContainer.setFrameSize(2);
    mContainer.setSize(600, 350);
    add(&mContainer, 100, 150);

    // Place the back button at the bottom right of the screen.
    add(&mBackButton,
        getWidth() - mBackButton.getWidth() - 5,
        getHeight() - mBackButton.getHeight() - 5);
    mBackButton.addEventListener(this);
}

OptionsMenu::~OptionsMenu()
{
    remove(&mContainer);
    remove(&mBackButton);
    mBackButton.removeEventListener(this);
}

void OptionsMenu::eventOccurred(Event event, const string& content, CreatureMovedToPointListener* creatureMovedToPointListener)
{
    pushEvent(event, content, creatureMovedToPointListener);
}
