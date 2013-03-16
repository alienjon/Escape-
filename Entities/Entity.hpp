/*
 * Entity.hpp
 *
 *  Created on: Jun 25, 2009
 *      Author: alienjon
 */
#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <set>
#include <string>

#include <SFML/Graphics.hpp>

#include "../Interfaces/ActionInterface.hpp"
#include "../Engine/AnimatedSprite.hpp"
#include "../Interfaces/ChangeScoreInterface.hpp"
#include "../Listeners/DeathListener.hpp"
#include "../Interfaces/FloatingTextInterface.hpp"
#include "../Game/Math.hpp"

class Item;
class Level;

/**
 * @brief A being is a single, tangible game object.
 *
 * A being is a single game object and provides basic object
 * functioning for something that needs to act on screen
 * (such as displaying itself, performing logic and having
 * various listeners)
 */
class Entity : public ActionInterface, public ChangeScoreInterface, public FloatingTextInterface
{
    public:
    enum EntityType
    {
    	ENTITY_CREATURE,
    	ENTITY_ITEM,
    	ENTITY_KEY,
    	ENTITY_PICKUP,
    	ENTITY_PLAYER,
    	ENTITY_PORTAL,
    	ENTITY_SPEEDCHANGE,
    	ENTITY_SURPRISEPICKUP,
    	ENTITY_TIMECHANGE,
    	ENTITY_NULL
    };

    virtual ~Entity();

    /**
     * @brief Add a death listener.
     * @param listener The listener to add.
     */
    inline void addDeathListener(DeathListener* listener)
    {
        mDeathListeners.push_back(listener);
    }

    /**
     * @brief This entity is colliding/interacting with an entity.
     * @param entity The entity this creature collided into.
     */
    virtual void collide(Entity& entity) = 0;

    /**
     * @brief Draw the being to the screen.
     * @param renderer The graphics object.
     */
    virtual void draw(sf::RenderWindow& renderer);

    /**
     * @brief Get the alpha value for the entity.
     * @return The alpha value for the entity.
     *
     * @note Must be implemented by inheriting classes as it is based off of class-specific sf::Drawables.
     */
    virtual unsigned int getAlpha() const
    {
    	return mSprite.getAlpha();
    }

    /**
     * @brief Get the physical area of this being.
     * @return The dimension.
     *
     * @note Must be implemented by inheriting classes as it is based off of class-specific sf::Drawables.
     */
    virtual sf::FloatRect getDimension() const
    {
    	return mSprite.getGlobalBounds();
    }

    /**
     * @brief Get the being's height.
     * @return The being's height.
     */
    virtual unsigned int getHeight() const
    {
    	return mSprite.getHeight();
    }

    /**
     * @brief Get the current position of this being.
     * @return The current position of this being.
     */
    virtual const sf::Vector2f& getPosition() const
    {
    	return mSprite.getPosition();
    }

    /**
     * @brief Get the type of being this is.
     * @return The type of being.
     */
    inline Entity::EntityType getType() const
    {
        return mType;
    }

    /**
     * @brief Get the being's width.
     * @return The being's width.
     */
    virtual unsigned int getWidth() const
    {
    	return mSprite.getWidth();
    }

    /**
     * @brief Get the x position.
     * @return The x position.
     */
    virtual float getX() const
    {
    	return getPosition().x;
    }

    /**
     * @brief Get the y position.
     * @return The y position.
     */
    virtual float getY() const
    {
    	return getPosition().y;
    }

    /**
     * @brief Checks the collision state of the entity.
     * @return The collision state of the entity.
     */
    inline bool isCollidable() const
    {
        return mIsCollidable;
    }

    /**
     * @brief Checks the interactability of the entity.
     * @return The interactability of the entity.
     */
    inline bool isInteractable() const
    {
    	return mIsInteractable;
    }

    /**
     * @brief Perform internal logic.
     * @param level The level within which the entity is currently residing.
     * @param delta The time since the last frame displayed.
     */
    virtual void logic(Level& level, int delta);

    /**
     * @brief Remove a death listener.
     * @param listener The listener to add.
     */
    inline void removeDeathListener(DeathListener* listener)
    {
        mDeathListeners.remove(listener);
    }

    /**
     * @brief Set the alpha of the entity.
     * @param a The alpha value.
     *
     * @note Must be implemented in the inheriting class as it affects the class-specific sf::Drawable used.
     */
    virtual void setAlpha(unsigned int a)
    {
    	mSprite.setAlpha(a);
    }

    /**
     * @brief Set the collision state of the entity.
     * @param state The state to set.
     */
    inline void setCollidable(bool state)
    {
    	mIsCollidable = state;
    }

    /**
     * @brief Set the interactability of the entity.
     * @param state The interactability state.
     */
    inline void setInteractable(bool state)
    {
    	mIsInteractable = state;
    }

    /**
     * @brief Set the position of this being.
     * @param x The x position.
     * @param y The y position.
     *
     * @note Children of this class must set the position for the specific sf::Drawable used to display to the screen (position information is stored in that object)
     */
    inline void setPosition(float x, float y)
    {
    	mSprite.setPosition(x, y);
    }

    /**
     * @brief Set the X position.
     * @param x The x position.
     */
    virtual void setX(float x)
    {
    	setPosition(x, getY());
    }

    /**
     * @brief Set the Y position.
     * @param y The y position.
     */
    virtual void setY(float y)
    {
    	setPosition(getX(), y);
    }

    protected:
    /**
     * @brief A being is a 'sprite of substance' for gameplay.  Creatures are beings, GUI animations are sprites.
     * @param name The name of the entity.
     * @param maxHealth The maximum health for this entity.
     * @param collisionArea The collision area.
     *
     * @see mCollisionArea
     */
    Entity();

    /**
     * @brief This performs common operations when an entity has died.
     */
    virtual void mDie();

    // The being type.
    Entity::EntityType mType;

    // The visual entity.
    AnimatedSprite mSprite;

    private:
    // The collidability state of this being.
    bool mIsCollidable;

    // An entity's ability to collide with another entity is not related to whether it can still interact with an entity.
    bool mIsInteractable;

    // The listeners.
    std::list<DeathListener*> mDeathListeners;
};

/**
 * @brief Accept 2 beings and return the one with the lower Z index.
 * @param beingA The first being.
 * @param beingB The second being.
 * @return True if the first being is of a lower Z-Index than the other.
 */
bool sortByZIndex(Entity* beingA, Entity* beingB);

#endif /* ENTITY_HPP_ */
