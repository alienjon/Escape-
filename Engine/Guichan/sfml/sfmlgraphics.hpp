/*
 * sfmlgraphics.hpp
 *
 *  Created on: Nov 5, 2011
 *      Author: alienjon
 */
#ifndef SFMLGRAPHICS_HPP_
#define SFMLGRAPHICS_HPP_

#include <SFML/Graphics.hpp>

#include "../color.hpp"
#include "../graphics.hpp"
#include "../rectangle.hpp"

namespace gcn
{
	/*
	 * @brief A union between gcn::Graphics and sf::RenderWindow.
	 */
	class SFMLGraphics : public Graphics, public sf::RenderWindow
	{
		public:
		/**
		 * @brief Default constructor.
		 */
		SFMLGraphics();
		virtual ~SFMLGraphics();

		/**
		 * @brief Called before drawing the frame starts.
		 */
		virtual void _beginDraw();

		/**
		 * @brief Called when drawing is complete for this frame.
		 */
		virtual void _endDraw();

		/**
		 * @brief Start SFML drawing.
		 */
		virtual void startDraw();

		/**
		 * @brief Stop SFML drawing.
		 */
		virtual void stopDraw();

		/**
		 * @brief Draw an image.
		 * @param image The image to draw.
		 * @param srcX The x location from which to draw the image.
		 * @param srcY The y location from which to draw the image.
		 * @param dstX The x location to draw the image to.
		 * @param dstY The y location to draw the image to.
		 * @param width The width of the area of the image to draw.
		 * @param height The height of the area of the image to draw.
		 */
		virtual void drawImage(const Image *image, int srcX, int srcY, int dstX, int dstY, int width, int height);

		/**
		 * @brief Draw a line.
		 * @param x1 The x coordinate of the first point in the line.
		 * @param y1 The y coordinate of the first point in the line.
		 * @param x2 The x coordinate of the second point in the line.
		 * @param y2 The y coordinate of the second point in the line.
		 */
		virtual void drawLine(int x1, int y1, int x2, int y2);

		/**
		 * @brief Draw a single pixel.
		 * @param x The x coordinate of the pixel.
		 * @param y The y coordinate of the pixel.
		 */
		virtual void drawPoint(int x, int y);

		/**
		 * @brief Draw a rectangle outline (not filled).
		 * @param rectangle The area to draw.
		 */
		virtual void drawRectangle(const Rectangle& rectangle);

		/**
		 * @brief Draw a filled rectangle.
		 * @param rectangle The area to draw.
		 */
		virtual void fillRectangle(const Rectangle& rectangle);

		/**
		 * @brief Get the current drawing color.
		 * @return The color used to draw objects.
		 */
		virtual const Color& getColor() const;

		/**
		 * @brief Set the drawing color.
		 * @param color The color to use to draw objects.
		 */
		virtual void setColor(const Color& color);

		private:
		// The current drawing color.
		Color mColor;
	};
}

#endif /* RENDERER_HPP_ */
