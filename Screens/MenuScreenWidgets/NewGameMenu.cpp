/*
 * NewGameMenu.cpp
 *
 *  Created on: Jul 1, 2009
 *      Author: alienjon
 */
#include "NewGameMenu.hpp"

#include "../../Managers/FontManager.hpp"
#include "../../Engine/Logger.hpp"
#include "../MenuScreen.hpp"
#include "../../Managers/VideoManager.hpp"

using std::string;

NewGameMenu::NewGameMenu() :
	mEasyButton(ID_STARTGAME_EASY, EVENT_STARTEASY),
	mNormalButton(ID_STARTGAME_NORMAL, EVENT_STARTNORMAL),
	mHardButton(ID_STARTGAME_HARD, EVENT_STARTHARD),
	mUsernameLabel("Player Name: "),
	mUsernameTextbox("Bob the mailman"),
	mBackButton(ID_MAINMENU_BUTTON_MAIN, EVENT_SLIDE_MAINMENU)
{
    // Configure the username label.
    mUsernameLabel.setAlignment(gcn::Graphics::LEFT);
    mUsernameLabel.setFont(FontManager::get(FONT_MENU_HOVER));
    mUsernameLabel.adjustSize();

    // Configure the username textbox.
    mUsernameTextbox.setSize(300, 50);
    mUsernameTextbox.setFont(FontManager::get(FONT_MENU_INACTIVE));
    mUsernameTextbox.setText(mUsernameTextbox.getText());
    mUsernameTextbox.setBaseColor(getBaseColor());
    mUsernameTextbox.setBackgroundColor(COLOR_MENU_LIGHT);
    mUsernameTextbox.setFrameSize(2);

    // Position and add the buttons.
    add(&mUsernameLabel, (getWidth() / 2) - mUsernameLabel.getWidth(), 150);
    add(&mUsernameTextbox, (getWidth() / 2) + mUsernameTextbox.getFrameSize(), 150);
    add(&mEasyButton, (getWidth() / 2) - (mEasyButton.getWidth() / 2), 250);
    add(&mNormalButton, (getWidth() / 2) - (mNormalButton.getWidth() / 2), mEasyButton.getY() + mEasyButton.getHeight() + 8);
    add(&mHardButton, (getWidth() / 2) - (mHardButton.getWidth() / 2), mNormalButton.getY() + mNormalButton.getHeight() + 8);
    add(&mBackButton, getWidth() - mBackButton.getWidth() - 5, getHeight() - mBackButton.getHeight() - 5);
    mEasyButton.addEventListener(this);
    mNormalButton.addEventListener(this);
    mHardButton.addEventListener(this);
    mBackButton.addEventListener(this);
}

NewGameMenu::~NewGameMenu()
{
    remove(&mUsernameLabel);
    remove(&mUsernameTextbox);
    remove(&mEasyButton);
    remove(&mNormalButton);
    remove(&mHardButton);
    remove(&mBackButton);

    mEasyButton.removeEventListener(this);
    mNormalButton.removeEventListener(this);
    mHardButton.removeEventListener(this);
    mBackButton.removeEventListener(this);
}

void NewGameMenu::eventOccurred(Event event, const string& content, CreatureMovedToPointListener* creatureMovedToPointListener)
{
    // If we are going to start a new game but no name was provided, then warn the player but don't do anything.
    Event ev;
    string con;
    if((event == EVENT_STARTEASY   ||
        event == EVENT_STARTNORMAL ||
        event == EVENT_STARTHARD)  &&
       mUsernameTextbox.getText().empty())
    {
        ev = EVENT_DISPLAYMESSAGE;
        con = "Need to provide a name.";
    }
    else
    {
        ev = event;
        con = mUsernameTextbox.getText();
    }

    pushEvent(ev, con, creatureMovedToPointListener);
}

const char* ID_STARTGAME_EASY = "START EASY GAME";
const char* ID_STARTGAME_NORMAL = "START NORMAL GAME";
const char* ID_STARTGAME_HARD = "START HARD GAME";
