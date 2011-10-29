/*
 * AnimationCycleListener.hpp
 *
 *  Created on: Aug 5, 2009
 *      Author: alienjon
 */
#ifndef ANIMATIONCYCLELISTENER_HPP_
#define ANIMATIONCYCLELISTENER_HPP_

/**
 * @brief An interface to listen for when a sprite has finished cycling an animation.
 */
class AnimationCycleListener
{
    public:
    /**
     * @brief An entity's animation was cycled.
     */
    virtual void animationCycled() = 0;
};

#endif /* ANIMATIONCYCLELISTENER_HPP_ */
