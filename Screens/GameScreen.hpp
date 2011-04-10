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

#include "../Listeners/CreatureMovedToPointListener.hpp"
#include "../Game/Event.hpp"
#include "../Game/GameData.hpp"
#include "../Widgets/GameOptionsWidget.hpp"
#include "../Widgets/GameOverWidget.hpp"
#include "../Game/GUI.hpp"
#include "../guichan.hpp"
#include "../Widgets/GUIMessageWidget.hpp"
#include "../Widgets/HealthBarContainer.hpp"
#include "../Game/Input.hpp"
#include "../Listeners/InterfaceListener.hpp"
#include "../Widgets/LetterGUIWidget.hpp"
#include "../LevelInfo/Level.hpp"
#include "../Widgets/MessageDisplayWidget.hpp"
#include "../Managers/PlotManager.hpp"
#include "../Engine/Renderer.hpp"
#include "Screen.hpp"
#include "../Engine/Sprite.hpp"
#include "../Engine/Timer.hpp"
#include "../Math/Vector.hpp"
#include "../Engine/Viewport.hpp"

class Creature;
class Entity;

/**
 * @brief The game screen is a means to display the game itself.
 */
class GameScreen : public gcn::ActionListener, public InterfaceListener, public Screen
{
    public:
    /**
     * @brief Construct a game screen.
     */
    GameScreen();
    virtual ~GameScreen();

    /**
     * @brief Listen for gui actions.
     * @param event The action event.
     */
    virtual void action(const gcn::ActionEvent& event);

    /**
     * @brief Add creature info to the GUI.
     * @param creature The creature whose info is to be displayed.
     */
    virtual void addCreatureDisplay(Creature* creature);

    /**
     * @brief Add a message to the messages section of the options menu.
     * @param title The message's title.
     * @param message The message itself.
     */
    virtual void addMessage(const std::string& title, const std::string& message);

    /**
     * @brief Add a task for the user to complete.
     * @param title The task's title.
     * @param message A detailed message of how to complete the task.
     * @return The id of the task.
     */
    virtual unsigned int addTask(const std::string& title, const std::string& message);

    /**
     * @brief Complete the task with the indicated ID.
     * @param id The id of the newly completed task.
     */
    virtual void completeTask(unsigned int);

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
     * @brief Get the viewport's offset.
     * @return The offset.
     */
    Vector getViewportOffset() const;

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

    /**
     * @brief Remove a creature's health display from the GUI.
     * @param creature The creature whose display is to be removed.
     */
    virtual void removeCreatureDisplay(Creature* creature);

	/**
	 * @brief Save the game.
	 */
	virtual void saveGame();

	/**
	 * @brief Set the viewport's bounds.
	 * @param bounds The bounds to set.
	 */
	virtual void setViewportBounds(const Rectangle& bounds);

	/**
	 * @brief Set the viewport's focus.
	 * @param entity The entity onto which to set focus.
	 */
	virtual void setViewportFocus(const Entity* entity);

	/**
	 * @brief Set the viewport's focus.
	 * @param x The x position.
	 * @param y The y position.
	 */
	virtual void setViewportFocus(int x, int y);

    /**
     * @brief Signal the letter indicator.
     */
    virtual void signalLetterIndicator();

    /**
     * @brief The unload method.
     */
    virtual void unload();

    protected:
    /**
     * @brief Add a creature.
     * @param data The data needed to find a created creature or to create one.
     */
    void mAddCreature(const std::string& data);

    /**
     * @brief Add a flashlight.
     * @param data The data needed to add a flashlight.
     */
    void mAddFlashlight(const std::string& data);

    /**
     * @brief Add an object to the screen.
     * @param data The data needed to add an object to the screen.
     */
    void mAddObject(const std::string& data);

    /**
     * @brief Configure a creature.
     * @param data The data needed to configure a creature.
     */
    void mCreatureConfig(const std::string& data);

    /**
     * @brief Tell a creature to walk to a certain position.
     * @param data The data needed to tell a creature to walk to a position.
     * @param listener A possible listener for when the creature has finished moving to a position.
     */
    void mCreatureWalkTo(const std::string& data, CreatureMovedToPointListener* listener);

    /**
     * @brief Display a simple message.
     * @param message The message to display.
     * @param duration The time the message should be shown on the screen.
     * @note Simple messages should probably only be shown by the gamescreen, hence this is protected.
     */
    void mDisplaySimpleMessage(const std::string& message, unsigned int duration);

    /**
     * @brief Remove an entity from the level.
     * @param data The data needed to remove an entity from the level.
     */
    void mRemoveEntity(const std::string& data);

    private:
    /**
     * True if the game is paused.
     */
    bool mIsPaused;

    /**
     * The object to store this game's information.
     */
    GameData mGameData;

    /**
     * This is the plot device manager.
     */
    PlotManager mPlotManager;

    /**
     * The current level.
     */
    Level* mLevel;

    /**
     * Data for the next level (if the next level exists, then the current level needs to be unloaded after its logic is called).
     */
    std::string mNextLevel;

    /**
     * The game over widget.
     */
    GameOverWidget mGameOverWidget;

    /**
     * The game options menu.
     */
    GameOptionsWidget mOptionsMenu;

    /**
     * The creature display bar container.
     */
    HealthBarContainer mHealthBarContainer;

    /**
     * A widget to inform the user a letter was received or removed
     */
    LetterGUIWidget mLetterOSD;

    /**
     * A widget to show the user any collected messages (tutorial info, speech, etc...)
     */
    MessageDisplayWidget mMessageOSD;

    /**
     * The GUI message OSD (for simple messages)
     */
    GUIMessageWidget mSimpleMessageOSD;

    /**
     * The game screen's input timer.
     */
    Timer mInputTimer;
};

#endif /* GAMESCREEN_HPP_ */
