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

#include "../Interfaces/GCNActionInterface.hpp"
#include "../Engine/GUI.hpp"
#include "../Engine/guichan.hpp"
#include "../Engine/Guichan/sfml.hpp"

class Screen;

/**
 * @brief The game object itself.  Manages higher level aspects of the game.
 */
class Engine : public gcn::ActionListener, public GCNActionInterface, public gcn::KeyListener
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
     * @brief Set the framerate.
     * @param rate The framerate.
     */
    static void setFramerate(unsigned int rate);

    /**
     * @brief Default constructor.
     */
    Engine();
    virtual ~Engine();

    /**
     * @brief A key was pressed.
     * @param event The key event.
     */
    virtual void keyPressed(gcn::KeyEvent& event);

    /**
     * @brief Set the screen BPP.
     * @param bpp The new bits per pixel.
     * @note This just changes the setting, you still need to update the screen.
     * @see updateScreen()
     */
    inline void setScreenBPP(unsigned int bpp)
    {
    	mVideoMode.BitsPerPixel = bpp;
    }

    /**
     * @brief Set the screen height.
     * @param height The new screen height.
     * @note This just changes the setting, you still need to update the screen.
     * @see updateScreen()
     */
    inline void setScreenHeight(unsigned int height)
    {
    	mVideoMode.Height = height;
    }

    /**
     * @brief Set the screen width.
     * @param width The new screen width.
     * @note This just changes the setting, you still need to update the screen.
     * @see updateScreen()
     */
    inline void setScreenWidth(unsigned int width)
    {
    	mVideoMode.Width = width;
    }

    /**
     * @brief Run the game.
     */
    void run();

    /**
     * @brief Update the screen with the current video mode settings.
     */
    void updateScreen();

    protected:
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
    sf::VideoMode mVideoMode;
    sf::ContextSettings mSettings;

    // The window states.
    bool mFullscreen,
		 mVerticalSync;

    // Game objects.
    gcn::SFMLGraphics mRenderer;
    gcn::SFMLInput mInput;
    GUI* mGui;
    std::list<Screen*> mScreens;
    std::list<Screen*>::iterator mCurrentScreen;

    private:
    // The debug state.
    static bool mDebug;

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
