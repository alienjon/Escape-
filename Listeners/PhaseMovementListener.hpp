/*
 * PhaseMovementListener.hpp
 *
 *  Created on: Dec 7, 2011
 *      Author: alienjon
 */
#ifndef PHASEMOVEMENTLISTENER_HPP_
#define PHASEMOVEMENTLISTENER_HPP_

#include <SFML/System.hpp>

/**
 * @brief A listener for an object to phase to a specified position.
 */
class PhaseMovementListener
{
	public:
    /**
     * @brief Phase this creature to the specified position.
     * @param vec The position to phase the creature to.
     */
    virtual void phaseTo(const sf::Vector2f& vec) = 0;
};

#endif /* PHASEMOVEMENTLISTENER_HPP_ */
