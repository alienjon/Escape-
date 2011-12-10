/*
 * PlaySoundAction.cpp
 *
 *  Created on: Aug 12, 2009
 *      Author: alienjon
 */
#include "PlaySoundAction.hpp"

using std::string;

PlaySoundAction::PlaySoundAction(const std::string& sound) :
	mSound(sound)
{
}

void PlaySoundAction::activate(Level& level)
{
    // Play the sound.
    AudioManager::playSound(mSound);

    // The action is complete.
    mPerformed = true;
}
