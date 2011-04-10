/*
 * TileData.hpp
 *
 *  Created on: Jul 13, 2010
 *      Author: the-saint
 */

#ifndef TILEDATA_HPP_
#define TILEDATA_HPP_

#include <ostream>

/**
 * @brief A TileData holds the meta image's UID position for a single tile.
 */
struct TileData
{
	/**
	 * @brief Default constructor.
	 */
	TileData();

	/**
	 * @brief Set all the values in one go.
	 * @param _1 l
	 * @param _m m
	 * @param _u1 u1
	 * @param _u2 u2
	 * @param _u3 u3
	 */
	void set(unsigned int _l, unsigned int _m, unsigned int _u1, unsigned int _u2, unsigned int _u3);

	/**
	 * The UIDs for a single tile.
	 * l  = lower UID
	 * m  = middle UID
	 * u1 = lower-upper UID
	 * u2 = middle-upper UID
	 * u3 = top-most UID
	 */
	unsigned int l, m, u1, u2, u3;
};

/**
 * @brief Output the tile data to an ostream.
 * @param os The output stream.
 * @param data The tile data.
 * @return The updated output stream.
 */
std::ostream& operator<<(std::ostream& os, const TileData& data);

#endif /* TILEDATA_HPP_ */
