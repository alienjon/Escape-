/*
 * PlaySoundAction.hpp
 *
 *  Created on: Aug 12, 2009
 *      Author: alienjon
 */
#ifndef PLAYSOUNDACTION_HPP_
#define PLAYSOUNDACTION_HPP_

#include <string>

#include "../Actions/Action.hpp"
#include "../Engine/AudioManager.hpp"

/**
 * @brief An action that plays a sound.
 */
class PlaySoundAction : public Action
{
    public:
    /**
     * @brief Play the requested audio sound.
     * @param sound The sound to play.
     */
    PlaySoundAction(const std::string& sound);

    /**
     * @brief Activate the action.
     * @param level The level in which the action takes place.
     */
    virtual void activate(Level& level);

    private:
    // The sound.
    std::string mSound;
};

#endif /* PLAYSOUNDACTION_HPP_ */
