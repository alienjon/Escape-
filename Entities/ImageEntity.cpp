/*
 * ImageEntity.cpp
 *
 *  Created on: Nov 27, 2011
 *      Author: alienjon
 */
#include "ImageEntity.hpp"

void ImageEntity::adjustSize()
{
	mShape = sf::Shape::Rectangle(0-int(getWidth() / 2), 0-int(getHeight() / 2), getWidth(), getHeight(), sf::Color::Magenta);
}
