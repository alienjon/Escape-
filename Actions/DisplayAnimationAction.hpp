/*
 * DisplayAnimationAction.hpp
 *
 *  Created on: May 21, 2009
 *      Author: alienjon
 */
#ifndef DISPLAYANIMATIONACTION_HPP_
#define DISPLAYANIMATIONACTION_HPP_

#include "../Actions/Action.hpp"
#include "../Listeners/AnimationCycleListener.hpp"
#include "../Engine/Sprite.hpp"

class Entity;

/**
 * @brief An action to tell a being to display a certain animation.
 */
class DisplayAnimationAction : public Action, public AnimationCycleListener
{
    public:
    /**
     * @brief An action to display an animation for a sprite.
     * @param entity The entity whose animation we will change.
     * @param sprite The sprite to display.
     * @param count The number of times the animation is to be displayed (0 for infinite)
     * @param reset True if the animation counter should be reset.
     * @note If count = 0 then the animation is set permenantly.
     */
    DisplayAnimationAction(Entity& entity, const Sprite& sprite, unsigned int count);
    ~DisplayAnimationAction();

    /**
     * @brief Activate the action.
     * @param level The level in which the action takes place.
     */
    virtual void activate(Level& level);

    /**
     * @brief The entity's animation was cycled.
     */
    virtual void animationCycled();

    protected:
    /**
     * The entity.
     */
    Entity& mEntity;

    /**
     * The animation.
     */
    Sprite mSprite;

    /**
     * The length of time to display the animation.
     */
    unsigned int mCount;

    /**
     * True if the animation is to display indefinitely.
     */
    bool mInfinite;
};

#endif /* DISPLAYANIMATIONACTION_HPP_ */
