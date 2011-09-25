/*
 * NonDisplayingEntity.hpp
 *
 *  Created on: Aug 12, 2009
 *      Author: alienjon
 */

#ifndef NONDISPLAYINGENTITY_HPP_
#define NONDISPLAYINGENTITY_HPP_

#include "../../Game/Direction.hpp"
#include "../Entity.hpp"
#include "../../Math/Rectangle.hpp"
#include "../../Engine/Renderer.hpp"

/**
 * @brief A non-displaying entity is an entity that exists but is not seen.
 *
 * These entities are mainly used for triggers (such as the object to
 * interact with in order to load the next level)
 */
class NonDisplayingEntity : public Entity
{
    public:
    /**
     * @brief Construct a non displaying being.
     * @param name The name of the entity.
     * @param area The dimension of the being.
     */
    NonDisplayingEntity(const std::string& name, const Rectangle& area);


    /**
     * @brief Cannot damage a basic non-displaying being.
     * @param damage The damage to perform.
     */
    virtual void damage(unsigned int);

    /**
     * @brief Override the being's call to logic.
     * @param renderer The graphics object.
     *
     * This method will draw a colored box in the event of debugging.
     */
    virtual void draw(Renderer& renderer);

    /**
     * @brief Perform internal logic.
     * @param eData The level environment in which this entity resides.
     */
//    virtual void logic(EnvironmentData& eData);//@todo review
};

#endif /* NONDISPLAYINGENTITY_HPP_ */
