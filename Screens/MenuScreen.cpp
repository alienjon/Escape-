/*
 * MenuScreen.cpp
 *
 *  Created on: Jun 24, 2009
 *      Author: alienjon
 */
#include "MenuScreen.hpp"

#include <cmath>
#include <stdexcept>

#include "../Managers/AudioManager.hpp"
#include "../Managers/FontManager.hpp"
#include "../MapInfo/MapRule.hpp"
#include "../Managers/VideoManager.hpp"
#include "MenuScreenWidgets/NewGameMenu.hpp"

using std::runtime_error;
using std::string;

const string MAINMENU_MAPFILE = "MainMenu.map";

MenuScreen::MenuScreen() :
		mTitle(VideoManager::loadSurface(FILE_MENUSCREEN_TITLEIMAGE)),
//		mMap(MAPRULE_MENUSCREEN),
		mMap(MAINMENU_MAPFILE),
        mCurrentScreen(MAINMENUSCREEN_MAIN),
        mNextScreen(MAINMENUSCREEN_NULL),
        mSlideCounter(0)
{
    // Configure the header.
    mMessageBox.setFont(FontManager::get(FONT_DEFAULT));
    mMessageBox.setCaption("Welcome to Escape!");
    mMessageBox.setSize(mTitle.getWidth(), FontManager::get(FONT_DEFAULT)->getHeight());
    mMessageBox.setAlignment(gcn::Graphics::CENTER);
    mHeader.setBaseColor(gcn::Color(0, 0, 0, 255));
    mHeader.setSize(mTitle.getWidth(), mTitle.getHeight());
    mHeader.add(&mTitle, 0, 0);
    mHeader.add(&mMessageBox, 0, mHeader.getHeight() - mMessageBox.getHeight());
    mHeader.setFrameSize(4);

    // Set this widget as an action listener for each menu (for when buttons are pressed)
    mCreditsMenu.addEventListener(this);
    mLoadGameMenu.addEventListener(this);
    mMainMenu.addEventListener(this);
    mNewGameMenu.addEventListener(this);
    mOptionsMenu.addEventListener(this);

    // Configure the menu's container.
    mMenus.setSize(SCREEN_WIDTH * 3, SCREEN_HEIGHT * 3);
    mMenus.setOpaque(false);
    mBase.add(&mMenus, -(mMenus.getWidth() / 3), -(mMenus.getHeight() / 3));
    mMenus.add(&mNewGameMenu, 800, 0);
    mMenus.add(&mMainMenu, 800, 600);
    mMenus.add(&mCreditsMenu, 1600, 600);
    mMenus.add(&mLoadGameMenu, 800, 1200);
    mMenus.add(&mOptionsMenu, 0, 600);

    // Add the header last so it is on top.
    mBase.add(&mHeader, (mBase.getWidth() / 2) - (mHeader.getWidth() / 2), mHeader.getHeight() / 4);
}

MenuScreen::~MenuScreen()
{
	// @todo test with this removed, I shouldn't need it.
    mCreditsMenu.removeEventListener(this);
    mLoadGameMenu.removeEventListener(this);
    mMainMenu.removeEventListener(this);
    mNewGameMenu.removeEventListener(this);
    mOptionsMenu.removeEventListener(this);
}

void MenuScreen::mDisplay(const string& message)
{
    mMessageBox.setCaption(message);
}

void MenuScreen::mLogic_slideCamera()
{
    // Get the distance to move.
    double distance = pow(mSlideCounter++, SLIDING_RATE);

    // Move in the appropriate direction.
    //  1) Set the new position.
    //  2) If the screen has moved far enough:
    //      a) Set the final position
    //      b) Reset the moving variables.
    switch(mNextScreen)
    {
        case MAINMENUSCREEN_CREDITS:
        {
            mViewport.setX(mViewport.getX() + distance);
            if(mViewport.getX() >= SCREEN_WIDTH * 2)
            {
                mViewport.setX(SCREEN_WIDTH * 2);
                mCurrentScreen = mNextScreen;
                mNextScreen = MAINMENUSCREEN_NULL;
                mSlideCounter = 0;
            }
            break;
        }
        case MAINMENUSCREEN_LOADING:
        {
            mViewport.setY(mViewport.getY() + distance);
            if(mViewport.getY() >= SCREEN_HEIGHT * 2)
            {
                mViewport.setY(SCREEN_HEIGHT * 2);
                mCurrentScreen = mNextScreen;
                mNextScreen = MAINMENUSCREEN_NULL;
                mSlideCounter = 0;
            }
            break;
        }
        case MAINMENUSCREEN_NEW:
        {
            mViewport.setY(mViewport.getY() - distance);
            if(mViewport.getY() <= 0)
            {
                mViewport.setY(0);
                mCurrentScreen = mNextScreen;
                mNextScreen = MAINMENUSCREEN_NULL;
                mSlideCounter = 0;
            }
            break;
        }
        case MAINMENUSCREEN_OPTIONS:
        {
            mViewport.setX(mViewport.getX() - distance);
            if(mViewport.getX() <= 0)
            {
                mViewport.setX(0);
                mCurrentScreen = mNextScreen;
                mNextScreen = MAINMENUSCREEN_NULL;
                mSlideCounter = 0;
            }
            break;
        }
        default:
        {
            // Slide to the center of the screen (main menu)
            mLogic_slideToCenter(distance);
        }
    }
}

void MenuScreen::mLogic_slideToCenter(double distance)
{
    // Move towards the center, based on the current screen.
    switch(mCurrentScreen)
    {
        case MAINMENUSCREEN_CREDITS:
        {
            mViewport.setX(mViewport.getX() - distance);
            mMenus.setX(mMenus.getX() - distance);
            if(mViewport.getX() <= SCREEN_WIDTH)
            {
                mViewport.setX(SCREEN_WIDTH);
                mCurrentScreen = mNextScreen;
                mNextScreen = MAINMENUSCREEN_NULL;
                mSlideCounter = 0;
            }
            break;
        }
        case MAINMENUSCREEN_LOADING:
        {
            mViewport.setY(mViewport.getY() - distance);
            mMenus.setY(mMenus.getY() - distance);
            if(mViewport.getY() <= SCREEN_HEIGHT)
            {
                mViewport.setY(SCREEN_HEIGHT);
                mCurrentScreen = mNextScreen;
                mNextScreen = MAINMENUSCREEN_NULL;
                mSlideCounter = 0;
            }
            break;
        }
        case MAINMENUSCREEN_NEW:
        {
            mViewport.setY(mViewport.getY() + distance);
            mMenus.setY(mMenus.getY() + distance);
            if(mViewport.getY() >= SCREEN_HEIGHT)
            {
                mViewport.setY(SCREEN_HEIGHT);
                mCurrentScreen = mNextScreen;
                mNextScreen = MAINMENUSCREEN_NULL;
                mSlideCounter = 0;
            }
            break;
        }
        case MAINMENUSCREEN_OPTIONS:
        {
            mViewport.setX(mViewport.getX() + distance);
            mMenus.setX(mMenus.getY() + distance);
            if(mViewport.getX() >= SCREEN_WIDTH)
            {
                mViewport.setX(SCREEN_WIDTH);
                mCurrentScreen = mNextScreen;
                mNextScreen = MAINMENUSCREEN_NULL;
                mSlideCounter = 0;
            }
            break;
        }
        default:
        {
            throw runtime_error("MenuScreen::logic() -> Trying to slide from an invalid screen to center.");
        }
    }
}

void MenuScreen::eventOccurred(Event event, const std::string& content, CreatureMovedToPointListener* creatureMovedToPointListener)
{
    // If the action performed is requesting a move to a screen, move to that screen.
    if(event == EVENT_SLIDE_NEWMENU) // Go to the start a new game screen
    {
        mDisplay("Start a new game.");
        slideToScreen(MAINMENUSCREEN_NEW);
    }
    else if(event == EVENT_SLIDE_LOADMENU) // Go to the load a new game screen.
    {
        mDisplay("Select a game to load.");
        slideToScreen(MAINMENUSCREEN_LOADING);
    }
    else if(event == EVENT_SLIDE_OPTIONSMENU) // Go to the options screen.
    {
        mDisplay("Change game options.");
        slideToScreen(MAINMENUSCREEN_OPTIONS);
    }
    else if(event == EVENT_SLIDE_CREDITSMENU) // Go to the credits screen.
    {
        mDisplay("See the credits.");
        slideToScreen(MAINMENUSCREEN_CREDITS);
    }
    else if(event == EVENT_SLIDE_MAINMENU) // Go to the main menu screen.
    {
        mDisplay("Welcome to Escape!");
        slideToScreen(MAINMENUSCREEN_MAIN);
    }
    else if(event == EVENT_DISPLAYMESSAGE) // Display a message.
    {
        mDisplay(content);
    }
    else
    {
        // Push the event to the listeners (likely the game object)
        pushEvent(event, content);

        // Also consider this screen to have finished.
        mDone = true;
    }
}

void MenuScreen::draw(Renderer& renderer)
{
    // Set the drawing area based on the viewport.
	renderer.pushClipArea(gcn::Rectangle(-mViewport.getX(), -mViewport.getY(), mViewport.getWidth(), mViewport.getHeight()));

    // First draw the map.
	//@todo not sure what's wrong with the map...
//    mMap.drawLower(renderer);
//    mMap.drawMiddle(renderer);
//    mMap.drawUpper(renderer);
	renderer.setColor(COLOR_BLACK);
	renderer.fillRectangle(gcn::Rectangle(0, 0, mMap.getWidth(), mMap.getHeight()));

    // Pop the drawing area.
    renderer.popClipArea();
}

void MenuScreen::load(GUI* gui)
{
    // Set the GUI.
    gui->setBase(&mBase);

    // Set the camera to display the map.
    mViewport.setBounds(Rectangle(0, 0, mMap.getWidth(), mMap.getHeight()));

    // Set the camera's initial position.
    mViewport.setPosition((mMenus.getWidth() / 3), (mMenus.getHeight() / 3));

    // Start playing the music.
    AudioManager::playMusic("Game Sounds/Anitras Dance.mp3", -1, 3000); // @todo set the song as a variable.
}

void MenuScreen::logic()
{
    // If the next screen is not null, then we are sliding towards a screen.
    if(mNextScreen != MAINMENUSCREEN_NULL)
    {
        // Slide the screens.
        mLogic_slideCamera();

        // Offset the menus based on the new camera position.
        mMenus.setPosition(-mViewport.getX(), -mViewport.getY());
    }
}

void MenuScreen::slideToScreen(MainMenuScreen screen)
{
    // If the current screen is not the main menu screen, then we are automatically
    //  going to the main menu (beause that's in the center)
    mNextScreen = (mCurrentScreen == MAINMENUSCREEN_MAIN && screen != MAINMENUSCREEN_MAIN) ? screen : MAINMENUSCREEN_MAIN;
}

void MenuScreen::unload()
{
    // Stop the music.
    AudioManager::stopMusic(2000);
}

const double MenuScreen::SLIDING_RATE = 1.25;

const char* FILE_MENUSCREEN_TITLEIMAGE = "Images/TitleImage.png";

const char* DIR_SAVEDGAME = "Saved/";

const char* ID_MAINMENU_BUTTON_START = "START A NEW GAME";
const char* ID_MAINMENU_BUTTON_LOAD = "LOAD A SAVED GAME";
const char* ID_MAINMENU_BUTTON_OPTIONS = "CHANGE GAME OPTIONS";
const char* ID_MAINMENU_BUTTON_CREDITS = "SEE GAME CREDITS";
const char* ID_MAINMENU_BUTTON_MAIN = "BACK TO MAIN MENU";
const char* ID_MAINMENU_BUTTON_QUIT = "QUIT THE GAME";