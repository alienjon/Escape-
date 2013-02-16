/***************************************************************************
 *   Copyright (C) 2007 by Jonathan Rosen   *
 *   holy.smoking.floorboards.batman@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "GUI.hpp"

#include "../Engine/Guichan/sfml.hpp"

#include "../Engine/FontManager.hpp"
#include "../Game/Keywords.hpp"
#include "../main.hpp"

GUI::GUI(gcn::SFMLGraphics& graphics, gcn::SFMLInput& input)
{
	// Set the graphics handler.
	setGraphics(&graphics);

	// Instantiate the input handle.
	setInput(&input);

	// Configure the root widget.
	setSize(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
	mRoot.setOpaque(false);
	mRoot.setFocusable(true);
	setTop(&mRoot);
	mFocusHandler->requestFocus(&mRoot);

    // Set the global font.
	gcn::SFMLFont* font = FontManager::getGCNFont(FONT_DEFAULT);
	font->setStyle(sf::Text::Italic | sf::Text::Bold);
	font->setColor(sf::Color::Magenta);
    gcn::Widget::setGlobalFont(font);
    mGraphics->setFont(font);
}

void GUI::setBase(gcn::Container* container)//@fixme Can I do this without this method?
{
	// Add and configure the new container.
    mRoot.add(container);
    container->setSize(mRoot.getWidth(), mRoot.getHeight());
}

void GUI::setSize(unsigned int width, unsigned int height)
{
	mRoot.setSize(width, height);
}
