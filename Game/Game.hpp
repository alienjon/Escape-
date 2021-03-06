/*
 * Game.hpp
 *
 *  Created on: Nov 7, 2011
 *      Author: alienjon
 */
#ifndef GAME_HPP_
#define GAME_HPP_

#include <string>

#include <SFML/Graphics.hpp>

#include "../Engine/Engine.hpp"
#include "../Interfaces/EventInterface.hpp"

/*
 * @brief Implementation of engine.
 */
class Game : public Engine
{
	public:
	typedef enum
	{
		EASY,
		NORMAL,
		HARD
	} Difficulty;

	/**
	 * @brief Default constructor.
	 */
	Game();
	virtual ~Game();

    /**
     * @brief An event occurred.
     * @param event The event details.
     */
    virtual void eventOccurred(const std::string& event);

	protected:
    /**
     * @brief Draw the loading screen (it's only a single frame).
     */
    virtual void mDrawLoadingScreen();

    /**
     * @brief Cleanup the game.
     */
    virtual void mGameCleanup();

    /**
     * @brief Setup the game.
     */
    virtual void mGameSetup();

    /**
     * @brief Load the game resources.
     */
    virtual void mLoadResources();

	private:
    /**
     * @brief Draw a loading resource frame.
     * @param percent The percent drawn.
     * @param title The title of the animation being loaded.
     */
    void mDrawResourceFrame(unsigned int percent, const std::string& title);

    // The loading screen image.
    sf::Sprite mLoadingScreen;
};

#endif /* GAME_HPP_ */
