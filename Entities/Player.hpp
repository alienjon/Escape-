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

#include "../Engine/guichan.hpp"

#include "../Listeners/AddLockListener.hpp"
#include "../Entities/Creature.hpp"
#include "../Listeners/RemoveLockListener.hpp"
#include "../Engine/Timer.hpp"

class Level;

/**
 * @brief The player class.
 */
class Player : public AddLockListener, public Creature, public gcn::KeyListener, public RemoveLockListener
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
	 * @brief Perform player logic.
	 * @param level The level in which this player exists.
	 */
	virtual void logic(Level& level);

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
     * @brief Set the player's state of accepting input.
     * @param state The input acceptance state.
     */
    inline void setInputState(bool state)
    {
    	mAllowInput = state;
    }

	protected:
	/**
	 * This is the distance in front of the player that will be used when the player presses the action button.
	 */
	static const int PLAYER_ACTION_DISTANCE;

	/**
	 * @brief The player has died.
	 */
	virtual void mDie();

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

	// True if the player can accept input.
	bool mAllowInput;

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
