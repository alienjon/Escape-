/*
 * DisplaySpriteAction.hpp
 *
 *  Created on: Aug 14, 2009
 *      Author: alienjon
 */

#ifndef DISPLAYSPRITEACTION_HPP_
#define DISPLAYSPRITEACTION_HPP_

#include "Action.hpp"

#include "../guichan.hpp"

#include "../Listeners/AnimationCycleListener.hpp"
#include "../Engine/Sprite.hpp"
#include "../Widgets/SpriteWidget.hpp"
#include "../Math/Vector.hpp"

/*
 * @brief An action to display a sprite in the game.
 */
class DisplaySpriteAction : public Action, public AnimationCycleListener
{
    public:
    /**
     * @brief Display a sprite in a gcn::Container.
     * @param sprite The sprite to display.
     * @param loc The location to add the sprite in the container.
     * @param container The container to put the sprite widget in.
     * @param loops The number of times to display the animation before removing it (can't do infinite here so 0 doesn't display at all)
     */
    DisplaySpriteAction(const Sprite& sprite, const Vector& loc, gcn::Container* container, unsigned int loops);
    virtual ~DisplaySpriteAction();

    /**
     * @brief Activate the action.
     * @param eData The environment data.
     */
    virtual void activate(EnvironmentData& eData);

    /**
     * @brief An animation cycle has occurred.
     */
    virtual void animationCycled();

    private:
    /**
     * The sprite to display.
     */
    Sprite mSprite;

    /**
     * The location to display the sprite.
     */
    Vector mPoint;

    /**
     * The holding container and a sprite widget, if there is one.
     */
    gcn::Container* mContainer;
    SpriteWidget mSpriteWidget;

    /**
     * The remaining number of cycles left.
     */
    unsigned int mCounter;
};

#endif /* DISPLAYSPRITEACTION_HPP_ */
