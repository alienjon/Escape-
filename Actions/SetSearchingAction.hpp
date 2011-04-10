/*
 * SetSearchingAction.hpp
 *
 *  Created on: May 2, 2009
 *      Author: alienjon
 */
#ifndef SETSEARCHINGACTION_HPP_
#define SETSEARCHINGACTION_HPP_

#include "Action.hpp"

class Creature;

/**
 * @brief An action that sets the searching state of an enemy.
 */
class SetSearchingAction : public Action
{
    public:
    /**
     * @brief Set the searching state of an enemy.
     * @param creature The creature whose searching state we are setting.
     * @param state The state being set.
     */
    SetSearchingAction(Creature& enemy, bool state);

    /**
     * @brief Activate this event.
     * @param eData The environment data.
     */
    virtual void activate(EnvironmentData& eData);

    protected:
    /**
     * The creature.
     */
    Creature& mCreature;

    /**
     * The state to set.
     */
    bool mState;
};

#endif /* SETSEARCHINGACTION_HPP_ */
