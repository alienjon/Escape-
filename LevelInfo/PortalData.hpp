/*
 * PortalData.hpp
 *
 *  Created on: Jun 3, 2010
 *      Author: the-saint
 */

#ifndef PORTALDATA_HPP_
#define PORTALDATA_HPP_

#include <string>

struct PortalData
{
	/**
	 * @brief Default constructor for ease of use.
	 */
	PortalData(const std::string& _a, const std::string& _mapB, const std::string& _b) : portalA(_a), portalBMap(_mapB), portalB(_b)
	{}

	/**
	 * The name of the entry portal.
	 */
	std::string portalA;

	/**
	 * The name of the map of the second portal.
	 */
	std::string portalBMap;

	/**
	 * The name of the second portal.
	 */
	std::string portalB;
};

#endif /* PORTALDATA_HPP_ */
