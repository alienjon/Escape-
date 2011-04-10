/*
 * OptionsMenu.hpp
 *
 *  Created on: Jul 1, 2009
 *      Author: alienjon
 */

#ifndef OPTIONSMENU_HPP_
#define OPTIONSMENU_HPP_

#include <string>

#include "../../Listeners/CreatureMovedToPointListener.hpp"
#include "../../Game/Event.hpp"
#include "../../guichan.hpp"
#include "../../Widgets/MenuButton.hpp"
#include "MenuWidget.hpp"

class MenuScreen;

/**
 * @brief This menu allows the player to change various game options in the main menu.
 */
class OptionsMenu : public MenuWidget
{
    // Only menu screens and derived classes should be able to create options menus.
    friend class MenuScreen;

    public:
    virtual ~OptionsMenu();

    protected:
    /**
     * @brief Allow the user to change certain options.
     */
    OptionsMenu();

    /**
     * @brief An event occurred.
     * @param event The event that occurred.
     * @param content Additional content.
     * @param creatureMovedToPointListener A potential creature moved to point listener.
     */
    virtual void eventOccurred(Event event, const std::string& content = "", CreatureMovedToPointListener* creaturedMovedToPointListener = 0);

    private:
    /**
     * A container to display all options.
     */
    gcn::Container mContainer;

    /**
     * The back button.
     */
    MenuButton mBackButton;
};

#endif /* OPTIONSMENU_HPP_ */
