///*
// * GameOptionsWidget.cpp
// *
// *  Created on: Aug 7, 2009
// *      Author: alienjon
// */
//#include "GameOptionsWidget.hpp"
//
//#include "../Engine/Colors.hpp"
//#include "../Engine/Logger.hpp"
//
//using std::string;
//
//const string GAMEOPTIONS_RESUME = "GAMEOPTIONS_RESUME";
//const string GAMEOPTIONS_MAINMENU = "GAMEOPTIONS_MAINMENU";
//const string GAMEOPTIONS_EXIT = "GAMEOPTIONS_EXIT";
//
//GameOptionsWidget::GameOptionsWidget() :
//	mResumeButton("RESUME"),
//	mOptionsButton("GAME OPTIONS"),
//	mCreditsButton("SEE CREDITS"),
//	mMainMenuButton("QUIT TO MAIN MENU"),
//	mExitButton("QUIT GAME")
//{
//    // Configure this widget.
//	gcn::Color c = gcn::COLOR_GREEN;
//	c.a = 75;
//    setBaseColor(c);
//    addKeyListener(this);
//    setFocusable(true);
//
//    // Configure the buttons.
//    mResumeButton.addActionListener(this);
//    mOptionsButton.addActionListener(this);
//    mCreditsButton.addActionListener(this);
//    mMainMenuButton.addActionListener(this);
//    mExitButton.addActionListener(this);
//
//    // Add the various buttons.
//    add(&mResumeButton);
//    add(&mOptionsButton);
//    add(&mCreditsButton);
//    add(&mMainMenuButton);
//    add(&mExitButton);
//}
//
//void GameOptionsWidget::action(const gcn::ActionEvent& actionEvent)
//{
//	if(actionEvent.getSource() == &mResumeButton)
//	{
//		setActionEventId(GAMEOPTIONS_RESUME);
//		distributeActionEvent();
//		setVisible(false);
//	}
//	else if(actionEvent.getSource() == &mOptionsButton)
//		LOG("Show Game Options");
//	else if(actionEvent.getSource() == &mCreditsButton)
//		LOG("Show Game Credits");
//	else if(actionEvent.getSource() == &mMainMenuButton)
//	{
//		setActionEventId(GAMEOPTIONS_MAINMENU);
//		distributeActionEvent();
//	}
//	else if(actionEvent.getSource() == &mExitButton)
//	{
//		setActionEventId(GAMEOPTIONS_EXIT);
//		distributeActionEvent();
//	}
//}
//
//void GameOptionsWidget::adjustInternals()
//{
//    mResumeButton.setPosition(getWidth() * 0.2, ((getHeight() / 6) * 1) - (mResumeButton.getHeight() / 2));
//    mOptionsButton.setPosition(getWidth() * 0.2, ((getHeight() / 6) * 2) - (mOptionsButton.getHeight() / 2));
//    mCreditsButton.setPosition(getWidth() * 0.2, ((getHeight() / 6) * 3) - (mCreditsButton.getHeight() / 2));
//    mMainMenuButton.setPosition(getWidth() * 0.2, ((getHeight() / 6) * 4) - (mMainMenuButton.getHeight() / 2));
//    mExitButton.setPosition(getWidth() * 0.2, ((getHeight() / 6) * 5) - (mExitButton.getHeight() / 2));
//}
//
//void GameOptionsWidget::keyPressed(gcn::KeyEvent& event)
//{
//	if(event.getKey().getValue() == gcn::Key::ESCAPE)
//	{
//		setActionEventId(GAMEOPTIONS_RESUME);
//		distributeActionEvent();
//		setVisible(false);
//	}
//}
