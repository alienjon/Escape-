/*
 * FontManager.cpp
 *
 *  Created on: Jul 8, 2009
 *      Author: alienjon
 */

#include "FontManager.hpp"

#include <stdexcept>

#include "../main.hpp"
#include "../Engine/Surface.hpp"

using std::runtime_error;

const char* FONTCHAR_DEFAULT = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?-+/():;%&`'*#=[]\"";
const char* FONTCHAR_CUSTOM  = " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-=!@#$%^&*()_+[]\\{}|;':\",./<>?`~";

const char* FILE_FONT_DEFAULT = "Fonts/defaultfont.png";
const char* FILE_FONT_MENU_INACTIVE = "Fonts/font_menu_inactive.png";
const char* FILE_FONT_MENU_HOVER = "Fonts/font_menu_hover.png";
const char* FILE_FONT_MENU_PRESSED = "Fonts/font_menu_pressed.png";
const char* FILE_FONT_OSD_MESSAGE = "Fonts/font_menu_osd.png";
const char* FILE_FONT_CAPTION = "Fonts/caption.png";
const char* FILE_FONT_TEXT = "Fonts/message.png";

FontManager::FontManager() : mDefaultFont(new Surface(loadSurface(FILE_FONT_DEFAULT)), FONTCHAR_DEFAULT),
                             mMenuInactiveFont(new Surface(loadSurface(FILE_FONT_MENU_INACTIVE)), FONTCHAR_CUSTOM),
                             mMenuHoverFont(new Surface(loadSurface(FILE_FONT_MENU_HOVER)), FONTCHAR_CUSTOM),
                             mMenuPressedFont(new Surface(loadSurface(FILE_FONT_MENU_PRESSED)), FONTCHAR_CUSTOM),
                             mOSDMessageFont(new Surface(loadSurface(FILE_FONT_OSD_MESSAGE)), FONTCHAR_CUSTOM),
                             mCaption(new Surface(loadSurface(FILE_FONT_CAPTION)), FONTCHAR_CUSTOM),
                             mText(new Surface(loadSurface(FILE_FONT_TEXT)), FONTCHAR_DEFAULT)
{
}

void FontManager::create()
{
    if(!mFontManager)
    {
        mFontManager = new FontManager();
    }
}

gcn::Font* FontManager::get(FontType type)
{
    if(!mFontManager)
    {
        throw runtime_error("FontManager::get() -> Trying to get a font, but the manager has not yet been created.");
    }
    switch(type)
    {
        case FONT_DEFAULT:
        {
            return &mFontManager->mDefaultFont;
        }
        case FONT_MENU_INACTIVE:
        {
            return &mFontManager->mMenuInactiveFont;
        }
        case FONT_MENU_HOVER:
        {
            return &mFontManager->mMenuHoverFont;
        }
        case FONT_MENU_PRESSED:
        {
            return &mFontManager->mMenuPressedFont;
        }
        case FONT_OSD_MESSAGE:
        {
            return &mFontManager->mOSDMessageFont;
        }
        case FONT_CAPTION:
        {
        	return &mFontManager->mCaption;
        }
        case FONT_TEXT:
        {
        	return &mFontManager->mText;
        }
        default:
        {
            throw runtime_error("FontManager::get() -> Requesting invalid font.");
        }
    }
}

void FontManager::terminate()
{
    delete mFontManager;
    mFontManager = 0;
}

FontManager* FontManager::mFontManager = 0;
