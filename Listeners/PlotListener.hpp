/*
 * PlotListener.hpp
 *
 *  Created on: Jun 23, 2010
 *      Author: the-saint
 */

#ifndef PLOTLISTENER_HPP_
#define PLOTLISTENER_HPP_

#include "../PlotInfo/PlotEvent.hpp"

/**
 * @brief A plot listener listens for when plot events occur.
 */
class PlotListener
{
	public:
	/**
	 * @brief A plot event occurred.
	 * @param event The plot event.
	 */
	virtual void plotOccurance(const PlotEvent& event) = 0;
};

#endif /* PLOTLISTENER_HPP_ */
