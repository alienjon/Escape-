/*
 * RectData.hpp
 *
 *  Created on: Jun 11, 2010
 *      Author: the-saint
 */

#ifndef RECTDATA_HPP_
#define RECTDATA_HPP_

#include <string>

#include "../Math/Rectangle.hpp"

struct RectData
{
	/**
	 * Default constructor for ease of use.
	 */
	RectData(const std::string& _n, const Rectangle& _e) : name(_n), area(_e)
	{}

	/**
	 * The name.
	 */
	std::string name;

	/**
	 * The area.
	 */
	Rectangle area;
};

#endif /* RECTDATA_HPP_ */
