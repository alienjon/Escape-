/*
 * PlaySoundAction.hpp
 *
 *  Created on: Aug 12, 2009
 *      Author: alienjon
 */

#ifndef PLAYSOUNDACTION_HPP_
#define PLAYSOUNDACTION_HPP_

#include <string>

#include "Action.hpp"
#include "../Managers/AudioManager.hpp"

/**
 * @brief An action that plays a sound.
 */
class PlaySoundAction : public Action
{
    public:
    /**
     * @brief Play the requested audio sound.
     * @param sound The sound to play.
     * @param loops The number of times to play the sound.
     */
    PlaySoundAction(const std::string& sound, unsigned int loops);

    /**
     * @brief Play the sound.
     * @param eData The environment data.
     */
    virtual void activate(EnvironmentData& eData);

    private:
    /**
     * The sound.
     */
    std::string mSound;

    /**
     * The number of times to play the sound.
     */
    unsigned int mLoops;
};

#endif /* PLAYSOUNDACTION_HPP_ */
