/*
 * SlideAction.hpp
 *
 *  Created on: May 2, 2009
 *      Author: alienjon
 */
#ifndef SLIDEACTION_HPP_
#define SLIDEACTION_HPP_

#include "Action.hpp"

#include "../Game/Direction.hpp"
#include "../Entities/Entity.hpp"
#include "../Math/Vector.hpp"

/**
 * @brief An action that slides a creature to a certain point.
 */
class SlideAction: public Action
{
    public:
    /**
     * @brief Slide a being in the provided direction for the provided distance.
     * @param being The being to slide.
     * @param destPt A point on the destination line.
     * @param distance The distance (in pixels) to slide the being.
     */
    SlideAction(Entity& being, const Vector& destPt, unsigned int distance);

    /**
     * @brief Start sliding the being.
     * @param eData The environment data.
     */
    virtual void activate(EnvironmentData& eData);

    protected:
    /**
     * The being to slide.
     */
    Entity& mEntity;

    /**
     * A point on the line to move towards.
     */
    Vector mDestPoint;

    /**
     * The number of pixels to slide the being.
     */
    unsigned int mDistance;
};

#endif /* SLIDEACTION_HPP_ */
