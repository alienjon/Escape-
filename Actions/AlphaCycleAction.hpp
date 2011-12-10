/*
 * AlphaCycleAction.hpp
 *
 *  Created on: Dec 6, 2011
 *      Author: alienjon
 */
#ifndef ALPHACYCLEACTION_HPP_
#define ALPHACYCLEACTION_HPP_

#include <SFML/Graphics.hpp>

#include "../Actions/Action.hpp"

/**
 * @brief An action to decrease and then increase the alpha level of a drawable.
 */
class AlphaCycleAction : public Action
{
	public:
	AlphaCycleAction(sf::Drawable& drawable);

    /**
     * @brief Activate this action.
     * @param level Level in which the action takes place.
     */
    virtual void activate(Level& level);

	private:
	// The drawable to set the opacity of.
	sf::Drawable& mDrawable;

	// If true then the action is increasing opacity, false is decreasing.
	bool mIsAddingAlpha;
};

#endif /* ALPHACYCLEACTION_HPP_ */
