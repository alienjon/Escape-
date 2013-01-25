/*
 * Game.cpp
 *
 *  Created on: Nov 7, 2011
 *      Author: alienjon
 */
#include "Game.hpp"

#include <stdexcept>

#include "../Engine/Colors.hpp"
#include "../Screens/GameScreen.hpp"
#include "../Game/Keywords.hpp"
#include "../Engine/Logger.hpp"
#include "../Game/TilesetManager.hpp"

const unsigned int LOADBAR_FRAMESIZE = 2;

using std::runtime_error;
using std::string;

Game::Game()
{
	// Create the tileset manager.
    TilesetManager::create();

	// Load all resources.
	mLoadResources();
}

Game::~Game()
{
	// Delete the tileset manager.
    TilesetManager::terminate();
}

void Game::mDrawResourceFrame(unsigned int percent, const string& title)
{
    // Just draw a black background for now.
	mRenderer._beginDraw();
    mRenderer.setColor(gcn::COLOR_BLACK);
    mRenderer.fillRectangle(gcn::Rectangle(0, 0, mRenderer.getSize().x, mRenderer.getSize().y));

    // Draw a loading bar.
    unsigned int width = (mRenderer.getSize().x / 4) + (LOADBAR_FRAMESIZE * 2),
				 height= (mRenderer.getSize().y / 16) + (LOADBAR_FRAMESIZE * 2);
    mRenderer.setColor(gcn::COLOR_BLUE);
    mRenderer.fillRectangle(gcn::Rectangle((mRenderer.getSize().x / 2) - (width / 2), (mRenderer.getSize().y / 2) - (height / 2), width, height));

    width -= (LOADBAR_FRAMESIZE * 2);
    height -= (LOADBAR_FRAMESIZE * 2);
    mRenderer.setColor(gcn::COLOR_CYAN);
    mRenderer.fillRectangle(gcn::Rectangle((mRenderer.getSize().x / 2) - (width / 2), (mRenderer.getSize().x / 2) - (height / 2), width * percent / 100, height));

    // Draw the text.@todo draw text
//    mRenderer.drawText(toString(percent) + ": Loading " + title, 0, mRenderer.GetHeight() - mRenderer.getFontHeight(), gcn::Graphics::LEFT);
    mRenderer._endDraw();
}

void Game::mGameCleanup()
{
}

void Game::mGameSetup()
{
	mScreens.push_back(new GameScreen(5));
	//@todo implement when done testing gamescreen.
//    // If the game is being debugged, then skip to the game screen.
//    if(Engine::isDebug())
//    	mScreens.push_back(new GameScreen(5));
//    else
//    {
//		/* The screens load in the following order:
//		  1) Trust credits.
//		  2) Game credits.
//		  3) Loading screen.
//		  4) Main menu.*/
//		mScreens.push_back(new SpriteCreditScreen(VideoManager::loadSurface(FILE_THETRUSTCREDIT_IMAGE), 2000, 750, 750));@todo remove when done testing
//		mScreens.push_back(new SpriteCreditScreen(VideoManager::loadSurface(FILE_ESCAPECREDIT_IMAGE), 2000));
//		mScreens.push_back(new MenuScreen());
//    }
}

void Game::mLoadResources()
{
    // First, determine the number of resources to be loaded.
    const double resourceCount = TilesetManager::determineSize();

    // Double check to make sure resources need to be loaded.
    if(resourceCount == 0)
        throw runtime_error("Engine::mLoadResources() -> No resources to load.");

    // The total number of resources currently loaded.
    double resourcesLoaded = 0;

    // Load the tilesets.
    do
    	mDrawResourceFrame((resourcesLoaded++ / resourceCount) * 100, TilesetManager::getCurrentResourceName());
    while(TilesetManager::loadResource());
}

void Game::action(const gcn::ActionEvent& event)
{
	if(event.getId() == ACTION_STARTGAME_EASY)
		mScreens.push_back(new GameScreen(1));
	else if(event.getId() == ACTION_STARTGAME_NORMAL)
		mScreens.push_back(new GameScreen(5));
	else if(event.getId() == ACTION_STARTGAME_HARD)
		mScreens.push_back(new GameScreen(10));
	else if(event.getId() == ACTION_QUIT)
		mRenderer.close();
	else if(event.getId() == ACTION_SHOWCURSOR)
		mRenderer.setMouseCursorVisible(true);
	else if(event.getId() == ACTION_HIDECURSOR)
		mRenderer.setMouseCursorVisible(false);
//	else if(event.getId() == ACTION_TO_MAINMENU)//@todo implement the main screen.
//		mScreens.push_back(new MenuScreen());
//	else if(event.getId() == ACTION_TO_CREDITSCREEN)//@todo review adding credit screens.
//    {
//    	string::size_type pos = 0;
//    	string credit_file	  = extractDataLine(content, pos, CHAR_DELIMITER_ALTERNATE);
//    	unsigned int fade_in  = toInt(extractDataLine(content, pos, CHAR_DELIMITER_ALTERNATE));
//    	unsigned int fade_out = toInt(extractDataLine(content, pos, CHAR_DELIMITER_ALTERNATE));
//    	mScreens.push_back(new SpriteCreditScreen(Sprite(VideoManager::loadSurface(credit_file)), 4000, fade_in, fade_out));
//    }
	else
		LOG("Invalid action requested: " + event.getId());
}
