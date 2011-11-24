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
#include "../Interfaces/AddLockInterface.hpp"
#include "../Interfaces/ChangeScoreInterface.hpp"
#include "../Listeners/DeathListener.hpp"
#include "../Interfaces/FloatingTextInterface.hpp"
#include "../Game/Math.hpp"
#include "../Interfaces/RemoveLockInterface.hpp"

class Level;

/**
 * @brief A being is a single, tangible game object.
 *
 * A being is a single game object and provides basic object
 * functioning for something that needs to act on screen
 * (such as displaying itself, performing logic and having
 * various listeners)
 */
class Entity : public ActionInterface, public AddLockInterface, public ChangeScoreInterface, public FloatingTextInterface, public RemoveLockInterface
{
    public:
    enum EntityType
    {
    	ENTITY_CREATURE,
    	ENTITY_PLAYER,
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
     * @brief This creature is colliding/interacting with an entity.
     * @param entity The entity this creature collided into.
     */
    virtual void collide(Entity& entity) = 0;

    /**
     * @brief Draw the being to the screen.
     * @param renderer The graphics object.
     */
    virtual void draw(sf::RenderWindow& renderer);

    /**
     * @brief Get the physical area of this being.
     * @return The dimension.
     */
    inline const sf::Shape& getDimension() const
    {
    	return mSprite;
    }

    /**
     * @brief Get the being's height.
     * @return The being's height.
     */
    inline unsigned int getHeight() const
    {
    	return boundingBox(mSprite).Height;
    }

    /**
     * @brief Get the current position of this being.
     * @return The current position of this being.
     */
    inline const sf::Vector2f& getPosition() const
    {
        return mSprite.GetPosition();
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
    inline unsigned int getWidth() const
    {
    	return boundingBox(mSprite).Width;
    }

    /**
     * @brief Get the x position.
     * @return The x position.
     */
    inline float getX() const
    {
    	return mSprite.GetPosition().x;
    }

    /**
     * @brief Get the y position.
     * @return The y position.
     */
    inline float getY() const
    {
    	return mSprite.GetPosition().y;
    }

//    /**
//     * @brief Interact with an entity.
//     * @param entity The entity.
//     */
//    virtual void interact(Entity& entity)
//    {}

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
     */
    virtual void logic(Level& level);

    /**
     * @brief Remove a death listener.
     * @param listener The listener to add.
     */
    inline void removeDeathListener(DeathListener* listener)
    {
        mDeathListeners.remove(listener);
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
     */
    inline void setPosition(float x, float y)
    {
    	setX(x);
    	setY(y);
    }

    /**
     * @brief Set the X position.
     * @param x The x position.
     */
    inline void setX(float x)
    {
    	mSprite.SetX(x);
    }

    /**
     * @brief Set the Y position.
     * @param y The y position.
     */
    inline void setY(float y)
    {
    	mSprite.SetY(y);
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

    // The displaying sprite for this being.
    //@todo How should entities be displayed?
    sf::Shape mSprite;

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
bool sortByZIndex(const Entity* beingA, const Entity* beingB);

#endif /* ENTITY_HPP_ */
