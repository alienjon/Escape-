/*
 * FontManager.cpp
 *
 *  Created on: Jul 8, 2009
 *      Author: alienjon
 */
#include "FontManager.hpp"

#include <stdexcept>

using std::list;
using std::map;
using std::runtime_error;
using std::string;

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
}

void FontManager::create()
{
    if(!mFontManager)
        mFontManager = new FontManager();
}

const sf::Font& FontManager::getSFFont(const string& filename)//@fixme The font manager isn't working.  Do I want it anyway?
{
    if(!mFontManager)
    	create();
	map<string, sf::Font>::iterator it = mFontManager->mSFFonts.find(filename);
	if(it == mFontManager->mSFFonts.end())
	{
		mFontManager->mSFFonts[filename] = sf::Font();
		if(!mFontManager->mSFFonts[filename].loadFromFile(filename))
			throw runtime_error("Error loading sf::Font: " + filename);
		return mFontManager->mSFFonts[filename];
	}
	return it->second;
}

void FontManager::terminate()
{
    delete mFontManager;
    mFontManager = 0;
}

FontManager* FontManager::mFontManager = 0;
