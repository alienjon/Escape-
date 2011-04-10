/*
 * PlayerHealthWidget.cpp
 *
 *  Created on: Aug 5, 2009
 *      Author: alienjon
 */
#include "HealthWidget.hpp"

#include "../Entities/Entity.hpp"

const unsigned int HEALTHWIDGET_BORDER = 1;

HealthWidget::HealthWidget(Entity* entity, unsigned int width, unsigned int height) : mEntity(entity),
	mInternalMaxWidth(width - (HEALTHWIDGET_BORDER * 2))
{
	// Tell the entity that this widget wants to listen for health changes.
	entity->addHealthChangedListener(this);

    // Set the colors.
    setBaseColor(gcn::Color(0, 0, 255));
    setForegroundColor(gcn::Color(0, 255, 0));
    setBackgroundColor(gcn::Color(255, 0, 0));

    // Set the size.
    setSize(width, height);
    mBackground.setAll(0, 0, getWidth(), getHeight());
    mStrengthBox = gcn::Rectangle(HEALTHWIDGET_BORDER, HEALTHWIDGET_BORDER, mInternalMaxWidth, (height - (HEALTHWIDGET_BORDER * 2)) / 2);
    mHealthBox = gcn::Rectangle(HEALTHWIDGET_BORDER, HEALTHWIDGET_BORDER + mStrengthBox.height, mInternalMaxWidth, (height - (HEALTHWIDGET_BORDER * 2)) / 2);

    // Draw a border.
    setFrameSize(2);
}

void HealthWidget::draw(gcn::Graphics* graphics)
{
    // Draw the foreground as the background.
    graphics->setColor(getBaseColor());
    graphics->fillRectangle(mBackground);
    graphics->setColor(getBackgroundColor());
    graphics->fillRectangle(mHealthBox);
    graphics->setColor(getForegroundColor());
    graphics->fillRectangle(mStrengthBox);
}

void HealthWidget::healthChanged(Entity* entity) // @todo change this to reference, not pointer.
{
    // Update the health display.
	mStrengthBox.width = mInternalMaxWidth * ((double)entity->getDefense() / (double)entity->getMaxDefense());
    mHealthBox.width = mInternalMaxWidth * ((double)entity->getHealth() / (double)entity->getMaxHealth());
}
