/*
 * SFMLFont.cpp
 *
 *  Created on: Nov 6, 2011
 *      Author: alienjon
 */
#include "sfmlfont.hpp"

#include "../exception.hpp"
#include "sfmlgraphics.hpp"

using std::string;

namespace gcn
{
	SFMLFont::SFMLFont()
	{
	}

	SFMLFont::SFMLFont(const string& filename)
	{
		if(!mFont.LoadFromFile(filename))
			throw GCN_EXCEPTION("Error loading font: " + filename);
		SetFont(mFont);
	}

	SFMLFont::SFMLFont(const SFMLFont& font) : mFont(font.GetFont())
	{
		if(this != &font)
			SetFont(mFont);
	}

	SFMLFont::~SFMLFont()
	{} // Memory management handled by SFML.

	SFMLFont& SFMLFont::operator=(const SFMLFont& font)
	{
		if(this == &font)
			return *this;

		mFont = font.GetFont();
		SetFont(mFont);
		return *this;
	}

	void SFMLFont::drawString(Graphics* graphics, const std::string& text, int x, int y)
	{
		SFMLGraphics* sfmlGraphics = dynamic_cast<SFMLGraphics*>(graphics);
		if(!sfmlGraphics)
			throw GCN_EXCEPTION("Trying to draw a sf:String to a non-SFMLGraphics.");

		const ClipRectangle& top = graphics->getCurrentClipArea();
		SetString(text);
		SetPosition(x + top.xOffset, y + top.y);
		sfmlGraphics->startDraw();
		sfmlGraphics->Draw(*this);
		sfmlGraphics->stopDraw();
	}

	int SFMLFont::getHeight() const
	{
		return GetCharacterSize();
	}

	int SFMLFont::getWidth(const string& text) const
	{
		sf::Text str(text, GetFont(), GetCharacterSize());
		return str.GetRect().Width;
	}

	void SFMLFont::setColor(const gcn::Color& color)
	{
		SetColor(sf::Color(color.r, color.g, color.b, color.a));
	}

	void SFMLFont::setColor(const sf::Color& color)
	{
		SetColor(color);
	}
}
