///*
// * NewGameMenu.cpp
// *
// *  Created on: Jul 1, 2009
// *      Author: alienjon
// */
//#include "NewGameMenu.hpp"
//
//#include "../../Managers/FontManager.hpp"
//#include "../../Game/Keywords.hpp"
//#include "../../Engine/Logger.hpp"
//#include "../MenuScreen.hpp"
//#include "../../Managers/VideoManager.hpp"
//
//NewGameMenu::NewGameMenu() :
//	mEasyButton(ID_STARTGAME_EASY),
//	mNormalButton(ID_STARTGAME_NORMAL),
//	mHardButton(ID_STARTGAME_HARD),
//	mUsernameLabel("Player Name: "),//@todo remove the username stuff
//	mUsernameTextbox("Bob the mailman"),
//	mBackButton(ID_MAINMENU_BUTTON_MAIN)
//{
//    // Configure the username label.
//    mUsernameLabel.setAlignment(gcn::Graphics::LEFT);
//    mUsernameLabel.setFont(FontManager::get(FONT_MENU_HOVER));
//    mUsernameLabel.adjustSize();
//
//    // Configure the username textbox.
//    mUsernameTextbox.setSize(300, 50);
//    mUsernameTextbox.setFont(FontManager::get(FONT_MENU_INACTIVE));
//    mUsernameTextbox.setText(mUsernameTextbox.getText());
//    mUsernameTextbox.setBaseColor(getBaseColor());
//    mUsernameTextbox.setBackgroundColor(COLOR_MENU_LIGHT);
//    mUsernameTextbox.setFrameSize(2);
//
//    // Configure the action ids.
//    mEasyButton.setActionEventId(ACTION_STARTGAME_EASY);
//    mNormalButton.setActionEventId(ACTION_STARTGAME_NORMAL);
//    mHardButton.setActionEventId(ACTION_STARTGAME_HARD);
//    mBackButton.setActionEventId(ACTION_SLIDE_MAINMENU);
//
//    // Position and add the buttons.
//    add(&mUsernameLabel, (getWidth() / 2) - mUsernameLabel.getWidth(), 150);
//    add(&mUsernameTextbox, (getWidth() / 2) + mUsernameTextbox.getFrameSize(), 150);
//    add(&mEasyButton, (getWidth() / 2) - (mEasyButton.getWidth() / 2), 250);
//    add(&mNormalButton, (getWidth() / 2) - (mNormalButton.getWidth() / 2), mEasyButton.getY() + mEasyButton.getHeight() + 8);
//    add(&mHardButton, (getWidth() / 2) - (mHardButton.getWidth() / 2), mNormalButton.getY() + mNormalButton.getHeight() + 8);
//    add(&mBackButton, getWidth() - mBackButton.getWidth() - 5, getHeight() - mBackButton.getHeight() - 5);
//    mEasyButton.setActionEventId(ACTION_STARTGAME_EASY);
//    mEasyButton.addActionListener(this);
//    mNormalButton.setActionEventId(ACTION_STARTGAME_NORMAL);
//    mNormalButton.addActionListener(this);
//    mHardButton.setActionEventId(ACTION_STARTGAME_HARD);
//    mHardButton.addActionListener(this);
//    mBackButton.setActionEventId(ACTION_SLIDE_MAINMENU);
//    mBackButton.addActionListener(this);
//}
//
//NewGameMenu::~NewGameMenu()
//{
//    remove(&mUsernameLabel);
//    remove(&mUsernameTextbox);
//    remove(&mEasyButton);
//    remove(&mNormalButton);
//    remove(&mHardButton);
//    remove(&mBackButton);
//
//    mEasyButton.removeActionListener(this);
//    mNormalButton.removeActionListener(this);
//    mHardButton.removeActionListener(this);
//    mBackButton.removeActionListener(this);
//}
//
//const char* ID_STARTGAME_EASY = "START EASY GAME";
//const char* ID_STARTGAME_NORMAL = "START NORMAL GAME";
//const char* ID_STARTGAME_HARD = "START HARD GAME";
