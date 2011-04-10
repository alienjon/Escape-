/*
 * PlotEvent.hpp
 *
 *  Created on: Jun 23, 2010
 *      Author: the-saint
 */

#ifndef PLOTEVENT_HPP_
#define PLOTEVENT_HPP_

#include <string>

/**
 * @brief A plot event details when a plot event has occurred.
 */
class PlotEvent
{
	public:
	/**
	 * @brief Default constructor.
	 * @param keyword The identification for the event that occurred.
	 * @param data Additional data that occurred. @todo needed?
	 * @param node An optional plot node.
	 */
	PlotEvent(const std::string& keyword, const std::string& data = "");

	/**
	 * @brief Retrieves the data for this plot event.
	 * @return The data associated with this plot event.
	 */
	const std::string& getData() const;

	/**
	 * @brief Retrieves the keyword for this plot event.
	 * @return The plot event's keyword.
	 */
	const std::string& getKeyword() const;

	private:
	/**
	 * The plot event's data.
	 */
	std::string mKeyword,
				mData;
};

#endif /* PLOTEVENT_HPP_ */
