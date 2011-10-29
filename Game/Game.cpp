/*
 * Game.cpp
 *
 *  Created on: Apr 30, 2009
 *      Author: alienjon
 */
#include "Game.hpp"

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <string>

#include "GUI.hpp"
#include "../Game/Level.hpp"
#include "../Engine/Logger.hpp"
#include "../Engine/Renderer.hpp"
#include "../Engine/Timer.hpp"

#include "../Managers/AnimationManager.hpp"
#include "../Managers/AudioManager.hpp"
#include "../Managers/FontManager.hpp"
#include "../Screens/GameScreen.hpp"
#include "../Screens/MenuScreen.hpp"
#include "../Entities/Player.hpp"
#include "../Screens/Screen.hpp"
#include "../Screens/SpriteCreditScreen.hpp"
#include "../Managers/TilesetManager.hpp"
#include "../Managers/VideoManager.hpp"

using std::list;
using std::runtime_error;
using std::string;

const unsigned int LOADBAR_FRAMESIZE = 2;

Game::Game() : mIsRunning(true),
               mCurrentScreen(mScreens.end()),
               mToggleFullscreen(false),
               mToggleScreenshot(false),
               mToggleDebug(false),
               mToggleVideoInfo(false)
{
    /* Seed the randomizer */
    srand(time(0));

    // Create the managers.
    AudioManager::create();
    VideoManager::create();
    AnimationManager::create();
    FontManager::create();
    TilesetManager::create();

    // Create the GUI after both the renderer and the font manager, as it needs both for initialization.
    mGui = new GUI(&mRenderer);

	// Finally, load all resources.
	mLoadResources();
}

Game::~Game()
{
	// Clean up any remaining screens.
	mCleanUp();

    // Delete the objects (delete them in reverse order)
    TilesetManager::terminate();
    AnimationManager::terminate();
    VideoManager::terminate();
    FontManager::terminate();
    AudioManager::terminate();
    delete mGui;
}

void Game::mCleanUp()
{
    // Delete any remaining screens and clear them.
    for(list<Screen*>::iterator it = mScreens.begin(); it != mScreens.end(); ++it)
    {
    	delete (*it);
    }
    mScreens.clear();
}

void Game::mDraw()
{
	// Start drawing non-gui.
    mRenderer._beginDraw();

	// Draw the non-gui.
    (*mCurrentScreen)->draw(mRenderer);

    // End drawing the non-gui.
    mRenderer._endDraw();

    // Draw the gui.
    mGui->draw();

    // Draw the cursor.
    mRenderer._beginDraw();
    mCursor.draw(mRenderer);
    mRenderer._endDraw();
}

void Game::mDrawResourceFrame(unsigned int percent, const string& title)
{
	// Begin drawing.
	mRenderer._beginDraw();

    // Just draw a black background for now.
    mRenderer.setColor(COLOR_BLACK);
    mRenderer.fillRectangle(gcn::Rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

    // Draw a loading bar.
    unsigned int width = (SCREEN_WIDTH / 4) + (LOADBAR_FRAMESIZE * 2),
				 height= (SCREEN_HEIGHT / 16) + (LOADBAR_FRAMESIZE * 2);
    mRenderer.setColor(COLOR_MENU_DARK);
    mRenderer.fillRectangle(Rectangle((SCREEN_WIDTH / 2) - (width / 2), (SCREEN_HEIGHT / 2) - (height / 2), width, height));

    width -= (LOADBAR_FRAMESIZE * 2);
    height -= (LOADBAR_FRAMESIZE * 2);
    mRenderer.setColor(COLOR_MENU_LIGHT);
    mRenderer.fillRectangle(Rectangle((SCREEN_WIDTH / 2) - (width / 2), (SCREEN_HEIGHT / 2) - (height / 2), width * percent / 100, height));

    // Draw the text.
    mRenderer.drawText(toString(percent) + ": Loading " + title, 0, SCREEN_HEIGHT - mRenderer.getFontHeight(), gcn::Graphics::LEFT);

    // Finally, render the screen.
    mRenderer.render();

    // End drawing.
    mRenderer._endDraw();
}

void Game::mHandleInput()
{
    // Handle input.
	mInput.handleInput(mGui);

    /*
     * All game level controls should function and then exit (don't allow further input)
     * This way I should avoid problems of duplicate commands in higher functioning code.
     */

	// Quit the game.
	if(mInput.isKeyPressed(SDLK_c) && mInput.isControlPressed())
	{
		mIsRunning = false;
		return;
	}

	// Toggle fullscreen.
	if(!mToggleFullscreen && mInput.isKeyPressed(SDLK_RETURN) && mInput.isAltPressed())
	{
		mRenderer.toggleFullscreen();
		mToggleFullscreen = true;
		return;
	}
	else if(mInput.isKeyPressed(SDLK_RETURN) && mInput.isAltPressed())
	{
		mToggleFullscreen = false;
	}

	// Save a screenshot.
	if(!mToggleScreenshot && mInput.isKeyPressed(SDLK_p) && mInput.isAltPressed())
	{
		mRenderer.takeScreenshot();
		mToggleScreenshot = true;
		return;
	}
	else if (mInput.isKeyPressed(SDLK_p) && mInput.isAltPressed())
	{
		mToggleScreenshot = false;
	}

	// Enable/Disable debugging.
	if(!mToggleDebug && mInput.isKeyPressed(SDLK_F1))
	{
		setDebug(!isDebug());
		mToggleDebug = true;

		if(isDebug())
		{
			Logger::log("Debugging enabled");
		}
		else
		{
			Logger::log("Debugging disabled");
		}
		return;
	}
	else if(!mInput.isKeyPressed(SDLK_F1))
	{
		mToggleDebug = false;
	}

	// Display video info.
	if(!mToggleVideoInfo && mInput.isKeyPressed(SDLK_F2))
	{
		VideoManager::displayVideoInfo();
		mToggleVideoInfo = true;
		return;
	}
	else if(mInput.isKeyPressed(SDLK_F2))
	{
		mToggleVideoInfo = false;
	}

	// Set the cursor's position.
	mCursor.setPosition(mInput.getMouseX(), mInput.getMouseY());

    // Pass info to the screen if input is being accepted.
	(*mCurrentScreen)->handleInput(mInput);
}

void Game::mLoadNextScreen()
{
    // The old screen.
    Screen* oldScreen = 0;

    // If the next screen is not the end of the screens list, then unload the current screen.
    if(mCurrentScreen != mScreens.end())
    {
        // Remove the listeners.
        (*mCurrentScreen)->removeEventListener(this);

        // Tell the screen to unload itself.
        (*mCurrentScreen)->unload();

        // Set the old screen for deletion later (it needs to be used for mGui->setBase())
        oldScreen = *mCurrentScreen;

        // Remove it from the list.
        mScreens.pop_front();
    }

    // The current screen should never be the last screen.
    if(mScreens.empty())
    {
        throw runtime_error("Game::mLoadNextScreen() -> No screens loaded.");
    }

    /* Now, load the new screen and configure it */

    // Set the new screen.
    mCurrentScreen = mScreens.begin();

    // Load the new screen.
    (*mCurrentScreen)->load(mGui);

    // Set listeners.
    (*mCurrentScreen)->addEventListener(this);

    // If the old screen exists, delete it.
    if(oldScreen)
    {
        delete oldScreen;
    }
}

void Game::mLoadResources()
{
    // First, determine the number of resources to be loaded.
    const double resourceCount = AnimationManager::determineSize() + TilesetManager::determineSize();

    // Double check to make sure resources need to be loaded.
    if(resourceCount == 0)
    {
        throw runtime_error("Game::mLoadResources() -> No resources to load.");
    }

    // The total number of resources currently loaded.
    double resourcesLoaded = 0;

    // Load the animations.
    do
    {
        mDrawResourceFrame((resourcesLoaded++ / resourceCount) * 100, AnimationManager::getCurrentResourceName());
    }
    while(AnimationManager::loadResource());

    // Load the tilesets.
    do
    {
    	mDrawResourceFrame((resourcesLoaded++ / resourceCount) * 100, TilesetManager::getCurrentResourceName());
    }
    while(TilesetManager::loadResource());

    // Load the cursor.
    mCursor.load();
}

void Game::mLogic()
{
    (*mCurrentScreen)->logic();
    mGui->logic();
    mCursor.logic();
}

void Game::eventOccurred(Event event, const string& content, CreatureMovedToPointListener* creatureMovedToPointListener)
{
    switch(event)
    {
        case EVENT_STARTEASY:
        case EVENT_STARTNORMAL:
        case EVENT_STARTHARD:
        {
            // Start a new game.
        	mScreens.push_back(new GameScreen(event));
            break;
        }
        case EVENT_QUIT:
        {
            mIsRunning = false;
            break;
        }
        case EVENT_MAINMENU:
        {
            mScreens.push_back(new MenuScreen());
            break;
        }
        case EVENT_ADDCREDITSCREEN:
        {
        	string::size_type pos = 0;
        	string credit_file	  = extractDataLine(content, pos, CHAR_DELIMITER_ALTERNATE);
        	unsigned int fade_in  = toInt(extractDataLine(content, pos, CHAR_DELIMITER_ALTERNATE));
        	unsigned int fade_out = toInt(extractDataLine(content, pos, CHAR_DELIMITER_ALTERNATE));
        	mScreens.push_back(new SpriteCreditScreen(Sprite(VideoManager::loadSurface(credit_file)), 4000, fade_in, fade_out));
        }
        default: // Don't do anything.
        {}
    }
}

bool Game::isDebug()
{
	return m_debug;
}

void Game::run()
{
    // Make sure all screens are cleared.
	for(list<Screen*>::iterator it = mScreens.begin(); it != mScreens.end(); ++it)
	{
		delete *it;
	}
    mScreens.clear();

    // If the game is being debugged, then skip to the game screen.
    if(Game::isDebug())
    {
    	mScreens.push_back(new GameScreen(EVENT_STARTNORMAL));
    }
    else
    {
		// The screens load in the following order:
		//  1) Trust credits.
		//  2) Game credits.
		//  3) Loading screen.
		//  4) Main menu.
//		mScreens.push_back(new SpriteCreditScreen(VideoManager::loadSurface(FILE_THETRUSTCREDIT_IMAGE), 2000, 750, 750));@todo remove when done testing
//		mScreens.push_back(new SpriteCreditScreen(VideoManager::loadSurface(FILE_ESCAPECREDIT_IMAGE), 2000));
		mScreens.push_back(new MenuScreen());
    }

    // Load the initial screen.
    mLoadNextScreen();

    // The current tick.
    unsigned int current_tick = 0;

    while(mIsRunning)
    {
    	// Basic game loop.
        mHandleInput();
        mLogic();
        mDraw();

        // Render the frame.
        mRenderer.render();

        // If the screen has finished, then load the next screen.
        if((*mCurrentScreen)->isDone())
        {
            mLoadNextScreen();
        }

		// Add a frame cap to avoid excessive CPU usage.
		if((SDL_GetTicks() - current_tick) < (1000 / FRAMERATE))
		{
			SDL_Delay((1000 / FRAMERATE) - (SDL_GetTicks() - current_tick));
		}

		// Update the current tick.
		current_tick = SDL_GetTicks();

        // Frame is finished.
        gFPSCounter++;
    }

    mCleanUp();
}

void Game::setDebug(bool state)
{
	m_debug = state;
}

bool Game::m_debug = false; // @todo Implement toggling, debug, etc...

const string GAME_NAME = "Escape!";
const string GAME_VERSION = "0.0.0";

int gFPSCounter = 0;

const unsigned int FRAMERATE = 100;

const char* FILE_THETRUSTCREDIT_IMAGE = "Images/TrustCredit.png";
const char* FILE_ESCAPECREDIT_IMAGE = "Images/EscapeCredit.png";

const char* GAME_SAVEDGAME_EXTENSION = ".esc";
