///*
// * MenuButton.cpp
// *
// *  Created on: Jul 1, 2009
// *      Author: alienjon
// */
//#include "MenuButton.hpp"
//
//#include "../Engine/AudioManager.hpp"
//#include "../Engine/Colors.hpp"
//#include "../Engine/FontManager.hpp"
//#include "../Game/Keywords.hpp"
//
//using std::string;
//
//MenuButton::MenuButton(const string& name) : gcn::Label(name),
//	mInactiveFont(FontManager::getGCNFont(FONT_DEFAULT)),
//	mHoverFont(FontManager::getGCNFont(FONT_DEFAULT)),
//	mPressedFont(FontManager::getGCNFont(FONT_DEFAULT))
//{
//    // Add this as a mouse, key and focus listener.
//    addKeyListener(this);
//    addMouseListener(this);
//    addFocusListener(this);
//
////@todo review colors/how the button is displayed
//    mInactiveFont->setColor(sf::Color(100, 0, 0));
//    mHoverFont->setColor(sf::Color(255, 0, 0));
//    mPressedFont->setColor(sf::Color(175, 0, 0));
//
//    // Set the initial font.
//    setFont(mInactiveFont);
//    adjustSize();
//}
//
//MenuButton::~MenuButton()
//{
//    // Remove this as listeners.
//    removeKeyListener(this);
//    removeMouseListener(this);
//    removeFocusListener(this);
//}
//
//void MenuButton::draw(gcn::Graphics* graphics)
//{
//    // Draw the button first.
//    gcn::Label::draw(graphics);
//}
//
//void MenuButton::focusGained(gcn::Event& event)
//{
//    setHover();
//}
//
//void MenuButton::focusLost(gcn::Event& event)
//{
//    setInactive();
//}
//
//void MenuButton::mouseEntered(gcn::MouseEvent& mouseEvent)
//{
//    setHover();
//}
//
//void MenuButton::mouseExited(gcn::MouseEvent& mouseEvent)
//{
//    setInactive();
//}
//
//void MenuButton::mousePressed(gcn::MouseEvent& mouseEvent)
//{
//    if(mouseEvent.getButton() == gcn::MouseInput::LEFT)
//        setPressed();
//}
//
//void MenuButton::mouseReleased(gcn::MouseEvent& mouseEvent)
//{
//    if(mouseEvent.getButton() != gcn::MouseInput::LEFT)
//        return;
//
//    setInactive();
//    distributeActionEvent();
//}
//
//void MenuButton::keyPressed(gcn::KeyEvent& keyEvent)
//{
//    if(keyEvent.getKey().getValue() == gcn::Key::SPACE)
//        setPressed();
//}
//
//void MenuButton::keyReleased(gcn::KeyEvent& keyEvent)
//{
//    if(keyEvent.getKey().getValue() == gcn::Key::SPACE)
//    {
//        setHover();
//        distributeActionEvent();
//    }
//}
//
//void MenuButton::setHover()
//{
//    setFont(mHoverFont);
//    adjustSize();
//}
//
//void MenuButton::setInactive()
//{
//    setFont(mInactiveFont);
//    adjustSize();
//}
//
//void MenuButton::setPressed()
//{
//    AudioManager::playSound(SOUND_MENU_CLICK);
//    setFont(mPressedFont);
//    adjustSize();
//}
