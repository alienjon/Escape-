/*
 * MainMenu.cpp
 *
 *  Created on: Jul 1, 2009
 *      Author: alienjon
 */
#include "MainMenu.hpp"

#include <algorithm>

#include "../MenuScreen.hpp"
#include "../../Managers/VideoManager.hpp"

using std::max;
using std::string;

MainMenu::MainMenu() :
	mStartButton(ID_MAINMENU_BUTTON_START, EVENT_SLIDE_NEWMENU),
	mOptionsButton(ID_MAINMENU_BUTTON_OPTIONS, EVENT_SLIDE_OPTIONSMENU),
	mCreditsButton(ID_MAINMENU_BUTTON_CREDITS, EVENT_SLIDE_CREDITSMENU),
	mQuitButton(ID_MAINMENU_BUTTON_QUIT, EVENT_QUIT)
{
    // This menu is see through.
    setOpaque(false);
    setFrameSize(0);

    // Listen to each button.
    mStartButton.addEventListener(this);
    mOptionsButton.addEventListener(this);
    mCreditsButton.addEventListener(this);
    mQuitButton.addEventListener(this);

    // The horizontal buffer between buttons.
    int buffer = 8;

    // Because the positions are centered, I need to set the size first.
    int width = max(mStartButton.getWidth(), mOptionsButton.getWidth());
    width = max(width, mCreditsButton.getWidth());
    width = max(width, mQuitButton.getWidth());
    add(&mStartButton, (getWidth() / 2) - (mStartButton.getWidth() / 2), (getHeight() / 2) - (mStartButton.getHeight() * 2.5));
    add(&mOptionsButton, (getWidth() / 2) - (mOptionsButton.getWidth() / 2), mStartButton.getY() + mStartButton.getHeight() + buffer);
    add(&mCreditsButton, (getWidth() / 2) - (mCreditsButton.getWidth() / 2), mOptionsButton.getY() + mOptionsButton.getHeight() + buffer);
    add(&mQuitButton, (getWidth() / 2) - (mQuitButton.getWidth() / 2), mCreditsButton.getY() + mCreditsButton.getHeight() + buffer);
}

MainMenu::~MainMenu()
{
    mStartButton.removeEventListener(this);
    mOptionsButton.removeEventListener(this);
    mCreditsButton.removeEventListener(this);
    mQuitButton.removeEventListener(this);

    remove(&mQuitButton);
    remove(&mCreditsButton);
    remove(&mOptionsButton);
    remove(&mStartButton);
}

void MainMenu::eventOccurred(Event event, const string& content, CreatureMovedToPointListener* creatureMovedToPointListener)
{
    pushEvent(event, content, creatureMovedToPointListener);
}
