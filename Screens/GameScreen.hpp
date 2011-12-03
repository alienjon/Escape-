/*
 * GameScreen.hpp
 *
 *  Created on: Jun 24, 2009
 *      Author: alienjon
 */
#ifndef GAMESCREEN_HPP_
#define GAMESCREEN_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../Listeners/ChangeScoreListener.hpp"
#include "../Widgets/GameOptionsWidget.hpp"
#include "../Engine/GUI.hpp"
#include "../Engine/guichan.hpp"
//#include "../Widgets/GameScreenMenuBar.hpp"
#include "../Game/Level.hpp"
#include "../Widgets/LevelCompleteWidget.hpp"
#include "../Entities/Player.hpp"
#include "../Engine/Screen.hpp"
#include "../Interfaces/TimeChangeInterface.hpp"
#include "../Listeners/TimeChangeListener.hpp"
#include "../Engine/Timer.hpp"
#include "../Widgets/TimerWidget.hpp"

/**
 * @brief The game screen is a means to display the game itself.
 */
class GameScreen : public ChangeScoreListener, public TimeChangeInterface, public TimeChangeListener, public Screen
{
    public:
    /**
     * @brief Construct a game screen and start a new game.
     * @param difficulty The difficulty of the game.
     */
    GameScreen(unsigned int difficulty);
    virtual ~GameScreen();

    /**
     * @brief Listen for gui actions.
     * @param event The action event.
     */
    virtual void action(const gcn::ActionEvent& event);

	/**
	 * @brief Change the score by the provided amount.
	 * @param change The amount to change the score.
	 */
	virtual void changeScore(int change);

    /**
     * @brief Render the screen.
     * @param renderer The graphics object with which to draw.
     */
    virtual void draw(gcn::SFMLGraphics& renderer);

    /**
     * @brief A key was pressed.
     * @param event The key event.
     */
    virtual void keyPressed(gcn::KeyEvent& event);

    /**
     * @brief A key was released.
     * @param event The key event.
     */
    virtual void keyReleased(gcn::KeyEvent& event);

    /**
     * @brief Perform anything necessary to prepare this screen for displaying what it needs to.
     * @param gui The gui to work with.
     */
    virtual void load(GUI* gui);

    /**
     * @brief Perform logic.
     */
    virtual void logic();

    /**
     * @brief A time change request was sent.
     * @param time The time to change.
     */
    virtual void timeChange(int time)
    {
    	distributeTimeChange(time);
    }

    private:
    // The game's initial difficulty.
    unsigned int mDifficulty;

    // True if the game is paused.
    bool mIsPaused;

    // The current level.
    Level* mLevel;

    // The game options menu.
    GameOptionsWidget mOptionsMenu;

    // The menu bar.
//    GameScreenMenuBar mMenuBar;

    // The level complete widget.
    LevelCompleteWidget mLevelCompleteWidget;

	// This is the score.
	unsigned int mScore;

	// This is the amount to add to the score.
	int mCounter;

	// This is the score timer.
	Timer mScoreTimer;

    // The visual bounds for this level.
    sf::View mCamera;

    // Internal widgets.
    TimerWidget mTimerWidget;
    gcn::Label mScoreLabel;

    // The player.
    Player mPlayer;

    // If true, reset the view on the next draw() call (used when loading a new level)
    bool mResetView;
};

#endif /* GAMESCREEN_HPP_ */
