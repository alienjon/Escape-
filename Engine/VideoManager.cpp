/*
 * VideoManager.cpp
 *
 *  Created on: Nov 6, 2011
 *      Author: alienjon
 */
#include "VideoManager.hpp"

#include <stdexcept>

#include "../Engine/Guichan/sfml.hpp"

using std::map;
using std::runtime_error;
using std::string;

VideoManager::VideoManager()
{
    // An image loader is needed for GUIchan draw methods.
    gcn::Image::setImageLoader(this);
}

VideoManager::~VideoManager()
{
    // Clear the image loader.
    gcn::Image::setImageLoader(0);
}

void VideoManager::create()
{
    if(!mVideoManager)
        mVideoManager = new VideoManager;
}

const sf::Texture& VideoManager::getTexture(const std::string& filename)
{
	// Create the video manager if not created.
	if(!mVideoManager)
		create();

	// Find the requested image and create a sprite from it.
	map<string, sf::Texture>::iterator it = mVideoManager->mTextures.find(filename);
	if(it == mVideoManager->mTextures.end())
	{
		mVideoManager->mTextures[filename] = sf::Texture();
		if(!mVideoManager->mTextures[filename].LoadFromFile(filename))
			throw runtime_error("Error: requested image not found: " + filename);
		return mVideoManager->mTextures[filename];
	}
	return it->second;
}

gcn::Image* VideoManager::load(const string& filename, bool convertToDisplayFormat)
{
	map<string, gcn::Image*>::iterator it = mGCNImages.find(filename);
	if(it == mGCNImages.end())
	{
		if(!mVideoManager)
			create();
		mGCNImages[filename] = mVideoManager->gcn::SFMLImageLoader::load(filename, convertToDisplayFormat);
		return mGCNImages[filename];
	}
	return it->second;
}

void VideoManager::terminate()
{
    delete mVideoManager;
    mVideoManager = 0;
}

VideoManager* VideoManager::mVideoManager = 0;
