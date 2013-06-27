/*
 * Key.hpp
 *
 *  Created on: Oct 27, 2011
 *      Author: alienjon
 */
#ifndef KEY_HPP_
#define KEY_HPP_

#include <list>

#include "../Entities/Entity.hpp"
#include "../Listeners/KeyPickedUpListener.hpp"
#include "../Engine/Timer.hpp"

class Level;

/**
 * @brief A key entity is an item to be picked up by the player to unlock something/end the level.
 */
class KeyEntity : public Entity
{
	public:
	/**
	 * @brief Default constructor.
	 */
	KeyEntity();

    /**
     * @brief Add a KeyPickedUpListener.
     * @param listener The listener.
     */
    void addKeyPickedUpListener(KeyPickedUpListener* listener);

    /**
     * @brief This KeyEntity is colliding/interacting with an entity.
     * @param entity The entity this KeyEntity collided into.
     */
    virtual void collide(Entity& entity);

	/**
	 * @brief Perform logic.
	 * @param level The level in which this entity resides.
	 * @param delta The time since the last frame displayed.
	 */
	virtual void logic(Level& level, int delta);

	/**
	 * @brief Remove a KeyPickedUpListener.
	 * @param listener The listener to remove.
	 */
	void removeKeyPickedUpListener(KeyPickedUpListener* listener);

	private:
	// If not growing, then it is shrinking.
	bool mIsGrowing;

	// The drawing area of the entity.
	sf::Vector2f mSize;

	// The animation timer.
	Timer mTimer;

	// The KeyPickedUpListener's.
	std::list<KeyPickedUpListener*> mKeyPickedUpListeners;
};

#endif /* KEY_HPP_ */
