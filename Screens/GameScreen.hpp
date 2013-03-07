/*
 * GameScreen.hpp
 *
 *  Created on: Jun 24, 2009
 *      Author: alienjon
 */
#ifndef GAMESCREEN_HPP_
#define GAMESCREEN_HPP_

#include <string>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <CEGUI/elements/CEGUIFrameWindow.h>

#include "../Listeners/ChangeScoreListener.hpp"
#include "../Widgets/GameOptionsWidget.hpp"
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
     * @brief Handler for opening the audio options widget.
     * @param eArgs The event arguments.
     * @return True if run successfully.
     */
    bool _handlerShowAudioOptions(const CEGUI::EventArgs& eArgs);

    /**
     * @brief Handler for closing the audio options widget.
     * @param eArgs The event arguments.
     * @return True if run successfully.
     */
    bool _handlerCloseAudioOptions(const CEGUI::EventArgs& eArgs);

    /**
     * @brief Handler for closing the options widget.
     * @param eArgs The event arguments.
     * @return True if run successfully.
     */
    bool _handlerCloseOptions(const CEGUI::EventArgs& eArgs);

    /**
     * @brief Handler for closing the video options widget.
     * @param eArgs The event arguments.
     * @return True if run successfully.
     */
    bool _handlerCloseVideoOptions(const CEGUI::EventArgs& eArgs);

    /**
     * @brief Handler for returning to the main menu.
     * @param eArgs The event arguments.
     * @return True if run successfully.
     */
    bool _handlerMainMenu(const CEGUI::EventArgs& eArgs);

    /**
     * @brief Handler for opening the video options widget.
     * @param eArgs The event arguments.
     * @return True if run successfully.
     */
    bool _handlerShowVideoOptions(const CEGUI::EventArgs& eArgs);

    /**
     * @brief Update the text level of the music.
     * @param eArgs The event arguments.
     * @return True if run successfully.
     */
    bool _handlerUpdateMusicTextLevels(const CEGUI::EventArgs& eArgs);

    /**
     * @brief Update the text level of the sound.
     * @param eArgs The event arguments.
     * @return True if run successfully.
     */
    bool _handlerUpdateSoundTextLevels(const CEGUI::EventArgs& eArgs);

    /**
     * @brief Listen for gui actions.
     * @param event The action event.
     */
    virtual void eventOccurred(const std::string& event);

	/**
	 * @brief Change the score by the provided amount.
	 * @param change The amount to change the score.
	 */
	virtual void changeScore(int change);

    /**
     * @brief Render the screen.
     * @param renderer The graphics object with which to draw.
     */
    virtual void draw(sf::RenderWindow& renderer);

    /**
     * @brief Handle input.
     * @param event The input event.
     * @return True if the event was consumed (used).
     */
    virtual bool handleInput(const sf::Event& event);

    /**
     * @brief Perform anything necessary to prepare this screen for displaying what it needs to.
     * @param view The view in which the screen is displayed.
     */
    virtual void load(const sf::View& view);

    /**
     * @brief Perform logic.
     * @param delta The time since the last frame displayed.
     */
    virtual void logic(int delta);

    /**
     * @brief A time change request was sent.
     * @param time The time to change.
     */
    virtual void timeChange(int time)
    {
    	distributeTimeChange(time);
    }

    private:
    /**
     * @brief Reposition/resize the internal widgets.
     */
    void mUpdateWidgetPositions();

    // The game's initial difficulty.
    unsigned int mDifficulty;

    // True if the game is paused.
    bool mIsPaused;

    // The background music.
    sf::Music mBackMusic;

    // The current level.
    Level* mLevel;

    //@todo implement options and
//    // The level complete widget.
//    LevelCompleteWidget mLevelCompleteWidget;

	// This is the score.
	unsigned int mScore;

	// This is the amount to add to the score.
	int mCounter;

    // The visual bounds for this level.
    sf::View mCamera;

    // Internal widgets.
    CEGUI::FrameWindow *mOptionsWidget, *mVideoOptionsWidget, *mAudioOptionsWidget;
    std::list<CEGUI::ListboxTextItem*> mResolutionOptions;
    //@todo Need to re-implement widgets
//    TimerWidget mTimerWidget;
//    gcn::Label mScoreLabel;

    //@fixme re-implement timer GUI and score GUI then remove.
    sf::Text mScoreDisplay;
    Timer mScoreTimer;
    sf::Font mFont;//@todo remove when GUI is implemented?
    TimerWidget mTimerWidget;

    // The player.
    Player mPlayer;

    // If true, reset the view on the next draw() call (used when loading a new level)
    bool mResetView;

    // The collection of background musics.
    std::vector<std::string> mBackMusicVector;
};

#endif /* GAMESCREEN_HPP_ */
