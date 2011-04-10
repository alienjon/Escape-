/*
 * PlaySoundAction.cpp
 *
 *  Created on: Aug 12, 2009
 *      Author: alienjon
 */
#include "PlaySoundAction.hpp"

using std::string;

PlaySoundAction::PlaySoundAction(const std::string& sound, unsigned int loops) :
	mSound(sound),
	mLoops(loops)
{
}

void PlaySoundAction::activate(EnvironmentData& eData)
{
    // Play the sound.
    AudioManager::playSound(mSound, mLoops);

    // The action is complete.
    mPerformed = true;
}
