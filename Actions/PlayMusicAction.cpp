/*
 * PlayMusicAction.cpp
 *
 *  Created on: Aug 12, 2009
 *      Author: alienjon
 */
#include "PlayMusicAction.hpp"

using std::string;

PlayMusicAction::PlayMusicAction(const string& music, unsigned int loops, unsigned int fadein) :
	mMusic(music),
	mLoops(loops),
	mFadein(fadein)
{
}

void PlayMusicAction::activate(EnvironmentData& eData)
{
    // Play the music.
    AudioManager::playMusic(mMusic, mLoops, mFadein);

    // Done.
    mPerformed = true;
}
