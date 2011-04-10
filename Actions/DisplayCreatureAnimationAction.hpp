/*
 * DisplayCreatureAnimationAction.hpp
 *
 *  Created on: Aug 17, 2010
 *      Author: the-saint
 */
#ifndef DISPLAYCREATUREANIMATIONACTION_HPP_
#define DISPLAYCREATUREANIMATIONACTION_HPP_

#include "Action.hpp"
#include "../Listeners/AnimationCycleListener.hpp"
#include "../Entities/Creatures/CreatureAnimationState.hpp"

class Creature;
class EnvironmentData;

/**
 * @brief An action to tell a being to display a certain animation.
 */
class DisplayCreatureAnimationAction : public Action, public AnimationCycleListener
{
    public:
    /**
     * @brief An action to display an animation for a sprite.
     * @param entity The entity whose animation we will change.
     * @param state The animation state to display.
     * @param count The number of times the animation is to be displayed (0 for infinite)
     * @param reset True if the animation counter should be reset.
     * @note If count = 0 then the animation is set permenantly.
     */
	DisplayCreatureAnimationAction(Creature& creature, CreatureAnimationState state, unsigned int count);
    ~DisplayCreatureAnimationAction();

    /**
     * @brief Activate the action.
     * @param eData The environment data.
     */
    virtual void activate(EnvironmentData& eData);

    /**
     * @brief The entity's animation was cycled.
     */
    virtual void animationCycled();

    protected:
    /**
     * The creature.
     */
    Creature& mCreature;

    /**
     * The creature animation type.
     */
    CreatureAnimationState mState;

    /**
     * The length of time to display the animation.
     */
    unsigned int mCount;

    /**
     * True if the animation is to display indefinitely.
     */
    bool mInfinite;
};

#endif /* DISPLAYCREATUREANIMATIONACTION_HPP_ */
