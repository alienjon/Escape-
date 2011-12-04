/*
 * sfmlgraphics.cpp
 *
 *  Created on: Nov 5, 2011
 *      Author: alienjon
 */
#include "sfmlgraphics.hpp"

#include <GL/gl.h>

#include "../exception.hpp"
#include "sfmlimage.hpp"

namespace gcn
{
	SFMLGraphics::SFMLGraphics()
	{
	}

	SFMLGraphics::~SFMLGraphics()
	{
	}

	void SFMLGraphics::_beginDraw()
	{
		pushClipArea(Rectangle(0, 0, GetWidth(), GetHeight()));
	}

	void SFMLGraphics::_endDraw()
	{
		popClipArea();
	}

	void SFMLGraphics::startDraw()
	{
		if(mClipStack.empty())
			return;
		const ClipRectangle& top = mClipStack.top();
		glEnable(GL_SCISSOR_TEST);
		glScissor(top.x - 1, GetHeight() - (top.y + top.height), top.x + top.width, top.y + top.height);
	}

	void SFMLGraphics::stopDraw()
	{
		glDisable(GL_SCISSOR_TEST);
	}

	void SFMLGraphics::drawImage(const Image *image, int srcX, int srcY, int dstX, int dstY, int width, int height)
	{
		// If clip stack is empty, don't draw.
		if(mClipStack.empty())
			throw GCN_EXCEPTION("Clip stack is empty.  drawImage() was probably called outside of _beginDraw() and _endDraw()");

		// Convert to an SFImage.
		const SFMLImage* sfImage = dynamic_cast<const SFMLImage*>(image);
		if(!sfImage)
			throw GCN_EXCEPTION("Providing a non-SFImage to SFMLGraphics");

		const ClipRectangle& top = getCurrentClipArea();
		sf::Sprite sprite(*sfImage);
		sprite.SetPosition(dstX + top.xOffset, dstY + top.yOffset);
		sprite.SetSubRect(sf::IntRect(srcX, srcY, srcX + width, srcY + height));
		startDraw();
		Draw(sprite);
		stopDraw();
	}

	void SFMLGraphics::drawLine(int x1, int y1, int x2, int y2)
	{
		if(mClipStack.empty())
			throw GCN_EXCEPTION("Clip stack is empty.  drawImage() was probably called outside of _beginDraw() and _endDraw()");

		const ClipRectangle& c_area = mClipStack.top();
		x1 += c_area.xOffset;
		x2 += c_area.xOffset;
		y1 += c_area.yOffset;
		y2 += c_area.yOffset;
		if(!c_area.isPointInRect(x1, y1) && !c_area.isPointInRect(x2, y2))
			return;

		Color c = getColor();
		startDraw();
		Draw(sf::Shape::Line(x1, y1, x2, y2, 1, sf::Color(c.r, c.g, c.b, c.a)));
		stopDraw();
	}

	void SFMLGraphics::drawPoint(int x, int y)
	{
		if(mClipStack.empty())
			throw GCN_EXCEPTION("Clip stack is empty.  drawImage() was probably called outside of _beginDraw() and _endDraw()");

		const ClipRectangle& c_area = mClipStack.top();
		x += c_area.xOffset;
		y += c_area.yOffset;
		if(!c_area.isPointInRect(x, y))
			return;

		sf::Shape area;
		area.AddPoint(x, y, sf::Color(mColor.r, mColor.g, mColor.b, mColor.a));
		startDraw();
		Draw(area);
		stopDraw();
	}

	void SFMLGraphics::drawRectangle(const Rectangle& rectangle)
	{
		if(mClipStack.empty())
			throw GCN_EXCEPTION("Clip stack is empty.  drawImage() was probably called outside of _beginDraw() and _endDraw()");

		const ClipRectangle& c_area = mClipStack.top();
		Rectangle area = rectangle;
		area.x += c_area.xOffset;
		area.y += c_area.yOffset;

		if(!area.isIntersecting(c_area))
			return;

		Color c = getColor();
		sf::Shape rect = sf::Shape::Rectangle(area.x, area.y, area.width, area.height, sf::Color(c.r, c.g, c.b, c.a), 1.f, sf::Color(c.r, c.g, c.b, c.a));
		rect.EnableFill(false);
		startDraw();
		Draw(rect);
		stopDraw();
	}

	void SFMLGraphics::fillRectangle(const Rectangle& rectangle)
	{
		if(mClipStack.empty())
			throw GCN_EXCEPTION("Clip stack is empty.  drawImage() was probably called outside of _beginDraw() and _endDraw()");

		const ClipRectangle& c_area = mClipStack.top();
		Rectangle area = rectangle;
		area.x += c_area.xOffset;
		area.y += c_area.yOffset;

		if(!area.isIntersecting(c_area))
			return;

		Color c = getColor();
		startDraw();
		Draw(sf::Shape::Rectangle(area.x, area.y, area.width, area.height, sf::Color(c.r, c.g, c.b, c.a)));
		stopDraw();
	}

	const Color& SFMLGraphics::getColor() const
	{
		return mColor;
	}

	void SFMLGraphics::setColor(const Color& color)
	{
		mColor = color;
	}
}
