/*
 * GameScreen.cpp
 *
 *  Created on: Jun 24, 2009
 *      Author: alienjon
 */
#include "GameScreen.hpp"

#include <cmath>
#include <stdexcept>

#include "../Game/Keywords.hpp"
#include "../main.hpp"

//@todo This probably won't be here forever...
#include "../Engine/FontManager.hpp"

using std::abs;
using std::runtime_error;
using std::string;

const unsigned int SCORE_COUNTER_INTERVAL = 25;
const unsigned int __TIME_MULTIPLIER__ = 1000;//@todo change time multiplier for difficulty levels? Laura found game a bit too hard, Dan a bit too easy?
#include <iostream>
using namespace std;//@todo remove when done
GameScreen::GameScreen(unsigned int difficulty) : Screen(),
	mDifficulty(difficulty),
	mIsPaused(false),
	mLevel(0),
	mItemDisplay(mPlayer),
	mScore(0),
	mCounter(0),
	mResetView(false)
{
	// Set the size of the screen.
	setSize(800, 600);//@todo how should screen sizing work?  also, this needs to be changed when the menu widget is included

	// Load the background music.
	if(!mBackMusic.openFromFile(MUSIC_BACKGROUND))
		ERROR("Unable to open music file '" + MUSIC_BACKGROUND);
	else
		mBackMusic.play();

	// Configure the action listeners.
	mLevelCompleteWidget.addActionListener(this);
	mOptionsMenu.addActionListener(this);
	addKeyListener(&mPlayer);
	addKeyListener(&mItemDisplay);
	addKeyListener(&mPlayerDirectionSelectionWidget);
	addKeyListener(&mLevelCompleteWidget);

	// Setup the player/player item display.
	mPlayer.addPickupListener(&mItemDisplay);

	// @todo Temporary configurations.
	mScoreLabel.setFont(FontManager::getGCNFont(FONT_DEFAULT));
	mScoreLabel.setCaption("Score: 0");
	mScoreLabel.adjustSize();
	mScoreTimer.start();
}

GameScreen::~GameScreen()
{
	// In the event that the game crashes before a level is loaded, this will segfault without a check.
	if(mLevel)
	{
		mLevel->removeActionListener(this);
		mLevel->removeChangeScoreListener(this);
		mLevel->removeTimeChangeListener(this);
		delete mLevel;
	}
	removeKeyListener(&mPlayer);
	removeKeyListener(&mItemDisplay);
	removeKeyListener(&mPlayerDirectionSelectionWidget);
	removeKeyListener(&mLevelCompleteWidget);
	mPlayer.removePickupListener(&mItemDisplay);
    mPlayerDirectionSelectionWidget.removeActionListener(this);
}

void GameScreen::action(const gcn::ActionEvent& event)
{
	string::size_type pos = 0;
	string keyword = extractDataLine(event.getId(), pos, DELIMITER);
	if(keyword == ACTION_SELECTION_REQUEST)
	{
		// Determine the directions to display.
		bool up	   = extractDataLine(event.getId(), pos, DELIMITER) == toLower("true");
		bool down  = extractDataLine(event.getId(), pos, DELIMITER) == toLower("true");
		bool left  = extractDataLine(event.getId(), pos, DELIMITER) == toLower("true");
		bool right = extractDataLine(event.getId(), pos, DELIMITER) == toLower("true");
		int x = toInt(extractDataLine(event.getId(), pos, DELIMITER));
		int y = toInt(extractDataLine(event.getId(), pos, DELIMITER));

		// Display the widget.
		mPlayerDirectionSelectionWidget.setPosition(((mBase.getWidth() / 2) - (mCamera.getCenter().x - x)) - (mPlayerDirectionSelectionWidget.getWidth() / 2),
													((mBase.getHeight() / 2) - (mCamera.getCenter().y - y)) - (mPlayerDirectionSelectionWidget.getHeight() / 2));
		mPlayerDirectionSelectionWidget.display(up, down, left, right);
	}
	else if(keyword == ACTION_DIRECTION_SELECTED)
	{
		// Tell the level to phase the player in the requested direction.
		mLevel->phaseDirection(extractDataLine(event.getId(), pos, DELIMITER));
	}
	else if(event.getSource() == &mLevelCompleteWidget)
	{
		// If the old level completed, then load the next level.
		if(mLevel->isDone())
		{
			// Unload the current level.
			mLevel->removeActionListener(this);
			mLevel->removeChangeScoreListener(this);
			mLevel->removeTimeChangeListener(this);
			delete mLevel;
			mItemDisplay.clear();

			// Increase the difficulty and go to the next level.
			mLevel = new Level(++mDifficulty, mPlayer);
			mLevel->addActionListener(this);
			mLevel->addChangeScoreListener(this);
			mLevel->addTimeChangeListener(this);

		    // Reset the view.
		    mResetView = true;//@todo this isn't working.  Make sure the view is reset when a new level is loaded.

			// Make sure the game is not paused.
//			mMenuBar.stop();
			mTimerWidget.stop();//@todo remove when done
//			mMenuBar.start(mLevel->getMap().getComplexity() * __TIME_MULTIPLIER__);
			mTimerWidget.start(mLevel->getMap().getComplexity() * __TIME_MULTIPLIER__);//@todo remove when done
			mIsPaused = false;
		}
		// If the old level didn't complete, then the level was lost.
		else
		{
//			setActionEventId(ACTION_TO_MAINMENU);//@todo implement main menu.
//			distributeActionEvent();
			mDone = true;
		}
	}
	else if(event.getSource() == &mOptionsMenu)
	{
		if(keyword == GAMEOPTIONS_RESUME)
		{
			mIsPaused = false;
//			mMenuBar.unpause();
			mTimerWidget.unpause();//@todo remove when done
			mDistributeActionEvent(ACTION_HIDECURSOR);
		}
		else if(keyword == GAMEOPTIONS_MAINMENU)
		{
			mDistributeActionEvent(ACTION_TO_MAINMENU);
			mDone = true;
		}
		else if(keyword == GAMEOPTIONS_EXIT)
		{
			mDistributeActionEvent(ACTION_QUIT);
			mDone = true;
		}
	}
	// Now check for the id's.
	else if(keyword == ACTION_QUIT)
		mDone = true;
	else if(keyword == ACTION_TO_MAINMENU)
	{
		mDistributeActionEvent(ACTION_TO_MAINMENU);
		mDone = true;
	}
	else if(keyword == ACTION_PAUSE)
		mIsPaused = true;
	else if(keyword == ACTION_UNPAUSE)
		mIsPaused = false;
}

void GameScreen::changeScore(int change)
{
	mCounter += change;
	mScoreLabel.setCaption("Score: " + toString(mScore));
	mScoreLabel.adjustSize();
}

void GameScreen::draw(gcn::SFMLGraphics& renderer)
{
	// If resetting the view, reset it.
	if(mResetView)
	{
		mCamera = renderer.getDefaultView();
		mResetView = false;
	}

	// Everything on the level is relative to the viewport.
	renderer.setView(mCamera);

    // Draw any screen objects.
    mLevel->draw(renderer);
}

void GameScreen::keyPressed(gcn::KeyEvent& event)
{
	// If the shift key is pressed, give the item display widget focus and don't let the player move.
	if(event.getKey().getValue() == gcn::Key::LEFT_SHIFT || event.getKey().getValue() == gcn::Key::RIGHT_SHIFT)
	{
		mItemDisplay.setFocusable(true);
		mPlayer.setInputState(false);
	}

	// Open the options menu.
	if(event.getKey().getValue() == gcn::Key::ESCAPE)
	{
		// Pause the game.
		mIsPaused = true;
//		mMenuBar.pause();
		mTimerWidget.pause();//@todo remove when done

		// Show the options menu.
		mOptionsMenu.setVisible(true);
		mOptionsMenu.requestMoveToTop();
		mDistributeActionEvent(ACTION_SHOWCURSOR);
	}

	// Pass along the key pressed event.
	Screen::keyPressed(event);
}

void GameScreen::keyReleased(gcn::KeyEvent& event)
{
	// If the shift key is released, return movement to the player.
	if(event.getKey().getValue() == gcn::Key::LEFT_SHIFT || event.getKey().getValue() == gcn::Key::RIGHT_SHIFT)
		mPlayer.setInputState(true);

	Screen::keyReleased(event);
}

void GameScreen::load(GUI* gui)//@todo move the adding/etc... to the constructor
{
	// Start playing background music.
//	mBackMusic.//@todo implement playing music

    // Set the base.
    gui->setBase(&mBase);//@todo should this be in Engine?

    // Hide the cursor.
    mDistributeActionEvent(ACTION_HIDECURSOR);

    // Setup the in-game options menu.
    mOptionsMenu.setVisible(false);
    mBase.add(&mOptionsMenu, 0, 0);

    // Player items.
//    mBase.addKeyListener(&mItemDisplay);
    mBase.add(&mItemDisplay, mBase.getWidth() - mItemDisplay.getWidth() - 4, 4);

    // Direction Selection.
    mBase.add(&mPlayerDirectionSelectionWidget);
    mPlayerDirectionSelectionWidget.addActionListener(this);

    // Add the menu bar.
    mBase.add(&mScoreLabel, 0, mBase.getHeight() - mScoreLabel.getHeight());
    addTimeChangeListener(&mTimerWidget);
    mBase.add(&mTimerWidget);
//    mMenuBar.setSize(mBase.getWidth(), mBase.getHeight() * 0.15);
//    mMenuBar.adjustInternals();
//    mViewport.setHeight(mViewport.getHeight() - mMenuBar.getHeight());
//    mViewport.setYOffset(mMenuBar.getHeight());
//    mBase.add(&mMenuBar);

    // Add the level complete widget.
    mLevelCompleteWidget.setVisible(false);
    mBase.add(&mLevelCompleteWidget);

    // Load the level at the current difficulty.
    mLevel = new Level(mDifficulty, mPlayer);
    mLevel->addActionListener(this);
    mLevel->addChangeScoreListener(this);
    mLevel->addTimeChangeListener(this);

    // Reset the view.
    mResetView = true;

    // Start the timer
    mTimerWidget.stop();
    mTimerWidget.start(mLevel->getMap().getComplexity() * __TIME_MULTIPLIER__);
//    mMenuBar.stop();// Stopping first as a precaution.
//    mMenuBar.start(mLevel->getMap().getComplexity() * __TIME_MULTIPLIER__);
}

void GameScreen::logic()
{
	//@todo Temporary until I figure GUI stuff out later.
	mTimerWidget.adjustSize();
	mTimerWidget.setPosition(mBase.getWidth() - mTimerWidget.getWidth(), mBase.getHeight() - mTimerWidget.getHeight());

	// Update the score.
	if(mCounter != 0 && mScoreTimer.getTime() >= SCORE_COUNTER_INTERVAL)
	{
		// Only increment the score by 1, but determine the direction.
		int sign = (mCounter != 0) ? mCounter / abs(mCounter) : 0;

		// Increment the score.
		mScore = (sign < 0 && mScore == 0) ? 0 : mScore + sign;

		// Set the score.
		//@todo fix when gui implemented
		mScoreLabel.setCaption("Score: " + toString(mScore));
		mScoreLabel.adjustSize();
//		mMenuBar.setScore(mScore);

		// Update the counter.
		mCounter -= sign;

		// Reset the timer.
		mScoreTimer.start();
	}

	// If time is up, then the player has lost...
	if(mTimerWidget.getTime() == 0 && !mLevel->isDone() && !mLevelCompleteWidget.isVisible())
	{
		// Pause the game.
		mTimerWidget.stop();//@todo remove when done
		mIsPaused = true;

		// Display the level complete widget, but don't add any bonuses.
		double bonusMod = 0;
		unsigned int bonus = 0;
		unsigned int timeBonus = mTimerWidget.getTime() / (1000000 * mLevel->getMap().getComplexity());
		mLevelCompleteWidget.display("LEVEL FAILED", timeBonus, timeBonus, mLevel->getMap().getComplexity(), mLevel->getMap().getComplexity(), mDifficulty, (double)bonusMod, mScore, bonus, mScore + bonus);//@todo remove when done
		mLevelCompleteWidget.setPosition(mBase.getWidth() / 2 - mLevelCompleteWidget.getWidth() / 2, mBase.getHeight() / 2 - mLevelCompleteWidget.getHeight() / 2);
	}
	// ... or if the next level should be loaded.
	else if(mLevel->isDone() && !mLevelCompleteWidget.isVisible())
	{
		// Pause the game.
		mTimerWidget.pause();
		mIsPaused = true;

		// Add the rest of the counter to the score and set the final score.
		mScore = (mScore + mCounter < 0) ? 0 : mScore + mCounter;
		mCounter = 0;

		// Display the level complete widget.
		double bonusMod = (mDifficulty / 10.0) + 1;
		unsigned int timeBonus = mTimerWidget.getTime() / (1000000 * mLevel->getMap().getComplexity()); // @todo review scoring
		unsigned int bonus = (timeBonus) * bonusMod;
		mLevelCompleteWidget.display("LEVEL COMPLETE", timeBonus, timeBonus, mLevel->getMap().getComplexity(), mLevel->getMap().getComplexity(), mDifficulty, (double)bonusMod, mScore, bonus, mScore + bonus);//@todo remove when done
		mScoreLabel.setCaption(toString(mScore += bonus));//@todo remove when done
		mLevelCompleteWidget.setPosition(mBase.getWidth() / 2 - mLevelCompleteWidget.getWidth() / 2, mBase.getHeight() / 2 - mLevelCompleteWidget.getHeight() / 2);
	}

    // Only do game logic if the game is not paused.
    if(!mIsPaused)
		mLevel->logic(mCamera);
}
