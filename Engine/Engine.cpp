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
#include "../Engine/VideoManager.hpp"

using std::ifstream;
using std::list;
using std::ofstream;
using std::runtime_error;
using std::string;

const char* CONFIG_FILE = "config.txt";

Engine::Engine() :
	mFullscreen(false),
	mVerticalSync(true),
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
				setScreenWidth(toInt(value));
			else if(keyword == "ScreenHeight")
				setScreenHeight(toInt(value));
			else if(keyword == "ScreenBPP")
				setScreenBPP(toInt(value));
			else if(keyword == "VerticalSync")
				mVerticalSync = (toLower(value) == "true") ? true : false;
			else if(keyword == "Fullscreen")
				mFullscreen = (toLower(value) == "true") ? true : false;
			else if(keyword == "BitDepth")
				mSettings.DepthBits = toInt(value);
			else if(keyword == "StencilBits")
				mSettings.StencilBits = toInt(value);
			else if(keyword == "Antialiasing")
				mSettings.AntialiasingLevel = toInt(value);
			else if(Engine::isDebug())
				Logger::log("Unknown entry in config.txt: " + keyword);
		}
	}
	else
		Logger::log("Configuration file cannot be loaded, using default settings.");
	settings.close();

	// Set other options.
	mRenderer.EnableKeyRepeat(false);

    // Create the managers.
    AudioManager::create();
    FontManager::create();
    VideoManager::create();

	// Do any Game specific stuff.
	mGui = new GUI(mRenderer, mInput);
	mGui->addGlobalKeyListener(this);
	mGui->getTop()->addActionListener(this);
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
	settings << "ScreenWidth:" << toString(mVideoMode.Width) << "\n";
	settings << "ScreenHeight:" << toString(mVideoMode.Height) << "\n";
	settings << "ScreenBPP:" << toString(mVideoMode.BitsPerPixel) << "\n";
	settings << "VerticalSync:" << (mVerticalSync ? "true" : "false") << "\n";
	settings << "Fullscreen:" << (mFullscreen ? "true" : "false") << "\n";
	settings << "BitDepth:" << toString(mSettings.DepthBits) << "\n";
	settings << "StencilBits:" << toString(mSettings.StencilBits) << "\n";
	settings << "Antialiasing:" << toString(mSettings.AntialiasingLevel) << "\n";
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

    // Load the new screen.
    (*mCurrentScreen)->load(mGui);

    // If the old screen exists, delete it.
    if(oldScreen)
        delete oldScreen;
}

void Engine::keyPressed(gcn::KeyEvent& event)
{
	// Quit the game.@todo remove during final version
	if(event.getKey().getValue() == 'c' && event.isControlPressed())
		mRenderer.Close();

	// Save a screenshot.
	if(event.getKey().getValue() == 'p' && event.isControlPressed())
	{
		static unsigned int i = 0;
		sf::Image shot = mRenderer.Capture();
		shot.SaveToFile("screenshot_" + toString(i++) + ".png");
		return;
	}

	// Enable/Disable debugging.
	if(event.getKey().getValue() == gcn::Key::F1)
	{
		setDebug(!isDebug());
		if(isDebug())
			Logger::log("Debugging enabled");
		else
			Logger::log("Debugging disabled");
	}
}

bool Engine::isDebug()
{
	return mDebug;
}

void Engine::run()
{
	// Start by creating (updating) the screen.
	updateScreen();

    // Make sure all screens are cleared.
	for(list<Screen*>::iterator it = mScreens.begin(); it != mScreens.end(); ++it)
		delete *it;
    mScreens.clear();

    // Setup the game.
    mGameSetup();
    mLoadNextScreen();

	// Basic game loop.
    while(mRenderer.IsOpened())
    {
    	// Process the events.
    	sf::Event event;
    	while(mRenderer.PollEvent(event))
    		mInput.pushInput(event);

    	// Logic.
    	(*mCurrentScreen)->logic();
    	mGui->logic();

		// Draw the non-gui.
		(*mCurrentScreen)->draw(mRenderer);

		// Draw the gui.
		mRenderer.SetView(mRenderer.GetDefaultView());
		mGui->draw();

        // Render the frame.
        mRenderer.Display();

        // If the screen has finished, then load the next screen.
        if((*mCurrentScreen)->isDone())
            mLoadNextScreen();
    }

    // Clean things up.
    mGameCleanup();
    mCleanUpScreens();
}

void Engine::updateScreen()
{
	mRenderer.Create(mVideoMode, GAME_NAME, (mFullscreen) ? sf::Style::Fullscreen : sf::Style::Titlebar, mSettings);
}

void Engine::setDebug(bool state)
{
	mDebug = state;
}

bool Engine::mDebug = false;
