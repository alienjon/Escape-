/*
 * Player.h
 *
 *  Created on: Apr 1, 2009
 *      Author: alienjon
 */
#ifndef PLAYER_H_
#define PLAYER_H_

#include <list>

#include "../Listeners/AddLockListener.hpp"
#include "../Entities/Creature.hpp"
#include "../Game/Input.hpp"
#include "../Listeners/RemoveLockListener.hpp"
#include "../Engine/Timer.hpp"

class Level;

/**
 * @brief The player class.
 */
class Player : public AddLockListener, public Creature, public RemoveLockListener
{
	public:
    /**
     * @brief Construct a new player.
     */
    Player();
    virtual ~Player();

    /**
     * @brief Add a color lock to the player.
     * @param color The color lock to add.
     */
    inline void addLock(gcn::Color color)
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
    virtual void draw(Renderer& renderer);

    /**
     * @brief Get the color locks for the player.
     * @return The locks.
     */
    inline const std::list<gcn::Color>& getColorLock() const
	{
    	return mLocks;
	}

	/**
	 * @brief Handle player input.
	 * @param input The input object.
	 */
	virtual void handleInput(const Input& input);

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
    inline void removeLock(gcn::Color color)
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
	// True if the player can accept input.
	bool mAllowInput;

	// True if the player should interact at the next logic call.
	bool mIsInteracting;

	// The interacting timer.
	Timer mInteractingTimer;

	// The color locks.
	std::list<gcn::Color> mLocks;
};

/**
 * The action key.
 */
extern const SDLKey PLAYER_ACTION_KEY;

#endif /* PLAYER_H_ */
