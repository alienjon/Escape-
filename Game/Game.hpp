/*
 * Game.hpp
 *
 *  Created on: Apr 30, 2009
 *      Author: alienjon
 */
#ifndef GAME_HPP_
#define GAME_HPP_

#include <list>
#include <string>

#include "../Engine/Cursor.hpp"
#include "../guichan.hpp"
#include "../Game/Input.hpp"
#include "../Engine/Renderer.hpp"
#include "../Engine/Timer.hpp"

class GUI;
class Level;
class Player;
class Screen;

/**
 * @brief The game object itself.  Manages higher level aspects of the game.
 *
 * Manages screens as interfaces to the game itself.
 */
class Game : public gcn::ActionListener
{
    public:
    /**
     * @brief Determine the debugging state.
     * @return The debugging state.
     */
    static bool isDebug();

    /**
     * @brief Set the debugging state.
     * @param state The state.
     */
    static void setDebug(bool state);

    /**
     * @brief The game object handles all meta-game issues.
     */
    Game();
    virtual ~Game();

    /**
     * @brief An action occurred.
     * @param event The event details.
     */
    virtual void action(const gcn::ActionEvent& event);

    /**
     * @brief Run the game.
     */
    void run();

    private:
    /**
     * The debug state.
     */
    static bool m_debug;

    /**
     * @brief Do any needed cleaning up.
     */
    void mCleanUp();

    /**
     * @brief Draw the screen.
     */
    void mDraw();

    /**
     * @brief Draw a loading resource frame.
     * @param percent The percent drawn.
     * @param title The title of the animation being loaded.
     */
    void mDrawResourceFrame(unsigned int percent, const std::string& title);

    /**
     * @brief Handle input.
     */
    void mHandleInput();

    /**
     * @brief Unload the current screen and load the next screen.
     * @note Will throw an exception if there are no more screens to load.
     */
    void mLoadNextScreen();

    /**
     * @brief Load the game resources.
     */
    void mLoadResources();

    /**
     * @brief Perform logic.
     */
    void mLogic();

    // True if the game is currently running.
    bool mIsRunning;

    /**
     * The video object.
     */
    Renderer mRenderer;

    /**
     * The GUI object.
     */
    GUI* mGui;

    /**
     * The input event.
     */
    Input mInput;

    /**
     * The key interval timer.
     * Note: This is needed so that when the keys are released, they can be read as being released at the same time.
     *          SDL checks for input events every millisecond, which means that even if the player releases two keys
     *          (notably directional keys) at the 'same time', they are read as several milliseconds apart, meaning
     *          that they are read as not actually being released at the same time.  This timer fixes that, by only
     *          allowing checking for a specified amount of time (see KEYINTERVAL in main.hpp.
     */
    Timer mKeyIntervalTimer;

    /**
     * The list of screens.
     */
    std::list<Screen*> mScreens;

    /**
     * The current screen.
     */
    std::list<Screen*>::iterator mCurrentScreen;

    /**
     * These values remember if certain activities were performed recently.
     */
    bool mToggleFullscreen, mToggleScreenshot, mToggleDebug, mToggleVideoInfo;

    /**
     * The game cursor.
     */
    Cursor mCursor;
};

/*
 * The name and version information for the game.
 */
extern const std::string GAME_NAME;
extern const std::string GAME_VERSION;

// The FPS counter.
extern int gFPSCounter;

// The framerate cap.
extern const unsigned int FRAMERATE;

// The filename's for this credits screens images.
extern const char* FILE_THETRUSTCREDIT_IMAGE;
extern const char* FILE_ESCAPECREDIT_IMAGE;

// A saved game's file extension.
extern const char* GAME_SAVEDGAME_EXTENSION;

#endif /* GAME_HPP_ */
