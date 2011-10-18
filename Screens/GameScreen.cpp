/*
 * GameScreen.cpp
 *
 *  Created on: Jun 24, 2009
 *      Author: alienjon
 */
#include "GameScreen.hpp"

#include <cmath>
#include <stdexcept>

#include "../Managers/AnimationManager.hpp"
#include "../Entities/Entity.hpp"
#include "../Game/Keywords.hpp"
#include "../Engine/Logger.hpp"
#include "../main.hpp"

using std::abs;
using std::runtime_error;
using std::string;

const unsigned int SCORE_COUNTER_INTERVAL = 25;

unsigned int convertTimeToBonus(unsigned int time)
{
	return time / 1000;//@todo how should time bonus be calculated?
}

GameScreen::GameScreen(Event difficulty) :
	mDifficulty(0),
	mIsPaused(false),
	mLevel(0),
	mScore(0),
	mCounter(0)
{
	// Determine the game's difficulty value based on the difficulty level.
	switch(difficulty)//@todo review difficulty in testing
	{
		case EVENT_STARTNORMAL:
		{
			mDifficulty = 5;
			break;
		}
		case EVENT_STARTHARD:
		{
			mDifficulty = 10;
			break;
		}
		default:
		{
			mDifficulty = 1;
		}
	}

	// Listen for when the game over widget's buttons are pressed.
	mGameOverWidget.addEventListener(this);
	mGameOverWidget.addActionListener(this); // @todo use Guichan's action events instead of my own events.  This will require removing the EventListeners, etc...

	// Configure the widgets.
	mOptionsMenu.setSize(mBase.getWidth() / 2, mBase.getHeight() / 2);
	mMessageOSD.setWidth(mBase.getWidth() / 2);
	mMessageOSD.setPosition((mBase.getWidth() / 2) - (mMessageOSD.getWidth() / 2), mBase.getHeight() / 5);

	// Configure the action listeners.
	mMessageOSD.addActionListener(this);
	mBase.addKeyListener(&mMessageOSD);
	mLevelCompleteWidget.addActionListener(this);

	// Start the timers.
	mInputTimer.start();
	mScoreTimer.start();
}

GameScreen::~GameScreen()
{
	mGameOverWidget.removeEventListener(this);
	mGameOverWidget.removeActionListener(this);
	mMessageOSD.removeActionListener(this);
	mBase.removeKeyListener(&mMessageOSD);

	// The level should stop listening for events.
	mLevel->removeEventListener(this);
	mLevel->removeChangeScoreListener(this);
	mLevel->setInterfaceListener(0);

    // Delete and unset the level.
	delete mLevel;
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
	if(event.getSource() == &mLevelCompleteWidget)
	{
		// Hide the level complete widget.
		mLevelCompleteWidget.setVisible(false);

		// Unload the current level.
		mLevel->removeEventListener(this);
		mLevel->removeChangeScoreListener(this);
		delete mLevel;

		// Increase the difficulty and go to the next level.
		mLevel = new Level(++mDifficulty, mPlayer, mViewport);
		mLevel->addEventListener(this);
		mLevel->addChangeScoreListener(this);

		// Make sure the game is not paused.
		mMenuBar.stop();
		mMenuBar.start();
		mIsPaused = false;

// @todo need to find a way to quit the game normally		mDone = true;
	}
}

void GameScreen::changeScore(int change)
{
	mCounter += change;
}

void GameScreen::displayMessage(const string& caption, const string& message, const string& sprite, const string& keyword)
{
	Sprite anim;
	try
	{
		anim = AnimationManager::get(sprite);
	}
	catch(runtime_error& e)
	{
		anim = AnimationManager::get(ANIMATION_NULL_CONVERSATION);
	}

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

    // Apply the layers.
//    renderer.applyLayers();@todo review lighting
}

void GameScreen::eventOccurred(Event event, const std::string& content, CreatureMovedToPointListener* creatureMovedToVectorListener)
{
    // If the event is to quit or to load the main menu, then we are done.
    switch(event)
    {
    	case EVENT_PAUSE:
    	{
    		mIsPaused = true;
    		break;
    	}
    	case EVENT_UNPAUSE:
    	{
    		mIsPaused = false;
    		break;
    	}
        case EVENT_INPUT_ACTIVATE:
        {
        	// Get the player and halt input.
        	mPlayer.setInputState(true);
        	break;
        }
        case EVENT_INPUT_DEACTIVATE:
        {
        	mPlayer.setInputState(false);
        	break;
        }
        case EVENT_MAINMENU:
        {
        	// The content should be a delimited list of images to show as credits screens before returning to the main menu.
        	// Iterate through them and load them.
//        	string::size_type pos = 0;
//        	while(pos != content.size())
//        	{
//        		// Extract the current image and load it.
//        		string filename = extractDataLine(content, pos, CHAR_DELIMITER);
//        		pushEvent(EVENT_ADDCREDITSCREEN, filename); // @todo instead of a credit screen, show the player the top 10 scores for his/her difficulty.
//        	}

        	// End by adding the main menu.
        	pushEvent(EVENT_MAINMENU);

        	// Don't break, as both EVENT_MAINMENU and EVENT_QUIT need to set mDone.
        }
        case EVENT_QUIT:
        {
            mDone = true;
            break;
        }
        default:
        {
        }
    }

    // Push the event to any additional listeners.
    pushEvent(event, content);
}

void GameScreen::handleInput(const Input& input)
{
	/*  As in the Game object, each conditional will return to avoid repetition of commands. */

	if(mInputTimer.getTime() >= 50)
	{
		// Restart the timer.
		mInputTimer.start();

		if(input.isKeyPressed(SDLK_ESCAPE))
		{
			// If the options menu is open (is visible) then hide it and unpause the game.
			if(mOptionsMenu.isVisible())
			{
				mOptionsMenu.setVisible(false);
			}
			// If the options menu is hidden, the display message is not being shown,
			// and the game is not paused, then show the options and pause the game.
			else if(!mIsPaused && !mMessageOSD.isVisible())
			{
				mOptionsMenu.setVisible(true);
			}
			return;
		}
	}

	// If we're not paused and the message display isn't visible, continue with input.
    if(!mIsPaused && !mMessageOSD.isVisible() && !mOptionsMenu.isVisible())
    {
        mLevel->handleInput(input);
    }
}

void GameScreen::load(GUI* gui)
{
    // Set the base.
    gui->setBase(&mBase);

    // Setup the in-game options menu.
    mOptionsMenu.setVisible(false);
    mBase.add(&mOptionsMenu, (mBase.getWidth() / 2) - (mOptionsMenu.getWidth() / 2), (mBase.getHeight() / 2) - (mOptionsMenu.getHeight() / 2));

    // Setup the game over widget.
    mGameOverWidget.setVisible(false);
    mGameOverWidget.setSize((mBase.getWidth() * 3) / 4, (mBase.getWidth() * 3) / 4);
    mBase.add(&mGameOverWidget, (mBase.getWidth() / 2) - (mGameOverWidget.getWidth() / 2), (mBase.getHeight() / 2) - (mGameOverWidget.getHeight() / 2));

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

    // Set level listeners.
    mLevel->addEventListener(this);
    mLevel->addChangeScoreListener(this);

    // Configure the mini map.
    mMenuBar.configureMiniMap(mLevel->getMap().copyMapImage(), &mPlayer);

    // Start the timer.
    mMenuBar.stop();
    mMenuBar.start();
}

void GameScreen::logic()
{
	// Update the counter if time has run up.
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

	// Before any logic has been done, check if the next level should be loaded.
	if(mLevel->isDone() && !mLevelCompleteWidget.isVisible())
	{
		// Stop the timer.
		mMenuBar.pause();

		// Pause the game itself.
		mIsPaused = true;

		// Add the rest of the counter to the score and set the final score.
		mScore = (mScore + mCounter < 0) ? 0 : mScore + mCounter;
		mCounter = 0;
		mMenuBar.setScore(mScore);

		// Display the level complete widget.
		mLevelCompleteWidget.setPosition(mBase.getWidth() / 2 - mLevelCompleteWidget.getWidth() / 2, mBase.getHeight() / 2 - mLevelCompleteWidget.getHeight() / 2);
		double bonusMod = (mDifficulty / 10.0) + 1;
		unsigned int bonus = (convertTimeToBonus(mMenuBar.getTime()) + mLevel->getMap().getComplexity()) * bonusMod; // @todo review scoring
		mLevelCompleteWidget.display(mMenuBar.getTime()/100, convertTimeToBonus(mMenuBar.getTime()), mLevel->getMap().getComplexity(), mLevel->getMap().getComplexity(), mDifficulty, (double)bonusMod, mScore, bonus, mScore + bonus);
		mScore += bonus;
		mLevelCompleteWidget.setPosition(mBase.getWidth() / 2 - mLevelCompleteWidget.getWidth() / 2, mBase.getHeight() / 2 - mLevelCompleteWidget.getHeight() / 2);
	}

    // Only do game logic if the game is not paused and neither the options menu or
	// the message display widget is being shown.
    if(!mIsPaused && !mMessageOSD.isVisible() && !mOptionsMenu.isVisible())
    {
		mLevel->logic();
    }
}
