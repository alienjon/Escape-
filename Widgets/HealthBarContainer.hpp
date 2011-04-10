/*
 * HealthBarContainer.hpp
 *
 *  Created on: May 18, 2010
 *      Author: the-saint
 */
#ifndef HEALTHBARCONTAINER_HPP_
#define HEALTHBARCONTAINER_HPP_

#include <list>

#include "../guichan.hpp"

#include "HealthWidget.hpp"

class Entity;

/**
 * @brief A container to hold health bars.
 */
class HealthBarContainer : public gcn::Container
{
	public:
	HealthBarContainer();
	virtual ~HealthBarContainer();

	/**
	 * @brief Add's a new health bar.
	 * @param entity The entity to add the health bar for.
	 */
	virtual void add(Entity* entity);

	/**
	 * @brief Remove the health bar for the specified creature.
	 * @param entity The entity whose health bar is to be removed.
	 */
	virtual void remove(Entity* entity);

	private:
	std::list<HealthWidget*> mHealthBars;
};

#endif /* HEALTHBARCONTAINER_HPP_ */
