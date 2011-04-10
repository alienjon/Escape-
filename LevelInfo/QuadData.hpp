/*
 * QuadData.hpp
 *
 *  Created on: Jun 11, 2010
 *      Author: the-saint
 */

#ifndef QUADDATA_HPP_
#define QUADDATA_HPP_

#include <string>

#include "../Math/Quadrilateral.hpp"

struct QuadData
{
	/**
	 * Default constructor for ease of use.
	 */
	QuadData(const std::string& _n, const Quadrilateral& _e) : name(_n), area(_e)
	{}

	/**
	 * The name.
	 */
	std::string name;

	/**
	 * The area.
	 */
	Quadrilateral area;
};

#endif /* QUADDATA_HPP_ */
