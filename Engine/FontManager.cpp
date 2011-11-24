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
	for(list<gcn::SFMLFont*>::iterator it = mGCNFonts.begin(); it != mGCNFonts.end(); ++it)
		delete *it;
}

void FontManager::create()
{
    if(!mFontManager)
        mFontManager = new FontManager();
}

gcn::SFMLFont* FontManager::getGCNFont(const string& filename)
{
    if(!mFontManager)
    	create();
    gcn::SFMLFont* font = new gcn::SFMLFont(filename);
    mFontManager->mGCNFonts.push_back(font);
    return font;
}

const sf::Font& FontManager::getSFFont(const string& filename)
{
    if(!mFontManager)
    	create();
	map<string, sf::Font>::iterator it = mFontManager->mSFFonts.find(filename);
	if(it == mFontManager->mSFFonts.end())
	{
		mFontManager->mSFFonts[filename] = sf::Font();
		if(!mFontManager->mSFFonts[filename].LoadFromFile(filename))
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
