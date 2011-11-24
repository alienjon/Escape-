/*
 * FontManager.hpp
 *
 *  Created on: Jul 8, 2009
 *      Author: alienjon
 */
#ifndef FONTMANAGER_HPP_
#define FONTMANAGER_HPP_

#include <list>
#include <map>
#include <string>

#include "../Engine/Guichan/sfml.hpp"

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
     * @brief Get a requested font.
     * @param filename The filename of the font to get.
     * @return A new gcn::SFMLFont*
     */
    static gcn::SFMLFont* getGCNFont(const std::string& filename);

    /**
     * @brief Get a requested sf::Font.
     * @param filename The filename of the font to get.
     * @return The sf::Font of the requested type.
     */
    static const sf::Font& getSFFont(const std::string& filename);

    /**
     * @brief Delete the font manager.
     */
    static void terminate();

    virtual ~FontManager();

    private:
    /**
     * The font manager.
     */
    static FontManager* mFontManager;

    /**
     * @brief Manages all fonts.
     */
    FontManager();

    // The fonts.
    std::map<std::string, sf::Font> mSFFonts;
    std::list<gcn::SFMLFont*> mGCNFonts;
};

#endif /* FONTMANAGER_HPP_ */
