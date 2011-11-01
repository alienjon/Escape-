/*
 * CreditsMenu.hpp
 *
 *  Created on: Jul 1, 2009
 *      Author: alienjon
 */
#ifndef CREDITSMENU_HPP_
#define CREDITSMENU_HPP_

#include "../../guichan.hpp"
#include "../../Widgets/MenuButton.hpp"
#include "MenuWidget.hpp"

class MenuScreen;

/**
 * @brief A main menu widget to show game credits.
 */
class CreditsMenu : public MenuWidget
{
    // The menu screen should be the only non-derived class to be able to create a menu.
    friend class MenuScreen;

    public:
    virtual ~CreditsMenu();

    protected:
    /**
     * @brief Display the list of credits.
     */
    CreditsMenu();

    private:
    /**
     * @brief The credits.
     */
    gcn::TextBox mText;

    /**
     * A scroll box for the credits.
     */
    gcn::ScrollArea mScrollArea;

    /**
     * @brief A button to go back to the main menu.
     */
    MenuButton mBackButton;
};

#endif /* CREDITSMENU_HPP_ */
