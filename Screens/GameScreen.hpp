/*
 * GameScreen.hpp
 *
 *  Created on: Jun 24, 2009
 *      Author: alienjon
 */
#ifndef GAMESCREEN_HPP_
#define GAMESCREEN_HPP_

#include <list>
#include <string>

#include "SDL/SDL.h"

#include "../Game/Event.hpp"
#include "../Widgets/GameOptionsWidget.hpp"
#include "../Widgets/GameOverWidget.hpp"
#include "../Game/GUI.hpp"
#include "../guichan.hpp"
#include "../Game/Input.hpp"
#include "../LevelInfo/Level.hpp"
#include "../Widgets/MessageDisplayWidget.hpp"
#include "../Entities/Creatures/Player.hpp"
#include "../Engine/Renderer.hpp"
#include "Screen.hpp"
#include "../Engine/Sprite.hpp"
#include "../Engine/Timer.hpp"
#include "../Widgets/TimerWidget.hpp"
#include "../Math/Vector.hpp"

class Entity;

/**
 * @brief The game screen is a means to display the game itself.
 */
class GameScreen : public gcn::ActionListener, public Screen
{
    public:
    /**
     * @brief Construct a game screen and start a new game.
     * @param difficulty The difficulty of the game.
     */
    GameScreen(Event difficulty);
    virtual ~GameScreen();

    /**
     * @brief Listen for gui actions.
     * @param event The action event.
     */
    virtual void action(const gcn::ActionEvent& event);

    /**
     * @brief Messages can be things like tutorials or even conversations.
     * @param caption The caption.
     * @param message The message to display.
     * @param sprite The sprite keyword to use to display with the message.
     * @param keyword A keyword to pass when the conversation is closed.
     * @note The image can be an empty string and a default image will display.
     */
    virtual void displayMessage(const std::string& caption, const std::string& message, const std::string& sprite, const std::string& keyword);

    /**
     * @brief Render the screen.
     * @param renderer The graphics object with which to draw.
     */
    virtual void draw(Renderer& renderer);

    /**
     * @brief An event occurred.
     * @param event The event that occurred.
     * @param content Additional content.
     * @param creatureMovedToPointListener A potential creature moved to point listener.
     */
    virtual void eventOccurred(Event event, const std::string& content = "", CreatureMovedToPointListener* creaturedMovedToPointListener = 0);

    /**
     * @brief Handle input.
     * @param input The input.
     */
    virtual void handleInput(const Input& input);

    /**
     * @brief Perform anything necessary to prepare this screen for displaying what it needs to.
     * @param gui The gui to work with.
     */
    virtual void load(GUI* gui);

    /**
     * @brief Perform logic.
     */
    virtual void logic();

    private:
    /**
     * The player.
     */
    Player mPlayer;

    /**
     * The game's initial difficulty.
     */
    unsigned int mDifficulty;

    /**
     * True if the game is paused.
     */
    bool mIsPaused;

    /**
     * The current level.
     */
    Level* mLevel;

    /**
     * The game over widget.
     */
    GameOverWidget mGameOverWidget;

    /**
     * The game options menu.
     */
    GameOptionsWidget mOptionsMenu;

    /**
     * A widget to show the user any collected messages (tutorial info, speech, etc...)
     */
    MessageDisplayWidget mMessageOSD;

    /**
     * The game screen's input timer.
     */
    Timer mInputTimer;

    /**
     * The timer widget.
     */
    TimerWidget mTimerWidget;
};

#endif /* GAMESCREEN_HPP_ */
