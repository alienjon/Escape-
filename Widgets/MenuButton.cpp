/*
 * MenuButton.cpp
 *
 *  Created on: Jul 1, 2009
 *      Author: alienjon
 */
#include "MenuButton.hpp"

#include "../Managers/AudioManager.hpp"
#include "../Managers/FontManager.hpp"
#include "../Managers/VideoManager.hpp"

using std::list;
using std::string;

MenuButton::MenuButton(const string& name) : gcn::Label(name)
{
    // Add this as a mouse, key and focus listener.
    addKeyListener(this);
    addMouseListener(this);
    addFocusListener(this);

    mInactiveFont = FontManager::get(FONT_MENU_INACTIVE);
    mHoverFont    = FontManager::get(FONT_MENU_HOVER);
    mPressedFont  = FontManager::get(FONT_MENU_PRESSED);

    // Set the initial font.
    setFont(mInactiveFont);
    adjustSize();
}

MenuButton::~MenuButton()
{
    // Remove this as listeners.
    removeKeyListener(this);
    removeMouseListener(this);
    removeFocusListener(this);
}

void MenuButton::draw(gcn::Graphics* graphics)
{
    // Draw the button first.
    gcn::Label::draw(graphics);

    // If this button is focused, then also draw a border around the label.
    if(isFocused())
    {
        graphics->setColor(gcn::Color(0, 0, 0));
        graphics->drawRectangle(gcn::Rectangle(0, 0, getWidth(), getHeight()));
    }
}

void MenuButton::focusGained(gcn::Event& event)
{
    setHover();
}

void MenuButton::focusLost(gcn::Event& event)
{
    setInactive();
}

void MenuButton::mouseEntered(gcn::MouseEvent& mouseEvent)
{
    setHover();
}

void MenuButton::mouseExited(gcn::MouseEvent& mouseEvent)
{
    setInactive();
}

void MenuButton::mousePressed(gcn::MouseEvent& mouseEvent)
{
    if(mouseEvent.getButton() == gcn::MouseInput::LEFT)
        setPressed();
}

void MenuButton::mouseReleased(gcn::MouseEvent& mouseEvent)
{
    if(mouseEvent.getButton() != gcn::MouseInput::LEFT)
        return;

    setInactive();
    distributeActionEvent();
}

void MenuButton::keyPressed(gcn::KeyEvent& keyEvent)
{
    if(keyEvent.getKey().getValue() == gcn::Key::SPACE)
        setPressed();
}

void MenuButton::keyReleased(gcn::KeyEvent& keyEvent)
{
    if(keyEvent.getKey().getValue() == gcn::Key::SPACE)
    {
        setHover();
        distributeActionEvent();
    }
}

void MenuButton::setHover()
{
    setFont(mHoverFont);
    adjustSize();
}

void MenuButton::setInactive()
{
    setFont(mInactiveFont);
    adjustSize();
}

void MenuButton::setPressed()
{
    AudioManager::playSound("MenuButton.ogg");//@todo have this as a constant?
    setFont(mPressedFont);
    adjustSize();
}
