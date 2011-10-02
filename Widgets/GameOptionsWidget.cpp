/*
 * GameOptionsWidget.cpp
 *
 *  Created on: Aug 7, 2009
 *      Author: alienjon
 */

#include "GameOptionsWidget.hpp"

#include "../Engine/Colors.hpp"
#include "../Managers/FontManager.hpp"
#include "../Engine/Logger.hpp"

using std::string;

GameOptionsWidget::GameOptionsWidget() : gcn::Window("GAME OPTIONS")
{
    // Configure this widget.
    setBaseColor(COLOR_MENU_DARK);
    setBackgroundColor(COLOR_MENU_LIGHT);
    setFrameSize(2);
    setFont(FontManager::get(FONT_DEFAULT));
    setMovable(false);
}
