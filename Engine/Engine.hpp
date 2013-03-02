/*
 * Engine.hpp
 *
 *  Created on: Apr 30, 2009
 *      Author: alienjon
 */
#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <list>
#include <SFML/Graphics.hpp>

#include "../Interfaces/EventInterface.hpp"
#include "../Listeners/EventListener.hpp"
#include "../Engine/GUI.hpp"
#include "../Engine/RendererContext.hpp"
#include "../Engine/RendererContextInterface.hpp"

class Screen;

/**
 * @brief The game object itself.  Manages higher level aspects of the game.
 */
class Engine : public EventInterface, public EventListener, public RendererContextInterface
{
    public:
    /**
     * @brief Determine the debugging state.
     * @return The debugging state.
     */
    static bool isDebug();

    /**
     * @brief Set the debugging state.
     * @param state If true then extra information will be displayed to the console and stored in error.log.
     */
    static void setDebug(bool state);

    /**
     * @brief Default constructor.
     */
    Engine();
    virtual ~Engine();

    /**
     * @brief Get the video context.
     * @return The current video context.
     */
    virtual const RendererContext& getContext() const;

    /**
     * @brief Handle input.
     * @param event The input event.
     * @return true if the engine consumed (used) the event.
     */
    virtual bool handleInput(const sf::Event& event);

    /**
     * @brief Run the game.
     */
    void run();

    /**
     * @brief Update the context.
     * @param context Details needed to implement a new screen.
     */
    virtual void updateContext(const RendererContext& context);

    protected:
    /**
     * @brief Draw the loading screen (it's only a single frame).
     */
    virtual void mDrawLoadingScreen() {}

    /**
     * @brief Cleanup the game.
     */
    virtual void mGameCleanup() = 0;

    /**
     * @brief Setup the game.
     */
    virtual void mGameSetup() = 0;

    /**
     * @brief Load the game resources.
     * @note This must be called by inheritors of Engine (probably in the constructor)
     */
    virtual void mLoadResources() = 0;

    // The settings for the window.
    RendererContext mContext;

    // Game objects.
    sf::RenderWindow mRenderer;
    GUI mGUI;
    std::list<Screen*> mScreens;
    std::list<Screen*>::iterator mCurrentScreen;

    private:
    // The debug state.
    static bool mDebug;

    // The FPS information.
    sf::Text mFPSDisplay;
    sf::Font mFont;

    /**
     * @brief Clean up the remaining game screens.
     */
    void mCleanUpScreens();

    /**
     * @brief Unload the current screen and load the next screen.
     * @note Will throw an exception if there are no more screens to load.
     */
    void mLoadNextScreen();
};

#endif /* GAME_HPP_ */
