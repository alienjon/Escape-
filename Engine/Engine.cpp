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
	mGui(0),
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

	// Do any Game specific stuff.
	mGui = new GUI(mRenderer, mInput);
	mGui->addGlobalKeyListener(this);
	mGui->getTop()->addActionListener(this);

	// Setup the FPS displays.
	mFont.loadFromFile("Fonts/VeraMono.ttf");
	mGameFPS.setFont(mFont);
	mGameFPS.setCharacterSize(18);
	mGameFPS.setColor(sf::Color::Magenta);
	mGameFPS.setStyle(sf::Text::Bold);
	mVideoFPS.setFont(mFont);
	mVideoFPS.setCharacterSize(18);
	mVideoFPS.setColor(sf::Color::Magenta);
	mVideoFPS.setStyle(sf::Text::Bold);
	mGameFPS.setPosition(0, 0);
	mVideoFPS.setPosition(0, mGameFPS.getCharacterSize());
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
    mGui->getTop()->removeActionListener(this);
    mGui->removeGlobalKeyListener(this);
    delete mGui;
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
        (*mCurrentScreen)->removeActionListener(this);
        this->removeActionListener(*mCurrentScreen);
        mGui->getTop()->removeKeyListener(*mCurrentScreen);
        mGui->getTop()->removeMouseListener(*mCurrentScreen);

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
    (*mCurrentScreen)->addActionListener(this);
    this->addActionListener(*mCurrentScreen);
    mGui->getTop()->addKeyListener(*mCurrentScreen);
    mGui->getTop()->addMouseListener(*mCurrentScreen);
    (*mCurrentScreen)->setRendererContextInterface(this);

    // Display the loading screen.
    mRenderer.clear();
    mDrawLoadingScreen();
    mRenderer.display();

    // Load the new screen.
    (*mCurrentScreen)->load(mGui);

    // If the old screen exists, delete it.
    if(oldScreen)
        delete oldScreen;
}

const RendererContext& Engine::getContext() const
{
	return mContext;
}

void Engine::keyPressed(gcn::KeyEvent& event)
{
	// Quit the game.
	if(isDebug() && event.getKey().getValue() == 'c' && event.isControlPressed())
		mRenderer.close();

	// Save a screenshot.
	if(event.getKey().getValue() == 'p' && event.isControlPressed())
	{
		static unsigned int i = 0;
		sf::Image shot = mRenderer.capture();
		string filename = "screenshot_" + toString(i++) + ".png";
		shot.saveToFile(filename);
		LOG("Screenshot saved as '" + filename + "'");
		return;
	}

	// Enable/Disable debugging.
	if(event.getKey().getValue() == gcn::Key::F1)
	{
		setDebug(!isDebug());
		if(isDebug())
			LOG("Debugging enabled");
		else
			LOG_TO_CONSOLE("Debugging disabled");
	}

	// Display engine settings.
	if(event.getKey().getValue() == gcn::Key::F2)
	{
		LOG_TO_CONSOLE("Screen Size: " + toString(mContext.mVideoMode.width) + " x " + toString(mContext.mVideoMode.height) + " (" + toString(mContext.mVideoMode.bitsPerPixel) + ")");
		LOG_TO_CONSOLE(string("Fullscreen: ") + ((mContext.mFullscreen) ? "true" : "false"));
		LOG_TO_CONSOLE(string("Vertical Sync: ") + ((mContext.mVerticalSync) ? "true" : "false"));
		LOG_TO_CONSOLE("Antialiasing: " + toString(mContext.mContextSettings.antialiasingLevel));
		LOG_TO_CONSOLE("Audio Enabled: TO BE IMPLEMENTED");//@todo implement audio enable
		LOG_TO_CONSOLE("Music Volume: TO BE IMPLEMENTED");//@todo implement music volume
		LOG_TO_CONSOLE("SFX Volume: TO BE IMPLEMENTED");//@todo implement sfx volume
	}

	// Toggle fullscreen.
	//@todo I can do this without the screen flickering.  It's changing the scale/window decorations.  Look into it?
	if(event.getKey().getValue() == gcn::Key::ENTER && event.isAltPressed())
	{
		RendererContext c = getContext();
		c.mFullscreen = !c.mFullscreen;
		updateContext(c);
		LOG(string("Fullscreen ") + (c.mFullscreen ? "enabled" : "disabled"));
	}
}

bool Engine::isDebug()
{
	return mDebug;
}

void Engine::run()
{
	// Start by creating (updating) the screen.
	updateContext(mContext);

    // Make sure all screens are cleared.
	for(list<Screen*>::iterator it = mScreens.begin(); it != mScreens.end(); ++it)
		delete *it;
    mScreens.clear();

    // Setup the game.
    mGameSetup();
    mLoadNextScreen();
    Timer gametimer, fpstimer;
    gametimer.start();
    fpstimer.start();
    unsigned int gamefps_count = 0, videofps_count = 0;

	// Basic game loop.
    while(mRenderer.isOpen())
    {
    	if(gametimer.getTime() > 1000/60)
    	{
			// Process the events.
			sf::Event event;
			while(mRenderer.pollEvent(event))
				mInput.pushInput(event);

			// Logic.
			(*mCurrentScreen)->logic();
			mGui->logic();
			gamefps_count++;
			gametimer.start();
    	}

		// Draw
    	mRenderer.clear();
		(*mCurrentScreen)->draw(mRenderer);
		mGui->draw();

		// If debugging, draw FPS info.
		if(isDebug())
		{
			mRenderer.draw(mGameFPS);
			mRenderer.draw(mVideoFPS);

			if(fpstimer.getTime() > 1000)
			{
				mGameFPS.setString("Game FPS: " + toString(gamefps_count));
				mVideoFPS.setString("VideoFPS: " + toString(videofps_count));
				gamefps_count = 0;
				videofps_count = 0;
				fpstimer.start();
			}
		}

        // Render the frame.
        mRenderer.display();
        videofps_count++;

        // If the screen has finished, then load the next screen.
        if((*mCurrentScreen)->isDone())
            mLoadNextScreen();
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
	mGui->setSize(mContext.mVideoMode.width, mContext.mVideoMode.height);
	mRenderer.setKeyRepeatEnabled(false);
    mRenderer.setFramerateLimit(100); // @note Sets the maximum framerate if vsync is disabled.
    mRenderer.setVerticalSyncEnabled(mContext.mVerticalSync);
}

void Engine::setDebug(bool state)
{
	mDebug = state;
}

bool Engine::mDebug = false;
