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
#include "../Widgets/MenuButton.hpp"

/**
 * @brief A widget to display the in-game options menu.
 */
class GameOptionsWidget : public gcn::ActionListener, public gcn::Container
{
    public:
    /**
     * @brief The game options widget shows in-game options for the player.
     */
    GameOptionsWidget();

    /**
     * @brief An action occurred.
     * @param actionEvent The action event.
     */
    virtual void action(const gcn::ActionEvent& actionEvent);

    private:
    // Buttons.@todo Make these buttons look cooler
    MenuButton mResumeButton, mOptionsButton, mCreditsButton, mMainMenuButton, mExitButton;
};

extern const std::string GAMEOPTIONS_RESUME;
extern const std::string GAMEOPTIONS_MAINMENU;
extern const std::string GAMEOPTIONS_EXIT;

#endif /* GAMEOPTIONSWIDGET_HPP_ */
