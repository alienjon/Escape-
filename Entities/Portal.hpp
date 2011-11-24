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
#include "../Engine/Timer.hpp"

class Level;

class Portal: public Entity, public LevelCompleteInterface, public RemoveLockListener
{
	public:
	/**
	 * @brief Default constructor.
	 * @param width The width of the portal.
	 * @param height The height of the portal.
	 */
	Portal(unsigned int width, unsigned int height);

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
     * @brief Draw the being to the screen.
     * @param renderer The graphics object.
     */
    virtual void draw(sf::RenderWindow& renderer);

    /**
     * @brief Get the color locks for the portal.
     * @return The locks.
     */
//    inline const std::list<sf::Color>& getColorLock() const
//	{
//    	return mLocks;
//	}

    /**
     * @brief Get the height of the portal.
     * @return The height of the portal.
     */
    inline unsigned int getPortalHeight() const
    {
    	return mHeight;
    }

    /**
     * @brief Get the width of the portal.
     * @return The width of the portal.
     */
    inline unsigned int getPortalWidth() const
    {
    	return mWidth;
    }

    /**
     * @brief Portal logic.
     * @param level The level in which the portal exists.
     */
    virtual void logic(Level& level);

    /**
     * @brief Remove a color lock from the portal.
     * @param color The lock to remove.
     */
    void removeLock(sf::Color color);

    /**
     * @brief Set the height of the portal.
     * @param height The height of the portal.
     */
    inline void setPortalHeight(unsigned int height)
    {
    	mHeight = height;
    }

    /**
     * @brief Set the width of the portal.
     * @param width The width of the portal.
     */
    inline void setPortalWidth(unsigned int width)
    {
    	mWidth = width;
    }

	private:
    // These are the locks blocking the portal from being open.
    std::list<std::pair<sf::Color, float> > mLocks;

    // This is the size of the portal.
    unsigned int mWidth, mHeight;

    // The animation timer.
    Timer mTimer;

    // This is the start radius for the locks.
    float mStartRadius;
};

#endif /* PORTAL_HPP_ */
