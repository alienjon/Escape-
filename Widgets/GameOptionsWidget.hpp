/*
 * GameOptionsWidget.hpp
 *
 *  Created on: Aug 7, 2009
 *      Author: alienjon
 */
#ifndef GAMEOPTIONSWIDGET_HPP_
#define GAMEOPTIONSWIDGET_HPP_

#include <string>

#include "../guichan.hpp"

/**
 * @brief A widget to display the in-game options menu.
 */
class GameOptionsWidget : public gcn::SelectionListener, public gcn::Window
{
    public:
    /**
     * @brief The game options widget shows in-game options for the player.
     */
    GameOptionsWidget();
};

#endif /* GAMEOPTIONSWIDGET_HPP_ */
