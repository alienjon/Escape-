/*
 * FontManager.hpp
 *
 *  Created on: Jul 8, 2009
 *      Author: alienjon
 */

#ifndef FONTMANAGER_HPP_
#define FONTMANAGER_HPP_

#include "../guichan.hpp"

enum FontType
{
    FONT_NULL,
    FONT_DEFAULT,
    FONT_MENU_INACTIVE,
    FONT_MENU_HOVER,
    FONT_MENU_PRESSED,
    FONT_OSD_MESSAGE,
    FONT_CAPTION,
    FONT_TEXT
};

/**
 * @brief A class that manages fonts.
 */
class FontManager
{
    public:
    /**
     * @brief Create the font manager.
     */
    static void create();

    /**
     * @brief Retrieve the requested font.
     * @param type The font type to return.
     */
    static gcn::Font* get(FontType type);

    /**
     * @brief Delete the font manager.
     */
    static void terminate();

    private:
    /**
     * The font manager.
     */
    static FontManager* mFontManager;

    /**
     * @brief Manages all fonts.
     */
    FontManager();

    /**
     * The fonts.
     */
    gcn::ImageFont mDefaultFont;
    gcn::ImageFont mMenuInactiveFont;
    gcn::ImageFont mMenuHoverFont;
    gcn::ImageFont mMenuPressedFont;
    gcn::ImageFont mOSDMessageFont;
    gcn::ImageFont mCaption;
    gcn::ImageFont mText;
};

#endif /* FONTMANAGER_HPP_ */
