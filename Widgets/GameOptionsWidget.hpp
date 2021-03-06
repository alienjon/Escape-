///*
// * GameOptionsWidget.hpp
// *
// *  Created on: Aug 7, 2009
// *      Author: alienjon
// */
//#ifndef GAMEOPTIONSWIDGET_HPP_
//#define GAMEOPTIONSWIDGET_HPP_
//
//#include <string>
//
//#include "../Engine/guichan.hpp"
//#include "../Widgets/MenuButton.hpp"
//
///**
// * @brief A widget to display the in-game options menu.
// */
//class GameOptionsWidget : public gcn::ActionListener, public gcn::Container, public gcn::KeyListener
//{
//    public:
//    /**
//     * @brief The game options widget shows in-game options for the player.
//     */
//    GameOptionsWidget();
//
//    /**
//     * @brief An action occurred.
//     * @param actionEvent The action event.
//     */
//    virtual void action(const gcn::ActionEvent& actionEvent);
//
//    /**
//     * @brief Adjust the positions of the internal widgets.
//     */
//    void adjustInternals();
//
//    /**
//     * @brief A key was pressed.
//     * @param event The key event.
//     */
//    virtual void keyPressed(gcn::KeyEvent& event);
//
//    private:
//    // Buttons.
//    MenuButton mResumeButton, mOptionsButton, mCreditsButton, mMainMenuButton, mExitButton;
//};
//
//extern const std::string GAMEOPTIONS_RESUME;
//extern const std::string GAMEOPTIONS_MAINMENU;
//extern const std::string GAMEOPTIONS_EXIT;
//
//#endif /* GAMEOPTIONSWIDGET_HPP_ */
