/*
 * MoveToAction.hpp
 *
 *  Created on: Apr 19, 2009
 *      Author: alienjon
 */
#ifndef MOVETOACTION_HPP_
#define MOVETOACTION_HPP_

#include <SFML/System.hpp>

#include "../Actions/Action.hpp"
#include "../Listeners/CreatureWaypointListener.hpp"

class Creature;

/**
 * @brief An action that tells a creature to move to a certain point.
 */
class MoveToAction : public Action, public CreatureWaypointListener
{
    public:
    /**
     * @brief Move the creature to the specified point.
     * @param creature The creature to move.
     * @param loc The point to move the creature to.
     */
    MoveToAction(Creature& creature, const sf::Vector2f& loc);
    virtual ~MoveToAction();

    /**
     * @brief Activate the action.
     * @param level The level in which the action takes place.
     */
    virtual void activate(Level& level);

    /**
     * @brief The creature has moved to the next point on a path.
     * @param creature The creature that moved.
     */
    virtual void creatureMoved(Creature& creature);

    protected:
    // The creature to move.
    Creature& mCreature;

    // The point to move to.
    sf::Vector2f mLoc;
};

#endif /* MOVETOACTION_HPP_ */
