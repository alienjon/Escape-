/*
 * LetterGUIWidget.hpp
 *
 *  Created on: Aug 19, 2009
 *      Author: alienjon
 */

#ifndef LETTERGUIWIDGET_HPP_
#define LETTERGUIWIDGET_HPP_

#include "SpriteWidget.hpp"

#include "../Listeners/AnimationCycleListener.hpp"

class Letter;

/*
 * @brief This OSD indicates changes to the player's letter collection status.
 */
class LetterGUIWidget : public SpriteWidget, public AnimationCycleListener
{
    public:
    /**
     * @brief A default letter GUI widget.
     */
    LetterGUIWidget();
    virtual ~LetterGUIWidget();

    /**
     * @brief The listening animation was cycled.
     */
    virtual void animationCycled();

    /**
     * @brief A letter was found.
     */
    virtual void letterReceived();
};

#endif /* LETTERGUIWIDGET_HPP_ */
