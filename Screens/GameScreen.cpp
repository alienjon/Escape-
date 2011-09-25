/*
 * GameScreen.cpp
 *
 *  Created on: Jun 24, 2009
 *      Author: alienjon
 */
#include "GameScreen.hpp"

#include <stdexcept>

#include "../Managers/AnimationManager.hpp"
#include "../Entities/Entity.hpp"
#include "../Game/Keywords.hpp"
#include "../Engine/Logger.hpp"

using std::runtime_error;
using std::string;

GameScreen::GameScreen(Event difficulty) :
	mLoadLevel(false),
	mDifficulty(0),
	mIsPaused(false),
	mLevel(0)

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

	// Start the input timer.
	mInputTimer.start();
}

GameScreen::~GameScreen()
{
	mGameOverWidget.removeEventListener(this);
	mGameOverWidget.removeActionListener(this);
	mMessageOSD.removeActionListener(this);
	mBase.removeKeyListener(&mMessageOSD);

	// The level should stop listening for events.
	mLevel->removeEventListener(this);
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
    // Set the drawing area based on the viewport.
	renderer.pushClipArea(gcn::Rectangle(-mViewport.getX(), -mViewport.getY(), mViewport.getWidth(), mViewport.getHeight()));

    // Draw any screen objects.
    mLevel->draw(renderer, mViewport);

    // Pop the drawing area.
    renderer.popClipArea();

    // Apply the layers before drawing the cursor.
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
        case EVENT_NEXTLEVEL:
        {
        	mLoadLevel = true;
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

Vector GameScreen::getViewportOffset() const
{
	return mViewport.getOffset();
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

		if(Game::isDebug())//@todo move the viewport around FOR TESTING ONLY
		{
			int step = 25;
			if(input.isKeyPressed(SDLK_UP))
			{
				mViewport.setY(mViewport.getY() - step);
			}
			if(input.isKeyPressed(SDLK_DOWN))
			{
				mViewport.setY(mViewport.getY() + step);
			}
			if(input.isKeyPressed(SDLK_LEFT))
			{
				mViewport.setX(mViewport.getX() - step);
			}
			if(input.isKeyPressed(SDLK_RIGHT))
			{
				mViewport.setX(mViewport.getX() + step);
			}
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
    mOptionsMenu.adjustSize(); // This MUST be done upon level loading (several internal sizes depend on the fonts having been loaded)
    mBase.add(&mOptionsMenu, (mBase.getWidth() / 2) - (mOptionsMenu.getWidth() / 2), (mBase.getHeight() / 2) - (mOptionsMenu.getHeight() / 2));

    // Setup the game over widget.
    mGameOverWidget.setVisible(false);
    mGameOverWidget.setSize((mBase.getWidth() * 3) / 4, (mBase.getWidth() * 3) / 4);
    mBase.add(&mGameOverWidget, (mBase.getWidth() / 2) - (mGameOverWidget.getWidth() / 2), (mBase.getHeight() / 2) - (mGameOverWidget.getHeight() / 2));

    // Hide the message OSD.
    mMessageOSD.setVisible(false);

    // Add the OSDs to the screen.
    mBase.add(&mMessageOSD);

    // Load the level at the current difficulty.
    mLevel = new Level(mDifficulty, mPlayer);

    // Set level listeners.
    mLevel->setInterfaceListener(this);
    mLevel->addEventListener(this);

    // After the listeners are set, load the level. (this must be done after setting the listeners)
    mLevel->load();
}

void GameScreen::logic()
{
	// Before any logic has been done, check if the next level should be loaded.
	if(mLoadLevel)
	{
		// Unload the current level.
		mLevel->removeEventListener(this);
		delete mLevel;

		// Increase the difficulty and go to the next level.
		mLevel = new Level(++mDifficulty, mPlayer);
		mLevel->addEventListener(this);
		mLevel->setInterfaceListener(this);
		mLevel->load(); // This must be done after setting the listeners.

		// The next level is loaded.
		mLoadLevel = false;
	}

    // Only do game logic if the game is not paused and neither the options menu or
	// the message display widget is being shown.
    if(!mIsPaused && !mMessageOSD.isVisible() && !mOptionsMenu.isVisible())
    {
		// Perform logic.
		mLevel->logic();
		mViewport.logic();
    }
}

void GameScreen::setViewportBounds(const Rectangle& bounds)
{
	mViewport.setBounds(bounds);
}

void GameScreen::setViewportFocus(const Entity* entity)
{
	mViewport.center(entity);
}

void GameScreen::setViewportFocus(int x, int y)
{
	mViewport.center(x, y);
}
