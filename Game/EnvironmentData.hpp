/*
 * EnvironmentData.hpp
 *
 *  Created on: May 14, 2010
 *      Author: the-saint
 */
#ifndef ENVIRONMENTDATA_HPP_
#define ENVIRONMENTDATA_HPP_

#include <deque>
#include <list>
#include <set>
#include <string>

#include "../Listeners/CreatureMovedToPointListener.hpp"
#include "../Listeners/DeathListener.hpp"
#include "../Math/Ellipse.hpp"
#include "../Entities/EntityData.hpp"
#include "../Entities/EntityType.hpp"
#include "../Listeners/EnvironmentRequestListener.hpp"
#include "../Interfaces/EventInterface.hpp"
#include "../Game/Input.hpp"
#include "../MapInfo/Map.hpp"
#include "../Listeners/MovementListener.hpp"
#include "../Math/Quadrilateral.hpp"
#include "../LevelInfo/RectData.hpp"
#include "../Math/Rectangle.hpp"
#include "../Engine/Renderer.hpp"
#include "../Math/Vector.hpp"

class Entity;

/**
 * @brief The environment data possesses all environmental aspects of the world.  Each level has it's own data object
 * to represent a common object for entities to move, interact, and be seen by other entities.
 *
 * @todo Is the EnvironmentRequestListener needed, now that I've implemented EventInterface in the EnvironmentData
 */
class EnvironmentData : public DeathListener, public EnvironmentRequestListener, public EventInterface, public EventListener, public MovementListener
{
	public:
	/**
	 * @brief Default constructor.
	 * @param map The environment's map.
	 * @param entities The entities in this environment.
	 * @param areas These are the entity entrance areas (for plot devices, etc...)
	 */
	EnvironmentData(Map& map, const std::list<Entity*>& entities, const std::list<RectData> areas = std::list<RectData>());

	/**
	 * @brief Copy constructor.
	 * @param eData The data to copy from.
	 */
	EnvironmentData(const EnvironmentData& eData);
	virtual ~EnvironmentData();

    /**
     * @brief Assignment operator.
     * @param eData The data from which to copy.
     */
    EnvironmentData& operator=(const EnvironmentData& eData);

	/**
	 * @brief Add a creature to the environment.
	 * @param entity The entity to add.
	 */
	virtual void addEntity(Entity* entity);

    /**
     * @brief Draw a light for this frame.
     * @param area The area to draw.
     */
    virtual void addLight(const Ellipse& area);

    /**
     * @brief Draw a light for this frame.
     * @param area The area to draw.
     */
    virtual void addLight(const Quadrilateral& area);

    /**
     * @brief Check for a collision between the entity and the objects.
     * @param entity The entity to check.
     * @return The first entity collided with, or null if none found.
     * @note This method accepts a entity and will ensure that the collision detection will exclude that entity.
     */
    virtual std::set<Entity*> checkCollision(Entity& entity);

    /**
     * @brief Check for a collision between the quadrilateral and the entities.
     * @param area The area to check.
     * @param callers The calling entities (if there are any).
     * @return A collection of all entities in the collision area.
     *
     * @note If the second argument is ignored, then all entities in the area area checked.
     */
    virtual std::set<Entity*> checkCollision(const Quadrilateral& area, const std::set<Entity*>& callers = std::set<Entity*>());

    /**
     * @brief Called when the entity has died.
     * @param entity The entity who died.
     */
    virtual void deathOccurred(Entity& entity);

	/**
	 * @brief Draw entities and effects.
	 * @param renderer The renderer with which to draw.
	 */
	virtual void draw(Renderer& renderer);

	/**
	 * @brief Draw the lighting.
	 * @param renderer The renderer with which to draw.
	 */
	virtual void drawLighting(Renderer& renderer);

    /**
     * @brief An entity has moved.
     * @param entity The entity that moved.
     */
    virtual void entityMoved(Entity& entity);

    /**
     * @brief An event occurred.
     * @param event The game event.
     * @param content Additional content.
     * @param creatureMovedToPointListener A potential listener for when a creature moves to a point.  @todo is this needed?
     */
    virtual void eventOccurred(Event event, const std::string& content = "", CreatureMovedToPointListener* creatureMovedToPointLisener = 0);

    /**
     * @brief Extract the objects.
     * @return The objects in a base64 data string.
     */
    virtual std::string extract() const;

    /**
     * @brief Look for an entity with the provided id.
     * @param id The id of the entity to retrieve.
     * @return The entity with the matching unique ID, or NULL if not found.
     */
    Entity* getEntity(unsigned int id);

    /**
     * @brief Look for an entity with the provided name/keyword.
     * @param name The name of the entity.
     * @return The first entity with the matching name, or NULL if not found.
     */
    Entity* getEntity(const std::string& name);

    /**
     * @brief Get the current lighting state.
     * @return True if all lights in the environment are on (everything is visible).  False if only generated lights are shown.
     */
    virtual bool getLightingState() const;

    /**
     * @brief Get the viewport offset.
     * @return The offset.
     */
    virtual const Vector& getOffset() const;

    /**
     * @brief Return the viewport's X offset.
     * @return The X offset.
     */
    virtual int getXOffset() const;

    /**
     * @brief Return the viewport's Y offset.
     * @return The Y offset.
     */
    virtual int getYOffset() const;

    /**
     * @brief Handle input.
     * @param input The current input state.
     */
    virtual void handleInput(const Input& input);

	/**
	 * @brief Load previously saved environmental data.
	 * @param data The base64 data.
	 * @note All data is cleared from the environment before the information is loaded.
	 * @todo Review loading code.
	 */
	virtual void load(const std::string& data);

	/**
	 * @brief Perform environmental logic.
	 */
	virtual void logic();

	/**
	 * @brief Remove a creature from the environment.
	 * @param name The name of the creature to remove.
	 *
	 * @note Children of this class should remove all creatures with the provided name.
	 */
	virtual void removeEntity(const std::string& name);

    /**
     * @brief Toggle lighting and shadows on and off.
     * @param state Set to true to enable shadows or false to simply show all things on screen.
     */
    virtual void setLightingState(bool state);

    /**
     * @brief Set the viewport offset.
     * @param offset The offset.
     */
    virtual void setOffset(const Vector& offset);

	private:
    /**
     * @brief Remove all entities on the removal list.
     */
    void mClearRemoved();

    /**
     * The map.
     */
    Map& mMap;

    /**
     * The entities on the map.
     */
    std::list<Entity*> mEntities;

	/**
	 * The lighting information.
	 */
	bool mLightingState;
	std::list<Ellipse> mEllipseLights;
	std::list<Quadrilateral> mQuadLights;

	/**
	 * This is the collection of areas which fire an event if a creature enters them.
	 */
	std::list<RectData> mAreas;

	/**
	 * The offsets.
	 */
	Vector mViewportOffset;

    /**
     * A deque for removing entities (using a deque as this is potentially iterated through each loop iteration)
     */
    std::deque<Entity*> mRemoval;
};

#endif /* ENVIRONMENTDATA_HPP_ */
