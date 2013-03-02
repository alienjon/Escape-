/*
 * Game.cpp
 *
 *  Created on: Apr 30, 2009
 *      Author: alienjon
 */
#include "Engine.hpp"

#include <cctype>
#include <ctime>
#include <fstream>
#include <stdexcept>
#include <string>

#include "../Engine/AudioManager.hpp"
#include "../Engine/FontManager.hpp"
#include "../Game/Keywords.hpp"
#include "../Engine/Logger.hpp"
#include "../main.hpp"
#include "../Engine/Screen.hpp"
#include "../Engine/Timer.hpp"
#include "../Engine/VideoManager.hpp"

using std::ifstream;
using std::list;
using std::ofstream;
using std::runtime_error;
using std::string;

const char* CONFIG_FILE = "config.txt";

Engine::Engine() :
	mCurrentScreen(mScreens.end())
{
	// Seed the randomizer.
	srand(time(0));

	// Load saved video settings.
	ifstream settings;
	string line, keyword, value;
	settings.open(CONFIG_FILE, ifstream::in);
	if(settings.good())
	{
		while(getline(settings, line))
		{
			string::size_type pos = 0;
			keyword = extractDataLine(line, pos, ':');
			value	= extractDataLine(line, pos, ':');

			if(keyword.empty() || keyword[0] == '#')
				continue;
			else if(keyword == "ScreenWidth")
				mContext.mVideoMode.width = toInt(value);
			else if(keyword == "ScreenHeight")
				mContext.mVideoMode.height = toInt(value);
			else if(keyword == "ScreenBPP")
				mContext.mVideoMode.bitsPerPixel = toInt(value);
			else if(keyword == "VerticalSync")
				mContext.mVerticalSync = (toLower(value) == "true") ? true : false;
			else if(keyword == "Fullscreen")
				mContext.mFullscreen = (toLower(value) == "true") ? true : false;
			else if(keyword == "BitDepth")
				mContext.mContextSettings.depthBits = toInt(value);
			else if(keyword == "StencilBits")
				mContext.mContextSettings.stencilBits = toInt(value);
			else if(keyword == "Antialiasing")
				mContext.mContextSettings.antialiasingLevel = toInt(value);
			else if(Engine::isDebug())
				LOG("Unknown entry in config.txt: " + keyword);
		}
	}
	else
		LOG("Configuration file cannot be loaded, using default settings.");
	settings.close();

    // Create the managers.
    AudioManager::create();
    FontManager::create();
    VideoManager::create();

	// Setup the FPS displays.
	mFont.loadFromFile("Fonts/VeraMono.ttf");
	mFPSDisplay.setFont(mFont);
	mFPSDisplay.setCharacterSize(18);
	mFPSDisplay.setColor(sf::Color::Magenta);
	mFPSDisplay.setStyle(sf::Text::Bold);
	mFPSDisplay.setPosition(0, 0);
}

Engine::~Engine()
{
	// Save the settings.
	ofstream settings;
	settings.open(CONFIG_FILE, std::ofstream::out);
	settings << "##\n";
	settings << "# Configuration file.\n";
	settings << "#\n";
	settings << "# Commented lines begin with a '#' and the entire line is ignored.\n";
	settings << "# All other lines have a keyword and a value separated by a colon on a single line.\n";
	settings << "##\n";
	settings << "ScreenWidth:" << toString(mContext.mVideoMode.width) << "\n";
	settings << "ScreenHeight:" << toString(mContext.mVideoMode.height) << "\n";
	settings << "ScreenBPP:" << toString(mContext.mVideoMode.bitsPerPixel) << "\n";
	settings << "VerticalSync:" << (mContext.mVerticalSync ? "true" : "false") << "\n";
	settings << "Fullscreen:" << (mContext.mFullscreen ? "true" : "false") << "\n";
	settings << "BitDepth:" << toString(mContext.mContextSettings.depthBits) << "\n";
	settings << "StencilBits:" << toString(mContext.mContextSettings.stencilBits) << "\n";
	settings << "Antialiasing:" << toString(mContext.mContextSettings.antialiasingLevel) << "\n";
	settings.close();

	mCleanUpScreens();

    // Delete the objects.
    AudioManager::terminate();
    FontManager::terminate();
    VideoManager::terminate();
}

void Engine::mCleanUpScreens()
{
	// Delete any remaining screens and clear them.
	for(list<Screen*>::iterator it = mScreens.begin(); it != mScreens.end(); ++it)
		delete (*it);
	mScreens.clear();
}

void Engine::mLoadNextScreen()
{
    // The old screen.
    Screen* oldScreen = 0;

    // If the next screen is not the end of the screens list, then unload the current screen.
    if(mCurrentScreen != mScreens.end())
    {
        // Remove the listeners.
        (*mCurrentScreen)->removeEventListener(this);
        removeEventListener(*mCurrentScreen);

        // Tell the screen to unload itself.
        (*mCurrentScreen)->unload();

        // Set the old screen for deletion later (it needs to be used for mGui->setBase())
        oldScreen = *mCurrentScreen;

        // Remove it from the list.
        mScreens.pop_front();
    }

    // The current screen should never be the last screen.
    if(mScreens.empty())
        throw runtime_error("Engine::mLoadNextScreen() -> No screens loaded.");

    // Set the new screen.
    mCurrentScreen = mScreens.begin();

    // Set listeners.
    (*mCurrentScreen)->addEventListener(this);
    addEventListener(*mCurrentScreen);
    (*mCurrentScreen)->setRendererContextInterface(this);

    // Display the loading screen.
    mDrawLoadingScreen();
    mRenderer.display();

    // Load the new screen.
    (*mCurrentScreen)->load(mRenderer.getDefaultView());

    // If the old screen exists, delete it.
    if(oldScreen)
        delete oldScreen;
}

const RendererContext& Engine::getContext() const
{
	return mContext;
}

bool Engine::handleInput(const sf::Event& event)
{
	// Quit the game.
	if(isDebug() && event.key.code == sf::Keyboard::C && event.key.control)
	{
		mRenderer.close();
		return true;
	}

	// Save a screenshot.
	if(event.key.code == sf::Keyboard::P && event.key.control)
	{
		static unsigned int i = 0;
		sf::Image shot = mRenderer.capture();
		string filename = "screenshot_" + toString(i++) + ".png";
		shot.saveToFile(filename);
		LOG("Screenshot saved as '" + filename + "'");
		return true;
	}

	// Enable/Disable debugging.
	if(event.key.code == sf::Keyboard::F1)
	{
		setDebug(!isDebug());
		if(isDebug())
			LOG("Debugging enabled");
		else
			LOG_TO_CONSOLE("Debugging disabled");
		return true;
	}

	// Display engine settings.
	if(event.key.code == sf::Keyboard::F2)
	{
		LOG_TO_CONSOLE("Screen Size: " + toString(mContext.mVideoMode.width) + " x " + toString(mContext.mVideoMode.height) + " (" + toString(mContext.mVideoMode.bitsPerPixel) + ")");
		LOG_TO_CONSOLE(string("Fullscreen: ") + ((mContext.mFullscreen) ? "true" : "false"));
		LOG_TO_CONSOLE(string("Vertical Sync: ") + ((mContext.mVerticalSync) ? "true" : "false"));
		LOG_TO_CONSOLE("Antialiasing: " + toString(mContext.mContextSettings.antialiasingLevel));
		LOG_TO_CONSOLE("Audio Enabled: TO BE IMPLEMENTED");//@todo implement audio enable
		LOG_TO_CONSOLE("Music Volume: TO BE IMPLEMENTED");//@todo implement music volume
		LOG_TO_CONSOLE("SFX Volume: TO BE IMPLEMENTED");//@todo implement sfx volume
		return true;
	}

	// Toggle fullscreen.
	//@todo I can do this without the screen flickering.  It's changing the scale/window decorations.  Look into it?
	if(event.key.code == sf::Keyboard::Return && event.key.control)
	{
		RendererContext c = getContext();
		c.mFullscreen = !c.mFullscreen;
		updateContext(c);
		LOG(string("Fullscreen ") + (c.mFullscreen ? "enabled" : "disabled"));
		return true;
	}

	// If we've reached here, then the event wasn't used.
	return false;
}

bool Engine::isDebug()
{
	return mDebug;
}

void Engine::run()
{
	// Start by creating (updating) the screen.
	updateContext(mContext);

	// Initialize the GUI.
	/*
	 * @fixme The GUI seems to only work AFTER the video context is created.  When there is only the game
	 * screen that is being used that works fine, but when the context is recreated - such as when
	 * the resolution of the game is redone - I'm not sure that the GUI will work after that.  If
	 * that happens then I will probably want to specifically call 'destroy' on the GUI system
	 * and then re-initialize.
	 */
	mGUI.initialize();

    // Make sure all screens are cleared.
	for(list<Screen*>::iterator it = mScreens.begin(); it != mScreens.end(); ++it)
		delete *it;
    mScreens.clear();

    // Setup the game.
    mGameSetup();

    // Load the first game screen.
    mLoadNextScreen();

    // FPS display and information.
    Timer frameTimer, gameTimer;
    frameTimer.start();
    gameTimer.start();
    unsigned int lastFrameTime = 0, frameCount = 0;

	// Basic game loop.
    while(mRenderer.isOpen())
    {
		/* HANDLE INPUT */
		sf::Event event;
		while(mRenderer.pollEvent(event))
		{
			// Have the engine handle input first.
			if(handleInput(event))
				continue;
			// Then check for the GUI to handle input.
			else if(mGUI.handleInput(event))
				continue;
			// Otherwise pass the input along to the screen.
			else
				(*mCurrentScreen)->handleInput(event);
		}

		/* LOGIC */
		(*mCurrentScreen)->logic(gameTimer.getTime() - lastFrameTime);
        lastFrameTime = gameTimer.getTime();

        // Calculate the FPS.
		if(frameTimer.getTime() > 1000)
		{
			mFPSDisplay.setString("FPS: " + toString(frameCount));
			frameCount = 0;
			frameTimer.start();
		}

		// Clear the screen and draw SFML stuff.
    	mRenderer.clear();

    	mRenderer.pushGLStates(); // Needed for GUI to display appropriately.
		(*mCurrentScreen)->draw(mRenderer);

		// If debugging, draw FPS info.
		if(isDebug())
		{
			mRenderer.draw(mFPSDisplay);
		}
		mRenderer.popGLStates(); // Needed for GUI to display appropriately.

		// Draw the GUI on top.
		mGUI.draw();

		// Render the frame.
		mRenderer.display();

        // If the screen has finished, then load the next screen.
        if((*mCurrentScreen)->isDone())
            mLoadNextScreen();

        // The frame has completed.
        frameCount++;
    }

    // Clean things up.
    mGameCleanup();
    mCleanUpScreens();
}

void Engine::updateContext(const RendererContext& context)
{
	// Check the video mode.
	if(isDebug())
	{
		string log = "Updating Video Mode: ";
		context.mVideoMode.isValid() ? LOG(log + "valid") : LOG(log + "invalid");
	}

	// The renderer context.
	mContext = context;

	// Recreate the renderer.
	mRenderer.create(mContext.mVideoMode, GAME_NAME, (mContext.mFullscreen) ? sf::Style::Fullscreen : sf::Style::Titlebar, mContext.mContextSettings);

	// Set other options that are defaulted when the renderer is re-created.
	mRenderer.setKeyRepeatEnabled(false);
    mRenderer.setVerticalSyncEnabled(mContext.mVerticalSync);
	mRenderer.setMouseCursorVisible(false); // Only use the CEGUI cursor.
}

void Engine::setDebug(bool state)
{
	mDebug = state;
}

bool Engine::mDebug = false;
