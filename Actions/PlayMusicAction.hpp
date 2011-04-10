/*
 * PlayMusicAction.hpp
 *
 *  Created on: Aug 12, 2009
 *      Author: alienjon
 */
#ifndef PLAYMUSICACTION_HPP_
#define PLAYMUSICACTION_HPP_

#include <string>

#include "Action.hpp"
#include "../Managers/AudioManager.hpp"

/**
 * @brief An action that plays a music piece.
 */
class PlayMusicAction: public Action
{
    public:
    /**
     * @brief Plays the requested music.
     * @param music The music to play.
     * @param loops The number of times to play the music.
     * @param fadein The fadein time for the music.
     */
    PlayMusicAction(const std::string& music, unsigned int loops, unsigned int fadein = 0);

    /**
     * @brief Play the music.
     * @param eData The environment data.
     */
    virtual void activate(EnvironmentData& eData);

    private:
    /**
     * The music to play.
     */
    std::string mMusic;

    /**
     * The number of times to play the music (-1 for infinite)
     */
    unsigned int mLoops;

    /**
     * The fadein time for the music.
     */
    unsigned int mFadein;
};

#endif /* PLAYMUSICACTION_HPP_ */
