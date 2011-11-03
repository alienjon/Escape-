/*
 * GameScreen.cpp
 *
 *  Created on: Jun 24, 2009
 *      Author: alienjon
 */
#include "GameScreen.hpp"

#include <cmath>
#include <stdexcept>

#include "../Entities/Entity.hpp"
#include "../Game/Keywords.hpp"
#include "../Engine/Logger.hpp"
#include "../main.hpp"

using std::abs;
using std::runtime_error;
using std::string;

const unsigned int SCORE_COUNTER_INTERVAL = 25;
const unsigned int __TIME_MULTIPLIER__ = 2300;

GameScreen::GameScreen(unsigned int difficulty) :
	mDifficulty(difficulty),
	mIsPaused(false),
	mLevel(0),
	mScore(0),
	mCounter(0)
{
	// Configure the widgets.
	mMessageOSD.setWidth(mBase.getWidth() / 2);
	mMessageOSD.setPosition((mBase.getWidth() / 2) - (mMessageOSD.getWidth() / 2), mBase.getHeight() / 5);

	// Configure the action listeners.
	mMessageOSD.addActionListener(this);
	mBase.addKeyListener(&mMessageOSD);
	mLevelCompleteWidget.addActionListener(this);
	mOptionsMenu.addActionListener(this);

	// Start the timers.
	mScoreTimer.start();
}

GameScreen::~GameScreen()
{
	mMessageOSD.removeActionListener(this);
	mBase.removeKeyListener(&mMessageOSD);

	// In the event that the game crashes before a level is loaded, this will segfault without a check.
	if(mLevel)
	{
		mLevel->removeActionListener(this);
		mLevel->removeChangeScoreListener(this);

		// Delete and unset the level.
		delete mLevel;
	}
}

void GameScreen::action(const gcn::ActionEvent& event)
{
	// If the message OSD sends a signal, then the player has just pressed an action button in the message box.
	if(event.getSource() == &mMessageOSD)
	{
		// The message box is to be closed.
		mMessageOSD.setVisible(false);
	}
	// If the level complete widget sends a signal, then load the next level.
	else if(event.getSource() == &mLevelCompleteWidget)
	{
		// Hide the level complete widget.
		mLevelCompleteWidget.setVisible(false);

		// If the old level completed, then load the next level.
		if(mLevel->isDone())
		{
			// Unload the current level.
			mLevel->removeActionListener(this);
			mLevel->removeChangeScoreListener(this);
			delete mLevel;

			// Increase the difficulty and go to the next level.
			mLevel = new Level(++mDifficulty, mPlayer, mViewport);
			mLevel->addActionListener(this);
			mLevel->addChangeScoreListener(this);

			// Make sure the game is not paused.
			mMenuBar.stop();
			mMenuBar.start(mLevel->getMap().getComplexity() * __TIME_MULTIPLIER__);
			mIsPaused = false;
		}
		// If the old level didn't complete, then the level was lost.
		else
		{
			setActionEventId(ACTION_TO_MAINMENU);
			distributeActionEvent();
			mDone = true;
		}
	}
	else if(event.getSource() == &mOptionsMenu)
	{
		if(event.getId() == GAMEOPTIONS_RESUME)
		{
			mIsPaused = false;
			mMenuBar.unpause();
			mOptionsMenu.setVisible(false);
			mOptionsMenu.requestMoveToBottom();
		}
		else if(event.getId() == GAMEOPTIONS_MAINMENU)
		{
			setActionEventId(ACTION_TO_MAINMENU);
			distributeActionEvent();
			mDone = true;
		}
		else if(event.getId() == GAMEOPTIONS_EXIT)
		{
			setActionEventId(ACTION_QUIT);
			distributeActionEvent();
			mDone = true;
		}
	}
	// Now check for the id's.
	else if(event.getId() == ACTION_QUIT)
		mDone = true;
	else if(event.getId() == ACTION_TO_MAINMENU)
	{
		setActionEventId(ACTION_TO_MAINMENU);
		distributeActionEvent();
		mDone = true;
	}
	else if(event.getId() == ACTION_PAUSE)
		mIsPaused = true;
	else if(event.getId() == ACTION_UNPAUSE)
		mIsPaused = false;
}

void GameScreen::changeScore(int change)
{
	mCounter += change;
}

void GameScreen::displayMessage(const string& caption, const string& message, const string& sprite, const string& keyword)
{
	Sprite anim;//@todo review how this is handled/is it needed?
	// Show the message.
	mMessageOSD.setVisible(true);
	mMessageOSD.set(caption, message, anim);
	mMessageOSD.setActionEventId(keyword);
	mMessageOSD.requestFocus();
	mMessageOSD.requestMoveToTop();
}

void GameScreen::draw(Renderer& renderer)
{
	// Everything on the level is relative to the viewport.
	renderer.pushClipArea(gcn::Rectangle(0, mMenuBar.getY() + mMenuBar.getHeight(), SCREEN_WIDTH, SCREEN_HEIGHT));
	renderer.pushClipArea(gcn::Rectangle(-mViewport.getX(), -mViewport.getY(), mViewport.getWidth(), mViewport.getHeight()));

    // Draw any screen objects.
    mLevel->draw(renderer);

    // Pop the drawing area.
    renderer.popClipArea();
    renderer.popClipArea();
}

void GameScreen::handleInput(const Input& input)
{
	// Open the menu widget if escape is pressed.
	if(input.isKeyPressed(SDLK_ESCAPE))
	{
		// Pause the game.
		mIsPaused = true;
		mMenuBar.pause();

		// Show the options menu.
		mOptionsMenu.setVisible(true);
		mOptionsMenu.requestFocus();
		mOptionsMenu.requestMoveToTop();
	}

	// If we're not paused and the message display isn't visible, continue with input.
    if(!mIsPaused && !mMessageOSD.isVisible() && !mOptionsMenu.isVisible())
        mLevel->handleInput(input);
}

void GameScreen::load(GUI* gui)
{
    // Set the base.
    gui->setBase(&mBase);

    // Setup the in-game options menu.
    mOptionsMenu.setVisible(false);
    mBase.add(&mOptionsMenu, 0, 0);

    // Hide the message OSD.
    mMessageOSD.setVisible(false);

    // Add the OSDs to the screen.
    mBase.add(&mMessageOSD);

    // Add the menu bar.
    mMenuBar.setSize(SCREEN_WIDTH, SCREEN_HEIGHT * 0.15);
    mMenuBar.adjustInternals();
    mViewport.setHeight(mViewport.getHeight() - mMenuBar.getHeight());
    mViewport.setYOffset(mMenuBar.getHeight());
    mBase.add(&mMenuBar);

    // Add the level complete widget.
    mLevelCompleteWidget.setVisible(false);
    mBase.add(&mLevelCompleteWidget);

    // Load the level at the current difficulty.
    mLevel = new Level(mDifficulty, mPlayer, mViewport);
    mLevel->addActionListener(this);
    mLevel->addChangeScoreListener(this);

    // Configure the mini map.
    mMenuBar.configureMiniMap(mLevel->getMap().copyMapImage(), &mPlayer);

    // Start the timer.
    mMenuBar.stop();// Stopping first as a precaution.
    mMenuBar.start(mLevel->getMap().getComplexity() * __TIME_MULTIPLIER__);
}

void GameScreen::logic()
{
	// Update the score.
	if(mCounter != 0 && mScoreTimer.getTime() >= SCORE_COUNTER_INTERVAL)
	{
		// Only increment the score by 1, but determine the direction.
		int sign = (mCounter != 0) ? mCounter / abs(mCounter) : 0;

		// Increment the score.
		mScore = (sign < 0 && mScore == 0) ? 0 : mScore + sign;

		// Set the score.
		mMenuBar.setScore(mScore);

		// Update the counter.
		mCounter -= sign;

		// Reset the timer.
		mScoreTimer.start();
	}

	// If time is up, then the player has lost...
	if(mMenuBar.getTime() == 0 && !mLevel->isDone() && !mLevelCompleteWidget.isVisible())
	{
		// Pause the game.
		mMenuBar.stop();
		mIsPaused = true;

		// Display the level complete widget, but don't add any bonuses.
		double bonusMod = 0;
		unsigned int bonus = 0;
		mLevelCompleteWidget.display("LEVEL FAILED", mMenuBar.getTime()/100, mMenuBar.getTime(), mLevel->getMap().getComplexity(), mLevel->getMap().getComplexity(), mDifficulty, (double)bonusMod, mScore, bonus, mScore + bonus);
		mLevelCompleteWidget.setPosition(mBase.getWidth() / 2 - mLevelCompleteWidget.getWidth() / 2, mBase.getHeight() / 2 - mLevelCompleteWidget.getHeight() / 2);
	}
	// ... or if the next level should be loaded.
	else if(mLevel->isDone() && !mLevelCompleteWidget.isVisible())
	{
		// Pause the game.
		mMenuBar.pause();
		mIsPaused = true;

		// Add the rest of the counter to the score and set the final score.
		mScore = (mScore + mCounter < 0) ? 0 : mScore + mCounter;
		mCounter = 0;
		mMenuBar.setScore(mScore);

		// Display the level complete widget.
		double bonusMod = (mDifficulty / 10.0) + 1;
		unsigned int bonus = (mMenuBar.getTime()/100 + mLevel->getMap().getComplexity()) * bonusMod; // @todo review scoring
		mLevelCompleteWidget.display("LEVEL COMPLETE", mMenuBar.getTime()/100, mMenuBar.getTime()/100, mLevel->getMap().getComplexity(), mLevel->getMap().getComplexity(), mDifficulty, (double)bonusMod, mScore, bonus, mScore + bonus);
		mMenuBar.setScore(mScore += bonus);
		mLevelCompleteWidget.setPosition(mBase.getWidth() / 2 - mLevelCompleteWidget.getWidth() / 2, mBase.getHeight() / 2 - mLevelCompleteWidget.getHeight() / 2);
	}

    // Only do game logic if the game is not paused and neither the options menu or
	// the message display widget is being shown.
    if(!mIsPaused && !mMessageOSD.isVisible() && !mOptionsMenu.isVisible())
    {
		mLevel->logic();
    }
}
