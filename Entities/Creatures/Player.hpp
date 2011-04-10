/*
 * Player.h
 *
 *  Created on: Apr 1, 2009
 *      Author: alienjon
 */
#ifndef PLAYER_H_
#define PLAYER_H_

#include <list>

#include "Creature.hpp"
#include "../../Game/Game.hpp"
#include "../../Game/Input.hpp"
#include "../../Engine/Timer.hpp"
#include "../../Math/Vector.hpp"

class EnvironmentData;
class ObjectManager;

/**
 * @brief The player class.
 *
 * Note: This is the only being class that accepts user input (for a good reason!)
 */
class Player : public Creature
{
    // Let the GameData object load member values.
    friend class GameData;

	public:
    /**
     * @brief Construct a new player.
     */
    Player();

    /**
     * @brief Construct the entity from the data string.
     * @param data The data string with which to create the entity.
     */
    Player(const std::string& data);
    virtual ~Player();

    /**
     * @brief Convert the state of the entity to a string to save.
     * @return A string representation of the entity.
     */
    virtual std::string extract() const;

	/**
	 * @brief Handle player input.
	 * @param input The input object.
	 */
	virtual void handleInput(const Input& input);

    /**
     * @brief Perform internal logic.
     * @param eData The level environment in which this entity resides.
     */
    virtual void logic(EnvironmentData& eData);

    /**
     * @brief Interact with the provided entity.
     * @param entity The entity.
     */
    virtual void interact(Entity& entity);

    /**
     * @brief Set the player's state of accepting input.
     * @param state The input acceptance state.
     */
    virtual void setInputState(bool state);

	protected:
	/**
	 * This is the distance in front of the player that will be used when the player presses the action button.
	 */
	static const int PLAYER_ACTION_DISTANCE;

    /**
     * @brief This entity collided with the collidee
     * @param collidee The entity that has collided with this entity.
     */
    virtual void mCollision(Entity& collidee);

	/**
	 * @brief Interact with the object.
	 * @param object The object.
	 */
	virtual void mCreatureInteract(Entity* object);

	/**
	 * @brief The player has died.
	 */
	virtual void mDie();

	private:
	/**
	 * True if the player can accept input.
	 */
	bool mAllowInput;

	/**
	 * If true then the player is only looking at the current looking at spot.
	 */
	bool mIsStaringAtPoint;

	/**
	 * True if the player should interact at the next logic call.
	 */
	bool mIsInteracting;

	/**
	 * The interacting timer.
	 */
	Timer mInteractingTimer;
};

/**
 * The force with which the player pushes things.
 * @note The force used here is the 'other creature is unawares' force.
 */
extern const int PLAYER_PUSH_FORCE;

/**
 * The action key.
 */
extern const SDLKey PLAYER_ACTION_KEY;

#endif /* PLAYER_H_ */