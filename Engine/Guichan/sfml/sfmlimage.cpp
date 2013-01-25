/*
 * sfmlimage.cpp
 *
 *  Created on: Nov 3, 2011
 *      Author: alienjon
 */
#include "sfmlimage.hpp"

#include "../exception.hpp"

using std::string;

namespace gcn
{
	SFMLImage::SFMLImage(const string& filename)
	{
		if(!loadFromFile(filename))
			throw GCN_EXCEPTION("Cannot load file with filename: " + filename);
	}

	int SFMLImage::getHeight() const
	{
		return getSize().y;
	}

	Color SFMLImage::getPixel(int x, int y)
	{
		sf::Image img = copyToImage();
		sf::Color color = img.getPixel(x, y);
		return Color(color.r, color.g, color.b, color.a);
	}

	int SFMLImage::getWidth() const
	{
		return getSize().x;
	}

	void SFMLImage::putPixel(int x, int y, const Color& color)
	{
		sf::Image img = copyToImage();
		img.setPixel(x, y, sf::Color(color.r, color.g, color.b, color.a));
	}
}
