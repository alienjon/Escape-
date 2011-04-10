/*
 * MoveToAction.hpp
 *
 *  Created on: Apr 19, 2009
 *      Author: alienjon
 */
#ifndef MOVETOACTION_HPP_
#define MOVETOACTION_HPP_

#include "../Actions/Action.hpp"
#include "../Listeners/CreatureMovedToPointListener.hpp"
#include "../Math/Vector.hpp"

class Creature;

/**
 * @brief An action that tells a creature to move to a certain point.
 */
class MoveToAction : public Action, public CreatureMovedToPointListener
{
    public:
    /**
     * @brief Move the creature to the specified point.
     * @param creature The creature to move.
     * @param loc The point to move the creature to.
     * @note The location to move to is the center of the creature where the creature will come to rest.
     */
    MoveToAction(Creature& creature, const Vector& loc);
    virtual ~MoveToAction();

    /**
     * @brief Set the facing direction of the creature and determine the slope (on the first call) and move the creature on subsequent calls.
     * @param eData The environment data.
     */
    virtual void activate(EnvironmentData& eData);

    /**
     * @brief The creature has moved to the next point on a path.
     * @param creature The creature that moved.
     */
    virtual void creatureMoved(Creature& creature);

    protected:
    /**
     * The creature to move.
     */
    Creature& mCreature;

    /**
     * The point to move to.
     */
    Vector mLoc;
};

#endif /* MOVETOACTION_HPP_ */