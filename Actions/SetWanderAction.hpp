/*
 * SetWanderAction.hpp
 *
 *  Created on: Aug 7, 2009
 *      Author: alienjon
 */

#ifndef SETWANDERACTION_HPP_
#define SETWANDERACTION_HPP_

#include "Action.hpp"

class Creature;

/**
 * @brief An action that sets the wandering state of a creature.
 */
class SetWanderAction : public Action
{
    public:
    /**
     * @brief Set the creature's wandering state.
     * @param creature The creature.
     * @param state The wandering state to set.
     */
    SetWanderAction(Creature* creature, bool state);

    /**
     * @brief Activate the action.
     * @param eData The environment data.
     */
    virtual void activate(EnvironmentData& eData);

    private:
    /**
     * The creature.
     */
    Creature* mCreature;

    /**
     * The state.
     */
    bool mState;
};

#endif /* SETWANDERACTION_HPP_ */
