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
		if(!LoadFromFile(filename))
			throw GCN_EXCEPTION("Cannot load file with filename: " + filename);
	}

	int SFMLImage::getHeight() const
	{
		return GetHeight();
	}

	Color SFMLImage::getPixel(int x, int y)
	{
		sf::Image img = CopyToImage();
		sf::Color color = img.GetPixel(x, y);
		return Color(color.r, color.g, color.b, color.a);
	}

	int SFMLImage::getWidth() const
	{
		return GetWidth();
	}

	void SFMLImage::putPixel(int x, int y, const Color& color)
	{
		sf::Image img = CopyToImage();
		img.SetPixel(x, y, sf::Color(color.r, color.g, color.b, color.a));
	}
}
