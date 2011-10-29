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

#include "../Interfaces/ActionInterface.hpp"
#include "../Listeners/AnimationCycleListener.hpp"
#include "../Interfaces/ChangeScoreInterface.hpp"
#include "../Listeners/DeathListener.hpp"
#include "../Game/Direction.hpp"
#include "../Interfaces/EventInterface.hpp"
#include "../Game/Input.hpp"
#include "../Math/Vector.hpp"
#include "../Math/Quadrilateral.hpp"
#include "../Math/Rectangle.hpp"
#include "../Interfaces/RemoveLockInterface.hpp"
#include "../Engine/Renderer.hpp"
#include "../Engine/Sprite.hpp"
#include "../Engine/Timer.hpp"

class Level;

/**
 * @brief A being is a single, tangible game object.
 *
 * A being is a single game object and provides basic object
 * functioning for something that needs to act on screen
 * (such as displaying itself, performing logic and having
 * various listeners)
 */
class Entity : public ActionInterface, public ChangeScoreInterface, public EventInterface, public RemoveLockInterface
{
	friend class DisplayAnimationAction;

    public:
    enum EntityType
    {
    	ENTITY_CREATURE,
    	ENTITY_PLAYER,
    	ENTITY_NULL
    };

    virtual ~Entity();

    /**
     * @brief Add an animation cycle listener.
     * @param listener The listener to add.
     */
    inline void addAnimationCycleListener(AnimationCycleListener* listener)
    {
        mSprite.addAnimationCycleListener(listener);
    }

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
    virtual void draw(Renderer& renderer);

    /**
     * @brief Get the physical area of this being.
     * @return The dimension.
     */
    inline const Rectangle& getDimension() const
    {
    	return mDimension;
    }

    /**
     * @brief Get the being's height.
     * @return The being's height.
     */
    inline unsigned int getHeight() const
    {
    	return mDimension.height;
    }

    /**
     * @brief Get the current position of this being.
     * @return The current position of this being.
     */
    inline const Vector& getPosition() const
    {
        return mDimension.vector;
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
    	return mDimension.width;
    }

    /**
     * @brief Get the x position.
     * @return The x position.
     */
    inline double getX() const
    {
    	return mDimension.vector.x;
    }

    /**
     * @brief Get the y position.
     * @return The y position.
     */
    inline double getY() const
    {
    	return mDimension.vector.y;
    }

    /**
     * @brief Handle input.
     * @param input The current input state.
     */
    virtual void handleInput(const Input& input)
    {}

    /**
     * @brief Interact with an entity.
     * @param entity The entity.
     */
    virtual void interact(Entity& entity)
    {}

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
     * @brief Remove an animation cycle listener.
     * @param listener The listener to remove.
     */
    inline void removeAnimationCycleListener(AnimationCycleListener* listener)
    {
        mSprite.removeAnimationCycleListener(listener);
    }

    /**
     * @brief Remove a death listener.
     * @param listener The listener to add.
     */
    inline void removeDeathListener(DeathListener* listener)
    {
        mDeathListeners.remove(listener);
    }

    /**
     * @brief Set the animating state of the entity.
     * @param state The state to set.
     */
    inline void setAnimating(bool state)
    {
        mSprite.setAnimating(state);
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
    void setPosition(double x, double y);

    /**
     * @brief Set the X position.
     * @param x The x position.
     */
    inline void setX(double x)
    {
    	mDimension.vector.x = x;
    }

    /**
     * @brief Set the Y position.
     * @param y The y position.
     */
    inline void setY(double y)
    {
    	mDimension.vector.y = y;
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
     * @brief This performs common operations when an entity has died (health has reached 0 or otherwise killed)
     */
    virtual void mDie();

    /**
     * @brief Set this being's displaying animation.
     * @param sprite The animation to set.
     */
    virtual void mSetAnimation(const Sprite& sprite);

    // The being type.
    Entity::EntityType mType;

    // The displaying sprite for this being.
    Sprite mSprite;

    /**
     * @brief Set the size of the entity.
     * @param width The width.
     * @param height The height.
     * @todo remove once entity sprites are implemented.
     */
    void mSetSize(unsigned int width, unsigned int height)
    {
    	mDimension.width = width;
    	mDimension.height= height;
    }

    private:
    // The collidability state of this being.
    bool mIsCollidable;

    // An entity's ability to collide with another entity is not related to whether it can still interact with an entity.
    bool mIsInteractable;

    // The listeners.
    std::list<DeathListener*> mDeathListeners;

    // The dimension of the entity in the game world.
    Rectangle mDimension;
};

/**
 * @brief Accept 2 beings and return the one with the lower Z index.
 * @param beingA The first being.
 * @param beingB The second being.
 * @return True if the first being is of a lower Z-Index than the other.
 */
bool sortByZIndex(const Entity* beingA, const Entity* beingB);

#endif /* ENTITY_HPP_ */
