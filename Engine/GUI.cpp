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
	mRoot.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	mRoot.setOpaque(false);
	mRoot.setFocusable(true);
	setTop(&mRoot);
	mFocusHandler->requestFocus(&mRoot);

	// Add the FPS display widget to the GUI.
	mRoot.add(&mFPSDisplayWidget, 0, 0);

    // Set the global font.
	gcn::SFMLFont* font = FontManager::getGCNFont(FONT_DEFAULT);
	font->SetStyle(sf::Text::Italic | sf::Text::Bold);
	font->SetColor(sf::Color::Magenta);
    gcn::Widget::setGlobalFont(font);
    mGraphics->setFont(font);
}

void GUI::setBase(gcn::Container* container)
{
	// Set the new container, but make sure that the FPS widget is on top.
    mRoot.add(container);
    mFPSDisplayWidget.requestMoveToTop();
}

void GUI::toggleFPS()
{
    mFPSDisplayWidget.setVisible(!mFPSDisplayWidget.isVisible());
}
