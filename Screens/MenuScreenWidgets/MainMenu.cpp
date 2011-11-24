///*
// * MainMenu.cpp
// *
// *  Created on: Jul 1, 2009
// *      Author: alienjon
// */
//#include "MainMenu.hpp"
//
//#include <algorithm>
//
//#include "../../Game/Keywords.hpp"
//#include "../MenuScreen.hpp"
//#include "../../Managers/VideoManager.hpp"
//
//using std::max;
//
//MainMenu::MainMenu() :
//	mStartButton(ID_MAINMENU_BUTTON_START),
//	mOptionsButton(ID_MAINMENU_BUTTON_OPTIONS),
//	mCreditsButton(ID_MAINMENU_BUTTON_CREDITS),
//	mQuitButton(ID_MAINMENU_BUTTON_QUIT)
//{
//    // This menu is see through.
//    setOpaque(false);
//    setFrameSize(0);
//
//    // Listen to each button.
//    mStartButton.addActionListener(this);
//    mStartButton.setActionEventId(ACTION_SLIDE_NEWMENU);
//    mOptionsButton.addActionListener(this);
//    mOptionsButton.setActionEventId(ACTION_SLIDE_OPTIONSMENU);
//    mCreditsButton.addActionListener(this);
//    mCreditsButton.setActionEventId(ACTION_SLIDE_CREDITSMENU);
//    mQuitButton.addActionListener(this);
//    mQuitButton.setActionEventId(ACTION_QUIT);
//
//    // The horizontal buffer between buttons.
//    int buffer = 8;
//
//    // Because the positions are centered, I need to set the size first.
//    int width = max(mStartButton.getWidth(), mOptionsButton.getWidth());
//    width = max(width, mCreditsButton.getWidth());
//    width = max(width, mQuitButton.getWidth());
//    add(&mStartButton, (getWidth() / 2) - (mStartButton.getWidth() / 2), (getHeight() / 2) - (mStartButton.getHeight() * 2.5));
//    add(&mOptionsButton, (getWidth() / 2) - (mOptionsButton.getWidth() / 2), mStartButton.getY() + mStartButton.getHeight() + buffer);
//    add(&mCreditsButton, (getWidth() / 2) - (mCreditsButton.getWidth() / 2), mOptionsButton.getY() + mOptionsButton.getHeight() + buffer);
//    add(&mQuitButton, (getWidth() / 2) - (mQuitButton.getWidth() / 2), mCreditsButton.getY() + mCreditsButton.getHeight() + buffer);
//    mStartButton.setActionEventId(ACTION_SLIDE_STARTGAME);
//    mOptionsButton.setActionEventId(ACTION_SLIDE_OPTIONSMENU);
//    mCreditsButton.setActionEventId(ACTION_SLIDE_CREDITSMENU);
//    mQuitButton.setActionEventId(ACTION_QUIT);
//}
//
//MainMenu::~MainMenu()
//{
//    mStartButton.removeActionListener(this);
//    mOptionsButton.removeActionListener(this);
//    mCreditsButton.removeActionListener(this);
//    mQuitButton.removeActionListener(this);
//
//    remove(&mQuitButton);
//    remove(&mCreditsButton);
//    remove(&mOptionsButton);
//    remove(&mStartButton);
//}
