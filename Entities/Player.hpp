/*
 * Player.h
 *
 *  Created on: Apr 1, 2009
 *      Author: alienjon
 */
#ifndef PLAYER_H_
#define PLAYER_H_

#include <list>

#include <SFML/Graphics.hpp>

#include "../Listeners/AddLockListener.hpp"
#include "../Entities/Creature.hpp"
#include "../Listeners/InputListener.hpp"
#include "../Listeners/PickupListener.hpp"
#include "../Listeners/RemoveLockListener.hpp"
#include "../Engine/Timer.hpp"

class Level;

/**
 * @brief The player class.
 */
class Player : public AddLockListener, public Creature, public InputListener, public RemoveLockListener
{
	public:
    /**
     * @brief Construct a new player.
     */
    Player();

    /**
     * @brief Add a color lock to the player.
     * @param color The color lock to add.
     */
    inline void addLock(sf::Color color)
    {
    	mLocks.push_back(color);
    }

    /**
     * @brief This player is colliding/interacting with an entity.
     * @param entity The entity this player collided into.
     */
    virtual void collide(Entity& entity);

    /**
     * @brief Draw the being to the screen.
     * @param renderer The graphics object.
     */
    virtual void draw(sf::RenderWindow& renderer);

    /**
     * @brief Get the color locks for the player.
     * @return The locks.
     */
    inline const std::list<sf::Color>& getColorLock() const
	{
    	return mLocks;
	}

    /**
     * @brief Handle input.
     * @param event The input event.
     * @return True if the event was consumed (used).
     */
    virtual bool handleInput(const sf::Event& event);

	/**
	 * @brief Perform player logic.
	 * @param level The level in which this player exists.
	 * @param delta The time since the last frame displayed.
	 */
	virtual void logic(Level& level, int delta);

	/**
	 * @brief Remove all locks from the player.
	 */
	inline void removeAllLocks()
	{
		mLocks.clear();
	}

    /**
     * @brief Remove a color lock from the player.
     * @param color The lock to remove.
     */
    inline void removeLock(sf::Color color)
    {
    	mLocks.remove(color);
    }

    /**
     * @brief Set the input state.
     * @param state True allows the player to receive input.
     */
    inline void setInputState(bool state)
    {
    	mHasInput = state;
    }

	protected:
	/**
	 * This is the distance in front of the player that will be used when the player presses the action button.
	 */
	static const int PLAYER_ACTION_DISTANCE;

	private:
	enum ColorCycle
	{
		COLORCYCLE_PAUSE,
		COLORCYCLE_MOVE,
		COLORCYCLE_SWITCHCOLORS
	};

	/**
	 * @brief Reset the cycle colors to their original positions.
	 */
	void mResetCyclePositions();

	// If true, the player can perform input.
	bool mHasInput;

	// The information for cycling collected keys.
	Timer mColorCycleTimer;
	ColorCycle mCycle;
	sf::FloatRect mCol1, mCol2, mCol3, mCol4;
	std::list<sf::Color>::iterator mColor1, mColor2, mColor3, mColor4;

	// The color locks.
	std::list<sf::Color> mLocks;
};

// The action key.
extern const sf::Keyboard::Key PLAYER_ACTION_KEY;

#endif /* PLAYER_H_ */
