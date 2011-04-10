/*
 * MusicNode.cpp
 *
 *  Created on: Aug 11, 2010
 *      Author: the-saint
 */
#include "MusicNode.hpp"

#include "../Managers/AudioManager.hpp"

using std::string;

MusicNode::MusicNode(const string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation, const string& musicFile, int loops, unsigned int fadeIn, unsigned int fadeOut) : PlotNode(keyword, activation, deactivation),
	mMusicFile(musicFile),
	mLoops(loops),
	mFadeIn(fadeIn),
	mFadeOut(fadeOut)
{
}

void MusicNode::activate()
{
	// Play the music file the specified number of times.
	AudioManager::playMusic(mMusicFile, mLoops, mFadeIn);
}

void MusicNode::deactivate()
{
	// Stop playing music.
	AudioManager::stopMusic(mFadeOut);
}
