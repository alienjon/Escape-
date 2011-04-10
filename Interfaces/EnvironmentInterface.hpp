/*
 * EnvironmentInterface.hpp
 *
 *  Created on: Jun 28, 2010
 *      Author: the-saint
 */

#ifndef ENVIRONMENTINTERFACE_HPP_
#define ENVIRONMENTINTERFACE_HPP_

#include <list>

#include "../Listeners/EnvironmentRequestListener.hpp"

/**
 * @brief An interface which will push events to environment request listeners.
 */
class EnvironmentInterface
{
	public:
	/**
	 * @brief Add an environmental request listener.
	 * @param listener The listener to add.
	 */
	static void addEnvironmentalRequestListener(EnvironmentRequestListener* listener);

	/**
	 * @brief Remove an environmental request listener.
	 * @param listener The listener to remove.
	 */
	static void removeEnvironmentalRequestListener(EnvironmentRequestListener* listener);

	protected:
	/**
	 * @brief Distribute a request for the current lighting state.
	 * @return The lighting state.
	 */
	static bool mDistributeLightingStateRequest();

	/**
	 * @brief Distribute a request to set the current lighting state.
	 * @param state The lighting state to set.
	 */
	static void mDistributeSetLightingStateRequest(bool state);

	private:
	/**
	 * The listeners.
	 */
	static std::list<EnvironmentRequestListener*> mEnvironmentalRequestListeners;
};

#endif /* ENVIRONMENTINTERFACE_HPP_ */
