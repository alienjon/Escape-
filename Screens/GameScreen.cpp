/*
 * GameScreen.cpp
 *
 *  Created on: Jun 24, 2009
 *      Author: alienjon
 */
#include "GameScreen.hpp"

#include <cmath>
#include <stdexcept>

#include "../Game/Game.hpp"
#include "../Game/Keywords.hpp"
#include "../main.hpp"

//@todo This probably won't be here forever...
#include "../Engine/FontManager.hpp"

using std::abs;
using std::runtime_error;
using std::string;
using std::vector;

const unsigned int SCORE_COUNTER_INTERVAL = 25;
const unsigned int __TIME_MULTIPLIER__ = 1000;//@todo change time multiplier for difficulty levels? Laura found game a bit too hard, Dan a bit too easy?

GameScreen::GameScreen(unsigned int difficulty) : Screen(),
	mDifficulty(difficulty),
	mIsPaused(false),
	mLevel(0),
	mScore(0),
	mCounter(0),
	mResetView(false)
{
	// Set the size of the screen.
	setSize(800, 600);//@todo how should screen sizing work?  also, this needs to be changed when the menu widget is included

	// Configure the action listeners.
	mLevelCompleteWidget.addActionListener(this);
	mOptionsMenu.addActionListener(this);
	addKeyListener(&mPlayer);
	addKeyListener(&mLevelCompleteWidget);

	// @todo Temporary configurations.
	mScoreLabel.setFont(FontManager::getGCNFont(FONT_DEFAULT));
	mScoreLabel.setCaption("Score: 0");
	mScoreLabel.adjustSize();
	mScoreTimer.start();

	// Configurations.
    mTimerWidget.setPosition(mBase.getWidth() - mTimerWidget.getWidth(), mBase.getHeight() - mTimerWidget.getHeight());

    //@todo remove this when I implement boost libs to read through the filesystem.
    mBackMusicVector.push_back("Audio/DrSeuss - RoaringCow.flac");
    mBackMusicVector.push_back("Audio/Kid2Will-End_of_Your_Story.flac");
    mBackMusicVector.push_back("Audio/Pitfall-Final_Boss.flac");
    mBackMusicVector.push_back("Audio/Kid2Will-Valrens_Fight.flac");
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
	removeKeyListener(&mLevelCompleteWidget);
}

void GameScreen::action(const gcn::ActionEvent& event)
{
	string::size_type pos = 0;
	string keyword = extractDataLine(event.getId(), pos, DELIMITER);
	if(event.getSource() == &mLevelCompleteWidget)
	{
		// If the old level completed, then load the next level.
		if(mLevel->isDone())
		{
			// Unload the current level.
			mLevel->removeActionListener(this);
			mLevel->removeChangeScoreListener(this);
			mLevel->removeTimeChangeListener(this);
			delete mLevel;

			// Increase the difficulty and go to the next level.
			mLevel = new Level(++mDifficulty, mPlayer);
			mLevel->addActionListener(this);
			mLevel->addChangeScoreListener(this);
			mLevel->addTimeChangeListener(this);

		    // Reset the view.
		    mResetView = true;//@fixme this isn't working.  Make sure the view is reset when a new level is loaded.

			// Make sure the game is not paused.
			mTimerWidget.stop();
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
			mTimerWidget.unpause();
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

    // Return the view.
    renderer.setView(renderer.getDefaultView());
}

void GameScreen::keyPressed(gcn::KeyEvent& event)
{
	// Open the options menu.
	if(event.getKey().getValue() == gcn::Key::ESCAPE)
	{
		// Pause the game.
		mIsPaused = true;
		mTimerWidget.pause();

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
	Screen::keyReleased(event);
}

void GameScreen::load(GUI* gui)//@todo move the adding/etc... to the constructor
{
    // Set the base.
    gui->setBase(&mBase);//@todo should this be in Engine?

    // Hide the cursor.
    mDistributeActionEvent(ACTION_HIDECURSOR);

    // Setup the in-game options menu.
    mOptionsMenu.setVisible(false);
    mBase.add(&mOptionsMenu, 0, 0);

    // Add the menu bar.
    mBase.add(&mScoreLabel, 0, mBase.getHeight() - mScoreLabel.getHeight());
    addTimeChangeListener(&mTimerWidget);
    mBase.add(&mTimerWidget);

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

    // Restart the timer
    mTimerWidget.stop();
    mTimerWidget.start(mLevel->getMap().getComplexity() * __TIME_MULTIPLIER__);

	// Pick a random background music.
	string music = mBackMusicVector.at(random(0, int(mBackMusicVector.size() - 1)));
	if(!mBackMusic.openFromFile(music))
		ERROR("Unable to open music file '" + music);
	else
	{
		if(Game::isDebug())
			LOG("Playing: " + music);
		mBackMusic.play();
		mBackMusic.setLoop(true);
	}
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
		mScoreLabel.setCaption("Score: " + toString(mScore));
		mScoreLabel.adjustSize();

		// Update the counter.
		mCounter -= sign;

		// Reset the timer.
		mScoreTimer.start();
	}

	// If time is up, then the player has lost...
	if(mTimerWidget.getTime() == 0 && !mLevel->isDone() && !mLevelCompleteWidget.isVisible())
	{
		// Pause the game.
		mTimerWidget.stop();
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
		unsigned int timeBonus = mTimerWidget.getTime() / (1000000 * mLevel->getMap().getComplexity());
		unsigned int bonus = (timeBonus) * bonusMod;
		mLevelCompleteWidget.display("LEVEL COMPLETE", timeBonus, timeBonus, mLevel->getMap().getComplexity(), mLevel->getMap().getComplexity(), mDifficulty, (double)bonusMod, mScore, bonus, mScore + bonus);
		mScoreLabel.setCaption(toString(mScore += bonus));
		mLevelCompleteWidget.setPosition(mBase.getWidth() / 2 - mLevelCompleteWidget.getWidth() / 2, mBase.getHeight() / 2 - mLevelCompleteWidget.getHeight() / 2);
	}

    // Only do game logic if the game is not paused.
    if(!mIsPaused)
		mLevel->logic(mCamera);
}
