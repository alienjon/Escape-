/*
 * Portal.hpp
 *
 *  Created on: Oct 27, 2011
 *      Author: alienjon
 */
#ifndef PORTAL_HPP_
#define PORTAL_HPP_

#include <list>

#include "../Entities/Entity.hpp"
#include "../Listeners/KeyPickedUpListener.hpp"
#include "../Interfaces/LevelCompleteInterface.hpp"

class Portal: public Entity, public LevelCompleteInterface
{
	public:
	/**
	 * @brief Default constructor.
	 */
	Portal();
	virtual ~Portal() {}

    /**
     * @brief This portal is colliding/interacting with an entity.
     * @param entity The entity this portal collided into.
     */
    virtual void collide(Entity& entity);

    /**
     * @brief A key was picked up.
     */
    virtual void keyPickedUp();

	private:
    // True if the portal is locked.
    bool mIsLocked;
};

#endif /* PORTAL_HPP_ */
