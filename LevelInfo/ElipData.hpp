/*
 * ElipData.hpp
 *
 *  Created on: Jun 11, 2010
 *      Author: the-saint
 */

#ifndef ELIPDATA_HPP_
#define ELIPDATA_HPP_

#include <string>

#include "../Math/Ellipse.hpp"

struct ElipData
{
	/**
	 * Default constructor for ease of use.
	 */
	ElipData(const std::string& _n, const Ellipse& _e) : name(_n), area(_e)
	{}

	/**
	 * The name.
	 */
	std::string name;

	/**
	 * The area.
	 */
	Ellipse area;
};


#endif /* ELIPDATA_HPP_ */
