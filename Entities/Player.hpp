/*
 * Player.h
 *
 *  Created on: Apr 1, 2009
 *      Author: alienjon
 */
#ifndef PLAYER_H_
#define PLAYER_H_

#include <list>

#include "../Entities/Creature.hpp"
#include "../Listeners/InputListener.hpp"
#include "../Listeners/KeyPickedUpListener.hpp"

class Level;

/**
 * @brief The player class.
 */
class Player : public Creature, public InputListener
{
	public:
    /**
     * @brief Construct a new player.
     */
    Player();
    virtual ~Player();

    /**
     * @brief This player is colliding/interacting with an entity.
     * @param entity The entity this player collided into.
     */
    virtual void collide(Entity& entity);

    /**
     * @brief Handle input.
     * @param event The input event.
     * @return True if the event was consumed (used).
     */
    virtual bool handleInput(const sf::Event& event);

    /**
     * @brief Set the input state.
     * @param state True allows the player to receive input.
     */
    inline void setInputState(bool state)
    {
    	mHasInput = state;
    }

	private:
	/**
	 * This is the distance in front of the player that will be used when the player presses the action button.
	 */
	static const int PLAYER_ACTION_DISTANCE;

	// If true, the player can perform input.
	bool mHasInput;
};

// The action key.
extern const sf::Keyboard::Key PLAYER_ACTION_KEY;

#endif /* PLAYER_H_ */
