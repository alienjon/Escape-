///*
// * MenuWidget.hpp
// *
// *  Created on: Jul 1, 2009
// *      Author: alienjon
// */
//#ifndef MENUWIDGET_HPP_
//#define MENUWIDGET_HPP_
//
//#include <list>
//
//#include "../../Engine/Colors.hpp"
//#include "../../guichan.hpp"
//#include "../../Managers/VideoManager.hpp"
//
///**
// * @brief A base class for a main menu widget.
// */
//class MenuWidget : public gcn::ActionListener, public gcn::Container
//{
//    public:
//    virtual ~MenuWidget()
//    {}
//
//    /**
//     * @brief An action occurred.
//     * @param event The event that occurred.
//     */
//    virtual void action(const gcn::ActionEvent& event)
//    {
//    	setActionEventId(event.getId());
//    	distributeActionEvent();
//    }
//
//    protected:
//    /**
//     * @brief Defines properties common to all menu widgets.
//     */
//    MenuWidget()
//    {
//        // All menu's have the same base color.
//        setBaseColor(COLOR_MENU_DARK);
//
//        // Set the size to the size of one screen.
//        setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
//
//        // Set other basic attributes.
//        setOpaque(false);
//    }
//};
//
//#endif /* MENUWIDGET_HPP_ */
