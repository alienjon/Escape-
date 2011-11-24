/*
 * sfmlfont.hpp
 *
 *  Created on: Nov 6, 2011
 *      Author: alienjon
 */
#ifndef SFMLFONT_HPP_
#define SFMLFONT_HPP_

#include <SFML/Graphics.hpp>
#include <string>

#include "../font.hpp"
#include "../graphics.hpp"

namespace gcn
{
	/*
	 * @brief A font specific to the SFML library.
	 */
	class SFMLFont : public Font, public sf::Text
	{
		public:
		/**
		 * @brief Default constructor that uses SFML's default font (arial).
		 * @param font The font to use to display.
		 */
		SFMLFont();

		/**
		 * @brief Construct a font and load the font by filename and size.
		 * @param filename The filename of the font.
		 */
		SFMLFont(const std::string& filename);

		/**
		 * @brief Covering the rule of 3.
		 */
		SFMLFont(const SFMLFont& font);
		virtual ~SFMLFont();
		SFMLFont& operator=(const SFMLFont& font);

		/**
		 * @brief Draws a string.
		 * @param graphics A Graphics object to use for drawing.
		 * @param text The string to draw.
		 * @param x The x coordinate where to draw the string.
		 * @param y The y coordinate where to draw the string.
		 */
		virtual void drawString(Graphics* graphics, const std::string& text, int x, int y);

		/**
		 * @brief Gets the height of the glyphs in the font.
		 * @return The height of the glyphs in the font.
		 */
		virtual int getHeight() const;

	   /**
		* @brief Gets the width of a string.
		* @param text The string to return the width of.
		* @return The width of a string.
		*/
		virtual int getWidth(const std::string& text) const;

		/**
		 * @brief Set the color to display the text.
		 * @param color The color to set.
		 */
		virtual void setColor(const gcn::Color& color);

		/**
		 * @brief Set the color to display the text.
		 * @param color The color to set.
		 */
		virtual void setColor(const sf::Color& color);

		private:
		// The font.
		sf::Font mFont;
	};
}
#endif /* SFMLFONT_HPP_ */
