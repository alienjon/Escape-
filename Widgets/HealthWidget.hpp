/*
 * HealthWidget.hpp
 *
 *  Created on: Aug 5, 2009
 *      Author: alienjon
 */
#ifndef HEALTHWIDGET_HPP_
#define HEALTHWIDGET_HPP_

#include "../guichan.hpp"
#include "../Listeners/HealthChangedListener.hpp"

class Entity;

/**
 * @brief A widget to display the player's health.
 */
class HealthWidget : public gcn::Widget, public HealthChangedListener
{
    public:
    /**
     * @brief Display a entity's health.
     * @param entity The entity this widget is tracking.
     * @param width The width of the widget.
     * @param height The height of the widget.
     */
    HealthWidget(Entity* entity, unsigned int width, unsigned int height);

    /**
     * @brief Draw the widget.
     * @param graphics The graphics object to draw with.
     */
    virtual void draw(gcn::Graphics* graphics);

    /**
     * @brief Returns the entity this widget is listening to.
     * @return The entity.
     */
    inline Entity* getEntity() const
	{
		return mEntity;
	}

    /**
     * @brief The player's health has changed.
     * @param entity The entity whose health has changed.
     */
    virtual void healthChanged(Entity* entity);

    private:
    /**
     * The held entity.
     */
    Entity* mEntity;

    /**
     * The background.
     */
    gcn::Rectangle mBackground;

    /**
     * The strength area to draw.
     */
    gcn::Rectangle mStrengthBox;

    /**
     * The health area to draw.
     */
    gcn::Rectangle mHealthBox;

    /**
     * The internal measure's max width.
     */
    unsigned int mInternalMaxWidth;
};

#endif /* HEALTHWIDGET_HPP_ */
