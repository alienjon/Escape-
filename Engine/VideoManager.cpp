/*
 * VideoManager.cpp
 *
 *  Created on: Nov 6, 2011
 *      Author: alienjon
 */
#include "VideoManager.hpp"

#include <stdexcept>

using std::map;
using std::runtime_error;
using std::string;

VideoManager::VideoManager()
{
}

VideoManager::~VideoManager()
{
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
		if(!mVideoManager->mTextures[filename].loadFromFile(filename))
			throw runtime_error("Error: requested image not found: " + filename);
		return mVideoManager->mTextures[filename];
	}
	return it->second;
}

void VideoManager::terminate()
{
    delete mVideoManager;
    mVideoManager = 0;
}

VideoManager* VideoManager::mVideoManager = 0;
