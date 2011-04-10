/*
 * Direction.hpp
 *
 *  Created on: Jun 22, 2009
 *      Author: alienjon
 */
#ifndef DIRECTION_HPP_
#define DIRECTION_HPP_

#include <string>

#include "../Math/Vector.hpp"

/**
 * @brief The various directions.
 */
enum Direction
{
    DIR_UP        = 0,
    DIR_UPRIGHT   = 1,
    DIR_RIGHT     = 2,
    DIR_DOWNRIGHT = 3,
    DIR_DOWN      = 4,
    DIR_DOWNLEFT  = 5,
    DIR_LEFT      = 6,
    DIR_UPLEFT    = 7,
    DIR_NONE      = 8
};

/**
 * @brief Return the direction from the first point to the second.
 * @param pA The first (base) point.
 * @param pB the second point (destination).
 * @return The direction something at the first point would have to be facing to look at the second point.
 */
Direction directionToPoint(const Vector& pA, const Vector& pB);

/**
 * @brief Determine the character representation of the direction.
 * @param dir The direction.
 * @return The direction in string format.
 */
std::string getDirection(Direction dir);

/**
 * @brief Determine the direction based on the cardinal number.
 * @param n The int value of the cardinal direction (with 0 being north and 7 being north-west)
 * @return The direction.
 */
Direction getDirection(int n);

/**
 * @brief Get the point in the provided direction at the provided distance.
 * @param pos The current position.
 * @param dir The facing direction.
 * @param dis The distance.
 */
Vector getPointInDirection(const Vector& pos, Direction dir, unsigned int dis);

/**
 * @brief Return the opposite direction of the provided direction.
 * @param facing The facing direction.
 * @return The opposite direction of the facing direction.
 */
Direction oppositeDirection(Direction facing);

#endif /* DIRECTION_HPP_ */
