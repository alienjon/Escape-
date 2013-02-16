/*
 * Portal.hpp
 *
 *  Created on: Oct 27, 2011
 *      Author: alienjon
 */
#ifndef PORTAL_HPP_
#define PORTAL_HPP_

#include <list>

#include <SFML/Graphics.hpp>

#include "../Entities/Entity.hpp"
#include "../Interfaces/LevelCompleteInterface.hpp"
#include "../Listeners/RemoveLockListener.hpp"

class Portal: public Entity, public LevelCompleteInterface, public RemoveLockListener
{
	public:
	/**
	 * @brief Default constructor.
	 */
	Portal();
	virtual ~Portal() {}

    /**
     * @brief Add a color lock to the portal.
     * @param color The color lock to add.
     */
    void addLock(sf::Color color);

    /**
     * @brief This portal is colliding/interacting with an entity.
     * @param entity The entity this portal collided into.
     */
    virtual void collide(Entity& entity);

    /**
     * @brief Remove a color lock from the portal.
     * @param color The lock to remove.
     */
    void removeLock(sf::Color color);

	private:
    // These are the locks blocking the portal from being open.
    std::list<sf::Color> mLocks;
};

#endif /* PORTAL_HPP_ */
