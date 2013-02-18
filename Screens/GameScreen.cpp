/*
 * GameScreen.cpp
 *
 *  Created on: Jun 24, 2009
 *      Author: alienjon
 */
#include "GameScreen.hpp"

#include <cmath>
#include <stdexcept>

#include <boost/filesystem.hpp>

#include "../Engine/FontManager.hpp"
#include "../Game/Game.hpp"
#include "../Game/Keywords.hpp"
#include "../main.hpp"

using std::abs;
using std::runtime_error;
using std::string;
using std::vector;

using namespace boost::filesystem;

const unsigned int SCORE_COUNTER_INTERVAL = 25;
const unsigned int __TIME_MULTIPLIER__ = 1000;//@todo change time multiplier for difficulty levels? Laura found game a bit too hard, Dan a bit too easy?
//@fixme make the time multiplier be based on the difficulty

#include <iostream>
using namespace std;//@todo remove when done
GameScreen::GameScreen(unsigned int difficulty) : Screen(),
	mDifficulty(difficulty),
	mIsPaused(false),
	mLevel(0),
	mScore(0),
	mCounter(0),
	mResetView(false)
{
	// Configure the action listeners.
	//@todo implement level complete and options widgets/menus
//	mLevelCompleteWidget.addActionListener(this);
//	mOptionsMenu.addActionListener(this);
	addKeyListener(&mPlayer);
//	addKeyListener(&mLevelCompleteWidget);

	// Load all flac audio as background musics.
	path p("Audio/");

	try
	{
		// Make sure that Audio/ exists and is a directory.
		// NOTE: The following code is modified from the boost::filesystem tutorials website.
		if(exists(p) && is_directory(p))
		{
			// Create a vector of items within the directory and populate it.
			vector<path> v;
			copy(directory_iterator(p), directory_iterator(), back_inserter(v));

			for(vector<path>::const_iterator it(v.begin()); it != v.end(); ++it)
				if(it->extension() == ".flac")
					mBackMusicVector.push_back(it->native());
		}
		else
			ERROR("Audio directory not found.  No background music will be played.");
	}
	catch(filesystem_error& e)
	{
		ERROR(e.what());
	}

	//@todo remove when GUI system is implemented
	if(!mFont.loadFromFile("Fonts/VeraMono.ttf"))
		ERROR("GameScreen::GameScreen() -> Unable to load font.");
}

GameScreen::~GameScreen()
{
	// In the event that the game crashes before a level is loaded, this will segfault without a check.
	if(mLevel)
	{
		mLevel->removeChangeScoreListener(this);
		mLevel->removeTimeChangeListener(this);
		delete mLevel;
	}
	removeKeyListener(&mPlayer);
//	removeKeyListener(&mLevelCompleteWidget);
}

void GameScreen::changeScore(int change)
{
	mCounter += change;
//	mScoreLabel.setCaption("Score: " + toString(mScore));
	mScoreDisplay.setString("Score: " + toString(mScore));
}

void GameScreen::draw(sf::RenderWindow& renderer)
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

    //@fixme Draw the temporary widgets.
    //@note These have to be done after setting the view because they are in the GUI.
    mTimerWidget.draw(renderer);
    renderer.draw(mScoreDisplay);
}

void GameScreen::eventOccurred(const string& eventId)
{
	string::size_type pos = 0;
	string keyword = extractDataLine(eventId, pos, DELIMITER);
	//@fixme need to re-implement gui here
/*	if(false)//@fixme need to create an eventId for completing the level: event.getSource() == &mLevelCompleteWidget)
	{
		// If the old level completed, then load the next level.
		if(mLevel->isDone())
		{
			// Unload the current level.
			mLevel->removeEventListener(this);
			mLevel->removeChangeScoreListener(this);
			mLevel->removeTimeChangeListener(this);
			delete mLevel;

			// Increase the difficulty and go to the next level.
			mLevel = new Level(++mDifficulty, mPlayer);
			mLevel->addEventListener(this);
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
	else if(keyword == GAMEOPTIONS_RESUME)
	{
		mIsPaused = false;
		mTimerWidget.unpause();
		distributeEvent(ACTION_HIDECURSOR);
	}
	else if(keyword == GAMEOPTIONS_MAINMENU)
	{
		distributeEvent(ACTION_TO_MAINMENU);
		mDone = true;
	}
	else if(keyword == GAMEOPTIONS_EXIT)
	{
		distributeEvent(ACTION_QUIT);
		mDone = true;
	}
	// Now check for the id's.
	else*/ if(keyword == ACTION_QUIT)
		mDone = true;
	else if(keyword == ACTION_TO_MAINMENU)
	{
		distributeEvent(ACTION_TO_MAINMENU);
		mDone = true;
	}
	else if(keyword == ACTION_PAUSE)
		mIsPaused = true;
	else if(keyword == ACTION_UNPAUSE)
		mIsPaused = false;
}

void GameScreen::keyPressed(const sf::Event& event)
{
	// Open the options menu.
	// @todo implement options menu
//	if(!mOptionsMenu.isVisible() && event.key.code == sf::Keyboard::Escape)
//	{
//		// Pause the game.
//		mIsPaused = true;
//		mTimerWidget.pause();
//
//		// Show the options menu.
//		mOptionsMenu.setVisible(true);
//		distributeEvent(ACTION_SHOWCURSOR);
//	}

	// Pass along the key pressed event.
	Screen::keyPressed(event);
}

void GameScreen::keyReleased(const sf::Event& event)
{
	Screen::keyReleased(event);
}

void GameScreen::load(const sf::View& view)
{
    // Hide the cursor.
    distributeEvent(ACTION_HIDECURSOR);

    // Setup the in-game options menu.
    //@todo implement options menu
//    mOptionsMenu.setVisible(false);
//    mOptionsMenu.setSize(mBase.getWidth(), mBase.getHeight());
//    mOptionsMenu.adjustInternals();
//    mBase.add(&mOptionsMenu, 0, 0);

    // Add the menu bar.
    //@todo implement score widget
    mScoreDisplay.setFont(mFont);
    mScoreDisplay.setString("Score: 0");
    mScoreDisplay.setCharacterSize(18);
    mScoreDisplay.setColor(sf::Color::Magenta);
    mScoreDisplay.setStyle(sf::Text::Bold);
    mScoreTimer.start();
    mScoreDisplay.setPosition(0, view.getSize().y - mScoreDisplay.getLocalBounds().height - 2);
cout << mScoreDisplay.getPosition().x << ", " << mScoreDisplay.getPosition().y << endl;
//	mScoreLabel.setFont(FontManager::getGCNFont(FONT_DEFAULT));
//	mScoreLabel.setCaption("Score: 0");
//	mScoreLabel.adjustSize();
//	mScoreTimer.start();
//    mBase.add(&mScoreLabel, 0, mBase.getHeight() - mScoreLabel.getHeight());
//    addTimeChangeListener(&mTimerWidget);
//    mBase.add(&mTimerWidget, mBase.getWidth() - mTimerWidget.getWidth(), mBase.getHeight() - mTimerWidget.getHeight());

    // Add the level complete widget.
    //@todo implement level complete
//    mLevelCompleteWidget.setVisible(false);
//    mBase.add(&mLevelCompleteWidget);

    // Load the level at the current difficulty.
    mLevel = new Level(mDifficulty, mPlayer);
    mLevel->addChangeScoreListener(this);
    mLevel->addTimeChangeListener(this);

    // Reset the view.
    mResetView = true;

    // Restart the timer
    //@todo re-implement new widget
    mTimerWidget.stop();
    mTimerWidget.start(mLevel->getMap().getComplexity() * __TIME_MULTIPLIER__);
    mTimerWidget.setPosition(view.getSize().x - mTimerWidget.getWidth(), view.getSize().y - mTimerWidget.getHeight() - 2);

	// Pick a random background music.
	string music = mBackMusicVector.at(random(0, int(mBackMusicVector.size() - 1)));
	if(!mBackMusic.openFromFile(music))
		ERROR("Unable to open music file '" + music);
	else
	{
		if(Game::isDebug())
			LOG("Playing: " + music);
		mBackMusic.play();
		mBackMusic.setLoop(true);;
	}
}

void GameScreen::logic()
{
	// @todo temporary hack for the timer widget logic (need to implement full gui)
	mTimerWidget.logic();

	// Update the score.
	if(mCounter != 0 && mScoreTimer.getTime() >= SCORE_COUNTER_INTERVAL)
	{
		// Only increment the score by 1, but determine the direction.
		int sign = (mCounter != 0) ? mCounter / abs(mCounter) : 0;

		// Increment the score.
		mScore = (sign < 0 && mScore == 0) ? 0 : mScore + sign;

		// Set the score.
		//@todo implement score label widget
//		mScoreLabel.setCaption("Score: " + toString(mScore));
		mScoreDisplay.setString("Score: " + toString(mScore));

		// Update the counter.
		mCounter -= sign;

		// Reset the timer.
		mScoreTimer.start();
	}

	// If time is up, then the player has lost...
	//@todo implement level complete widget
//	if(mTimerWidget.getTime() == 0 && !mLevel->isDone() && !mLevelCompleteWidget.isVisible())
//	{
//		// Pause the game.
//		mTimerWidget.stop();
//		mIsPaused = true;
//
//		// Display the level complete widget, but don't add any bonuses.
//		double bonusMod = 0;
//		unsigned int bonus = 0;
//		unsigned int timeBonus = mTimerWidget.getTime() / (1000000 * mLevel->getMap().getComplexity());
//		mLevelCompleteWidget.display("LEVEL FAILED", timeBonus, timeBonus, mLevel->getMap().getComplexity(), mLevel->getMap().getComplexity(), mDifficulty, (double)bonusMod, mScore, bonus, mScore + bonus);//@todo remove when done
//		mLevelCompleteWidget.setPosition(mBase.getWidth() / 2 - mLevelCompleteWidget.getWidth() / 2, mBase.getHeight() / 2 - mLevelCompleteWidget.getHeight() / 2);
//	}
//	// ... or if the next level should be loaded.
//	else if(mLevel->isDone() && !mLevelCompleteWidget.isVisible())
//	{
//		// Pause the game.
//		mTimerWidget.pause();
//		mIsPaused = true;
//
//		// Add the rest of the counter to the score and set the final score.
//		mScore = (mScore + mCounter < 0) ? 0 : mScore + mCounter;
//		mCounter = 0;
//
//		// Display the level complete widget.
//		double bonusMod = (mDifficulty / 10.0) + 1;
//		unsigned int timeBonus = mTimerWidget.getTime() / (1000000 * mLevel->getMap().getComplexity());
//		unsigned int bonus = (timeBonus) * bonusMod;
//		mLevelCompleteWidget.display("LEVEL COMPLETE", timeBonus, timeBonus, mLevel->getMap().getComplexity(), mLevel->getMap().getComplexity(), mDifficulty, (double)bonusMod, mScore, bonus, mScore + bonus);
//		mScoreLabel.setCaption(toString(mScore += bonus));
//		mLevelCompleteWidget.setPosition(mBase.getWidth() / 2 - mLevelCompleteWidget.getWidth() / 2, mBase.getHeight() / 2 - mLevelCompleteWidget.getHeight() / 2);
//	}

    // Only do game logic if the game is not paused.
    if(!mIsPaused)
		mLevel->logic(mCamera);
}
