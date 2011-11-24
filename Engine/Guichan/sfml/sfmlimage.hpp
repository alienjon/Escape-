/*
 * sfmlimage.hpp
 *
 *  Created on: Nov 3, 2011
 *      Author: alienjon
 */
#ifndef SFMLIMAGE_HPP_
#define SFMLIMAGE_HPP_

#include <SFML/Graphics.hpp>
#include <string>

#include "../color.hpp"
#include "../image.hpp"

namespace gcn
{
	/*
	 * @brief An implementation of gcn::Image to work with Guichan.
	 */
	class SFMLImage : public Image, public sf::Texture
	{
		public:
		/**
		 * @brief Default constructor.
		 * @param filename The filename of the image.
		 */
		SFMLImage(const std::string& filename);

		/**
		 * @brief Convert the image to display format.
		 * @note Not used with SFML.
		 */
		virtual void convertToDisplayFormat()
		{}

		/**
		 * @brief Free the image.
		 * @note Not used with SFML.
		 */
		virtual void free()
		{}

		/**
		 * @brief Get the height of the image.
		 * @return The height.
		 */
		virtual int getHeight() const;

		/**
		 * @brief Get the color at the requested position.
		 * @param x The x position of the color to get.
		 * @param y The y position of the color to get.
		 * @return The color at the position.
		 */
		virtual Color getPixel(int x, int y);

		/**
		 * @brief Get the width of the image.
		 * @return The width.
		 */
		virtual int getWidth() const;

		/**
		 * @brief Place a pixel at the specified color.
		 * @param x The x location to put the color.
		 * @param y The y location to put the color.
		 * @param color The color to put at the requested pixel.
		 */
		virtual void putPixel(int x, int y, const Color& color);
	};
}

#endif /* GCNIMAGE_HPP_ */
