/*
 * Object.hpp
 *
 *  Created on: Jun 16, 2010
 *      Author: the-saint
 */

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include <string>

#include "../../Entities/Entity.hpp"
#include "../../Entities/EntityData.hpp"
#include "../../Entities/Templates/EntityTemplate.hpp"
#include "../../Math/Rectangle.hpp"

/**
 * @brief An object is an in-game object that cannot be collected.
 *
 * Objects may or may not be able to be pushed.  Those that can be pushed
 * are pushed immediately.
 */
class Object : public Entity
{
	public:
	/**
	 * @brief Create a new object.
     * @param name The object's name.
     * @param temp The general template this object will use.
	 */
	Object(const std::string& name, const EntityTemplate& temp);

	/**
	 * @brief Load an object from the data string.
	 * @param data The data from which to load the object.
	 */
	Object(const std::string& data);

    /**
     * @brief Cause a certain amount of damage to the being.
     * @param value The amount of damage to give.
     */
    virtual void damage(unsigned int value);

    /**
     * @brief Convert the state of the entity to a string to save.
     * @return A string representation of the entity.
     */
    virtual std::string extract() const;

    /**
     * @brief Push the being in a direction.
     * @param dir The direction the being is being pushed.
     * @param force The force with which to push the being.
     */
    virtual void push(Direction dir, unsigned int force);

	protected:
    /**
     * @brief Push back the sprite.
     * @param dir The direction being pushed backwards.
     */
    virtual void mPushed(Direction dir);
};

#endif /* OBJECT_HPP_ */
