/*
 * Item
 *
 *  Created on: Aug 18, 2009
 *      Author: alienjon
 */

#ifndef ITEM_HPP
#define ITEM_HPP

#include "../../Game/Direction.hpp"
#include "../../Entities/Entity.hpp"
#include "../../Entities/Templates/EntityTemplate.hpp"

class Creature;
class EnvironmentData;

/*
 * @brief An item that can be picked up by a creature.
 */
class Item : public Entity
{
    public:
    /**
     * @brief A default collectable item.
	 * @param name The name of the flashlight.
	 * @param tmpl The animation template this light displays while on the map.
     */
    Item(const std::string& name, const EntityTemplate& tmpl);

    /**
     * @brief You can't damage collectable items (Unless stated otherwise in derived classes)
     * @param damage The damage to perform.
     */
    virtual void damage(unsigned int damage);

    /**
     * @brief Logic performed when the item is being held.
     * @param eData The environment data the item is in.
     * @param holder The creature holding the item.
     */
    virtual void heldLogic(EnvironmentData& eData, Creature& holder);

    /**
     * @brief Collectable items aren't pushed but, rather, are picked up as they are walked into.
     * @param dir The direction to push.
     * @param force The force with which to push.
     */
    virtual void push(Direction dir, unsigned int force);

    protected:
    /**
     * @brief As above, collectable items are not pushed but, rather, are walked into.
     * @param dir The direction being pushed.
     */
    virtual void mPushedBack(Direction dir);
};

#endif /* ITEM_HPP */
