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
#include "../guichan.hpp"
#include "../Interfaces/LevelCompleteInterface.hpp"
#include "../Listeners/RemoveLockListener.hpp"
#include "../Engine/Renderer.hpp"

class Portal: public Entity, public LevelCompleteInterface, public RemoveLockListener
{
	public:
	Portal();

    /**
     * @brief Add a color lock to the portal.
     * @param color The color lock to add.
     */
    inline void addLock(gcn::Color color)
    {
    	mLocks.push_back(color);
    }

    /**
     * @brief This portal is colliding/interacting with an entity.
     * @param entity The entity this portal collided into.
     */
    virtual void collide(Entity& entity);

    /**
     * @brief Draw the being to the screen.
     * @param renderer The graphics object.
     */
    virtual void draw(Renderer& renderer);

    /**
     * @brief Get the color locks for the portal.
     * @return The locks.
     */
    inline const std::list<gcn::Color>& getColorLock() const
	{
    	return mLocks;
	}

    /**
     * @brief Remove a color lock from the portal.
     * @param color The lock to remove.
     */
    inline void removeLock(gcn::Color color)
    {
    	mLocks.remove(color);
    }

	private:
    // This is the list of locks blocking the portal from being open.
    std::list<gcn::Color> mLocks;
};

#endif /* PORTAL_HPP_ */
