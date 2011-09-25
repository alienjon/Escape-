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
#include "../Listeners/DeathListener.hpp"
#include "../Game/Direction.hpp"
#include "../Entities/EntityType.hpp"
#include "../Interfaces/EventInterface.hpp"
#include "../Listeners/HealthChangedListener.hpp"
#include "../Game/Input.hpp"
#include "../Listeners/InteractionListener.hpp"
#include "../Listeners/MovementListener.hpp"
#include "../Math/Vector.hpp"
#include "../Math/Quadrilateral.hpp"
#include "../Math/Rectangle.hpp"
#include "../Engine/Renderer.hpp"
#include "../Engine/Sprite.hpp"
#include "../Engine/Timer.hpp"

class Creature;
class EnvironmentData;

/**
 * @brief A being is a single, tangible game object.
 *
 * A being is a single game object and provides basic object
 * functioning for something that needs to act on screen
 * (such as displaying itself, performing logic and having
 * various listeners)
 */
class Entity : public ActionInterface, public EventInterface
{
    friend class DisplayAnimationAction;
    friend class ExplosionEntity;

    public:
    virtual ~Entity();

    /**
     * @brief Add an animation cycle listener.
     * @param listener The listener to add.
     */
    void addAnimationCycleListener(AnimationCycleListener* listener);

    /**
     * @brief Add a death listener.
     * @param listener The listener to add.
     */
    void addDeathListener(DeathListener* listener);

    /**
     * @brief Add a health changed listener.
     * @param listener The listener to add.
     */
    void addHealthChangedListener(HealthChangedListener* listener);

    /**
     * @brief Add an interaction listener.
     * @param listener The listener to add.
     */
    void addInteractionListener(InteractionListener* listener);

    /**
     * @brief Add a movement listener.
     * @param listener The listener.
     */
    void addMovementListener(MovementListener* listener);

    /**
     * @brief Cause a certain amount of damage to the being.
     * @param value The amount of damage to give.
     */
    virtual void damage(unsigned int value);

    /**
     * @brief Draw the being to the screen.
     * @param renderer The graphics object.
     */
    virtual void draw(Renderer& renderer);

    /**
     * @brief Convert the state of the entity to a string to save.
     * @return A string representation of the entity.
     */
    virtual std::string extract() const;

    /**
     * @brief Each being has an alignment to which they are a member.
     * @return This being's alignment.
     * @see alignment
     */
    virtual const std::string& getAlignment() const;

    /**
     * @brief Get the current defense.
     * @return The current defense value.
     */
    const int getDefense() const;

    /**
     * @brief Get the collision area of this being.
     * @return The collision area.
     */
    const Rectangle getDimension() const;

    /**
     * @brief Get the current health value.
     * @return The current health value.
     */
    unsigned int getHealth() const;

    /**
     * @brief Get the being's height.
     * @return The being's height.
     */
    unsigned int getHeight() const;

    /**
     * @brief Get this entities specific ID.
     * @return The unique ID number for this creature.
     */
    unsigned int getId() const;

    /**
     * @brief Get the current maximum possible defense.
     * @return The maximum possible defense.
     */
    const int getMaxDefense() const;

    /**
     * @brief Get the maximum possible health value for this creature.
     * @return The maximum health.
     */
    unsigned int getMaxHealth() const;

    /**
     * @brief Get the name of the entity.
     * @return The name of the entity.
     */
    const std::string& getName() const;

    /**
     * @brief Get the current position of this being.
     * @return The current position of this being.
     */
    virtual const Vector& getPosition() const;

    /**
     * @brief Get the type of being this is.
     * @return The type of being.
     */
    virtual EntityType getType() const;

    /**
     * @brief Get's the visible area.
     * @return The dimension of the visible area.
     */
    virtual const Rectangle getVisibleArea() const;

    /**
     * @brief Get the being's width.
     * @return The being's width.
     */
    unsigned int getWidth() const;

    /**
     * @brief Get the x position.
     * @return The x position.
     */
    const double& getX() const;

    /**
     * @brief Get the y position.
     * @return The y position.
     */
    const double& getY() const;

    /**
     * @brief A creature is grabbing this entity.
     * @param creature The creature.
     */
    virtual void grab(Creature* creature);

    /**
     * @brief Handle input.
     * @param input The current input state.
     */
    virtual void handleInput(const Input& input);

    /**
     * @brief Interact with an entity.
     * @param entity The entity.
     */
    virtual void interact(Entity& entity);

    /**
     * @brief Checks the collision state of the being.
     * @return The collision state of the being.
     */
    virtual bool isCollidable() const;

    /**
     * @brief Determines the living status of this entity.
     * @return True if the entity is not dead.
     * @note Please note that, as this is a zombie game, I use the term 'dead' loosly...
     */
    bool isDead() const;

    /**
     * @brief Checks to see if this entity is colliding with an area.
     * @param area The area to check.
     * @return True if an intersection exists.
     */
    virtual bool isIntersecting(const Quadrilateral& area) const;

    /**
     * @brief Perform internal logic.
     * @param eData The level environment in which this entity resides.
     */
//    virtual void logic(EnvironmentData& eData);@todo review

    /**
     * @brief Look at the provided point.
     * @param point The point to look at.
     *
     * @note This is unimplemented in Entity.
     */
    virtual void lookAt(const Vector& point);

    /**
     * @brief A creature is releasing it's grasp of this entity.
     * @param creature The creature.
     */
    virtual void release(Creature* creature);

    /**
     * @brief Remove an animation cycle listener.
     * @param listener The listener to remove.
     */
    void removeAnimationCycleListener(AnimationCycleListener* listener);

    /**
     * @brief Remove a death listener.
     * @param listener The listener to add.
     */
    void removeDeathListener(DeathListener* listener);

    /**
     * @brief Remove a health changed listener.
     * @param listener The listener to add.
     */
    void removeHealthChangedListener(HealthChangedListener* listener);

    /**
     * @brief Add an interaction listener.
     * @param listener The listener to add.
     */
    void removeInteractionListener(InteractionListener* listener);

    /**
     * @brief Remove a movement listener.
     * @param listener The listener to remove.
     */
    void removeMovementListener(MovementListener* listener);

    /**
     * @brief Set this being's alignment.
     * @param alignment The alignment to set.
     */
    virtual void setAlignment(const std::string& alignment);

    /**
     * @brief Set the animating state of the entity.
     * @param state The state to set.
     */
    virtual void setAnimating(bool state);

    /**
     * @brief Set the collision state of the entity.
     * @param state The state to set.
     */
    virtual void setCollision(bool state);

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
    void setX(double x);

    /**
     * @brief Set the Y position.
     * @param y The y position.
     */
    void setY(double y);

    protected:
    /**
     * @brief A being is a 'sprite of substance' for gameplay.  Creatures are beings, GUI animations are sprites.
     * @param name The name of the entity.
     * @param maxHealth The maximum health for this entity.
     * @param maxDefense The maximum defense value for this entity.
     * @param collisionArea The collision area.
     *
     * @see mCollisionArea
     */
    Entity(const std::string& name, unsigned int maxHealth, unsigned int maxDefense, const Rectangle& collisionArea);

    /**
     * @brief This entity collided with the collidee
     * @param collidee The entity that has collided with this entity.
     */
    virtual void mCollision(Entity& collidee);

    /**
     * @brief This performs common operations when an entity has died (health has reached 0 or otherwise killed)
     */
    virtual void mDie();

    /**
     * @brief Get the collision area.
     * @return The collision offset.
     */
    const Rectangle& mGetCollisionArea() const;

    /**
     * @brief Checks if this sprite is performing any actions.
     * @return True if this sprite has actions in its queue.
     */
    bool mIsPerforming() const;

    /**
     * @brief Push an interaction event.
     * @param actor The acting being.
     *
     * @note This should be called by each derivative of this class.
     */
     void mPushInteraction(Entity* actor);

     /**
      * @brief Push a movement event to the listeners.
      */
     void mPushMovementEvent();

    /**
     * @brief Set this being's displaying animation.
     * @param sprite The animation to set.
     */
    virtual void mSetAnimation(const Sprite& sprite);

    /**
     * This entity's specific ID.
     */
    unsigned int mId;

    /**
     * The entity's defense value represents how much force has been placed against them if they have been pushed.
     * It regenerates (through the regeneration rate) 10 times / second.
     */
    int mDefense;
    unsigned int mMaxDefense;
    int mDefenseRegenerationRate;
    Timer mDefenseRegenerationTimer;

    /**
     * An entity is 'dead' when its health has reached zero or below.
     */
    int mHealth;
    unsigned int mMaxHealth;

    /**
     * The collidability state of this being.
     */
    bool mCollidable;

    /**
     * This being's alignment.
     */
    std::string mAlignment;

    /**
     * The being type.
     */
    EntityType mType;

    /**
     * This is a set of creatures currently holding onto this entity.
     */
    std::set<Creature*> mHoldingAttackers;

    /**
     * The displaying sprite for this being.
     */
    Sprite mSprite;

    private:
    /**
     * The counter for each specific entity.
     */
    static unsigned int mIdCounter;

    /**
     * The name of the entity.
     */
    std::string mName;

    /**
     * The collision area of the being.
     *
     * The X and Y values are the offset of the collision area in comparison to the rest of the sprite.
     */
    Rectangle mCollisionArea;

    /**
     * The position of the entity in the game world.
     */
    Vector mPosition;

    /**
     * The listeners.
     */
    std::list<DeathListener*> mDeathListeners;
    std::list<HealthChangedListener*> mHealthChangedListener;
    std::list<InteractionListener*> mInteractionListeners;
    std::list<MovementListener*> mMovementListeners;

    /**
     * True if the entity is dead.
     */
    bool mIsDead;
};

/**
 * @brief Get the closest entity of a collection.
 * @param collection The collection to iterate through.
 * @param entity The entity to compare distance to.
 * @return The closest entity or null, if the collection is empty.
 */
Entity* getClosestEntity(const std::set<Entity*>& collection, Entity& entity);

/**
 * The pause time interval for the indication animation.
 */
extern const uint SPRITE_INDICATOR_ANIMATION_INTERVAL;

/**
 * The distance a sprite is pushed (in px) if pushed.
 */
extern const int PUSH_DISTANCE;

/**
 * @brief Accept 2 beings and return the one with the lower Z index.
 * @param beingA The first being.
 * @param beingB The second being.
 * @return True if the first being is of a lower Z-Index than the other.
 */
bool sortByZIndex(const Entity* beingA, const Entity* beingB);

#endif /* ENTITY_HPP_ */
