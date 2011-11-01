/*
 * MenuScreen.hpp
 *
 *  Created on: Jun 24, 2009
 *      Author: alienjon
 */
#ifndef MENUSCREEN_HPP_
#define MENUSCREEN_HPP_

#include <list>
#include <string>

#include "MenuScreenWidgets/CreditsMenu.hpp"
#include "../guichan.hpp"
#include "MenuScreenWidgets/MainMenu.hpp"
#include "../Game/Map.hpp"
#include "MenuScreenWidgets/NewGameMenu.hpp"
#include "MenuScreenWidgets/OptionsMenu.hpp"
#include "../Engine/Renderer.hpp"
#include "Screen.hpp"

/**
 * @brief The menu screen displays the main menu to the user and allows various functionality.
 *
 * The menu screen layout follows:
 * *-----------*
 * |---|---|---|
 * |-1-|-2-|-3-|    2) New Game Menu :
 * |---|---|---|
 * -------------    4) @todo Empty area? :
 * |---|---|---|
 * |-4-|-5-|-6-|    5) Main Menu : goes to other screens: start a new game; load a saved game; options; credits; quit
 * |---|---|---|
 * -------------    6) Credits Menu :
 * |---|---|---|
 * |-7-|-8-|-9-|    8) Load Game Menu :
 * |---|---|---|
 * *-----------*
 *
 * The above guide indicates what each menu does.  The only main menu option that does not go to a menu
 * is the 'quit' option.  This will immediately quit the game.  All other options go to another menu.
 *
 * This widget is the overall container for each menu, so it needs to be the size of 9 screens (note above)
 * even though it only uses 5 of them.
 */
class MenuScreen : public gcn::ActionListener, public Screen
{
    public:
    enum MainMenuScreen
    {
        MAINMENUSCREEN_NULL,
        MAINMENUSCREEN_CREDITS,
        MAINMENUSCREEN_MAIN,
        MAINMENUSCREEN_NEW,
        MAINMENUSCREEN_OPTIONS
    };

    /**
     * @brief The menu screen lets the player start a new game, load a saved game, etc...
     */
    MenuScreen();
    virtual ~MenuScreen();

    /**
     * @brief An action occurred.
     * @param event The event's details.
     */
    virtual void action(const gcn::ActionEvent& event);

    /**
     * @brief Draw the screen.
     * @param renderer The graphics object to draw with.
     */
    virtual void draw(Renderer& renderer);

    /**
     * @brief Perform anything necessary to prepare this screen for displaying what it needs to.
     * @param gui The gui object to load menu info.
     */
    virtual void load(GUI* gui);

    /**
     * @brief Perform logic.
     */
    virtual void logic();

    /**
     * @brief Slide to the requested screen.
     * @param screen The main menu screen to slide to.
     */
    virtual void slideToScreen(MainMenuScreen screen);

    /**
     * @brief This unloads the screen and finalizes any further actions to allow the screen to be safetly deleted.
     */
    virtual void unload();

    private:
    /**
     * The sliding rate.
     */
    static const double SLIDING_RATE;

    /**
     * @brief Display a message.
     * @param message The message to display.
     */
    void mDisplay(const std::string& message);

    /**
     * @brief Split of a logic step to slide the menus.
     */
    void mLogic_slideCamera();

    /**
     * @brief Split of logic to slide to the center of screen.
     * @param distance The distance is calculated in slide menus, so just pass it here to keep the same value.
     */
    void mLogic_slideToCenter(double distance);

    /**
     * A container for the title image and the message box.
     */
    gcn::Container mHeader;

    /**
     * The title image.
     */
    gcn::Icon mTitle;

    /**
     * The message box.
     */
    gcn::Label mMessageBox;

    /**
     * The 5 menus and their holding container.
     */
    gcn::Container mMenus;
    CreditsMenu mCreditsMenu;
    MainMenu mMainMenu;
    NewGameMenu mNewGameMenu;
    OptionsMenu mOptionsMenu;

    /**
     * The menu screen has a map as it's background, instead of as static image.
     */
    Map mMap;

    /**
     * The currently displaying screen.
     */
    MainMenuScreen mCurrentScreen;

    /**
     * The screen we are sliding towards.
     */
    MainMenuScreen mNextScreen;

    /**
     * The sliding counter.
     */
    double mSlideCounter;
};

extern const char* FILE_MENUSCREEN_TITLEIMAGE;

extern const char* FILE_MENUSCREEN_BACKGROUND_AUDIO;

extern const char* DIR_SAVEDGAME;

extern const char* ID_MAINMENU_BUTTON_START;
extern const char* ID_MAINMENU_BUTTON_OPTIONS;
extern const char* ID_MAINMENU_BUTTON_CREDITS;
extern const char* ID_MAINMENU_BUTTON_MAIN;
extern const char* ID_MAINMENU_BUTTON_QUIT;

#endif /* MENUSCREEN_HPP_ */
