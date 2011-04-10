/*
 * GreenZombie.hpp
 *
 *  Created on: Jun 19, 2009
 *      Author: alienjon
 */

#ifndef GREENZOMBIE_HPP_
#define GREENZOMBIE_HPP_

#include "../Creature.hpp"

/**
 * @brief The green zombie.
 */
class GreenZombie : public Creature
{
    friend class ObjectManager;

    public:
    /**
     * @brief Convert the state of the entity to a string to save.
     * @return A string representation of the entity.
     */
    virtual std::string extract() const;

//    protected: @todo
    /**
     * @brief Construct a new green zombie.
     */
    GreenZombie();
//@todo temporary
virtual void mCreatureInteract(Entity* entity) {}

    /**
     * @brief Construct the entity from the data string.
     * @param data The data string with which to create the entity.
     */
    GreenZombie(const std::string& data);
};

#endif /* GREENZOMBIE_HPP_ */
