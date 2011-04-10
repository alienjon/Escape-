/*
 * HealthBarContainer.cpp
 *
 *  Created on: May 18, 2010
 *      Author: the-saint
 */
#include "HealthBarContainer.hpp"

#include "../Entities/Creatures/Creature.hpp"

using std::list;

const unsigned int HEALTHBARCONTAINER_BUFFER = 5;
const unsigned int HEALTHBAR_WIDTH = 150;
const unsigned int HEALTHBAR_HEIGHT= 25;

HealthBarContainer::HealthBarContainer()
{
	setSize(HEALTHBAR_WIDTH, 0);
}

HealthBarContainer::~HealthBarContainer()
{
}

void HealthBarContainer::add(Entity* entity)
{
	// Create the new display, add it to the list, and display it on the screen.
	HealthWidget* widget = new HealthWidget(entity, HEALTHBAR_WIDTH, HEALTHBAR_HEIGHT);

	// If there aren't any other health bars, then add this one at the top.
	if(mHealthBars.empty())
	{
		gcn::Container::add(widget, 0, 0);
	}
	else
	{
		HealthWidget* last = mHealthBars.back();
		gcn::Container::add(widget, 0, last->getY() + last->getHeight() + HEALTHBARCONTAINER_BUFFER);
	}

	// Add the widget.
	mHealthBars.push_back(widget);

	// Resize the widget's height.
	setHeight(getHeight() + HEALTHBAR_HEIGHT);
}

void HealthBarContainer::remove(Entity* entity)
{
	for(list<HealthWidget*>::iterator it = mHealthBars.begin(); it != mHealthBars.end(); ++it)
	{
		if((*it)->getEntity() == entity)
		{
			mHealthBars.erase(it);
			setHeight(getHeight() - HEALTHBAR_HEIGHT);
			return;
		}
	}
}
