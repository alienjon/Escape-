/*
 * EnvironmentRequestListener.hpp
 *
 *  Created on: Jun 28, 2010
 *      Author: the-saint
 */

#ifndef ENVIRONMENTREQUESTLISTENER_HPP_
#define ENVIRONMENTREQUESTLISTENER_HPP_

#include <string>

/**
 * @brief A listener for environmental alterations.
 */
class EnvironmentRequestListener
{
	public:
	/**
	 * @brief Determine the current lighting state.
	 * @return True if the environment is fully visible.
	 */
	virtual bool getLightingState() const = 0;

	/**
	 * @brief Change the lighting state (visibility) of an environment.
	 * @param state The state to change the lighting to.
	 */
	virtual void setLightingState(bool state) = 0;
};

#endif /* ENVIRONMENTREQUESTLISTENER_HPP_ */
