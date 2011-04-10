/*
 * SoundNode.cpp
 *
 *  Created on: Aug 10, 2010
 *      Author: the-saint
 */
#include "SoundNode.hpp"

#include "../Managers/AudioManager.hpp"

using std::string;

SoundNode::SoundNode(const string& keyword, const NodeKeywordSet& activation, const NodeKeywordSet& deactivation, const string& soundfile, int loops) : PlotNode(keyword, activation, deactivation),
	mSoundFile(soundfile),
	mLoops(loops),
	mChannel(-1)
{
}

SoundNode::~SoundNode()
{
	// Just make sure this node is removed as a listener.
	AudioManager::removeSoundStoppedListener(this);
}

void SoundNode::activate()
{
	// Start listening for sounds.
	AudioManager::addSoundStoppedListener(this);

	// Start playing the sound (and store the channel to listen for).
	mChannel = AudioManager::playSound(mSoundFile, mLoops);
}

void SoundNode::deactivate()
{
	// Stop playing the sound, if it was originally set.
	if(mChannel >= 0)
	{
		AudioManager::stopSound(mChannel);
		AudioManager::removeSoundStoppedListener(this);
	}
}

void SoundNode::soundStopped(int channel)
{
	// If the provided channel is the channel being listened for, then deactivate.
	if(mChannel == channel)
	{
		mIsPerformed = true;
		mDistributePlotEvent();
	}
}
