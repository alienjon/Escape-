/*
 * AudioManager.hpp
 *
 *  Created on: May 5, 2009
 *      Author: alienjon
 */
#ifndef AUDIOMANAGER_HPP_
#define AUDIOMANAGER_HPP_

#include <list>
#include <map>
#include <SFML/Audio.hpp>
#include <string>

/**
 * @brief A class that manages both music and sound effects.
 */
class AudioManager
{
    public:
    /**
     * @brief Create the audio manager.
     */
    static void create();

    /**
     * @brief Get a sound to play.
     * @param filename The filename of the sound.
     */
    static void playSound(const std::string& filename);

    /**
     * @brief Delete the manager.
     */
    static void terminate();

    protected:
    // The audio manager.
    static AudioManager* mAudioManager;

    /**
     * @brief Manage all audio aspects of the game.
     */
    AudioManager();

    /**
     * @brief Get the sound buffer based on its filename.
     * @param filename The filename of the sound buffer.
     * @return The sound buffer.
     */
    sf::SoundBuffer& mGetSoundBuffer(const std::string& filename);

    // The audio collections.
    std::map<std::string, sf::SoundBuffer> mSounds;

    // This is the list of playing sounds.  When playSound() is called, all stopped sounds are removed.
    std::list<sf::Sound> mPlayingSounds;
};

#endif /* AUDIOMANAGER_HPP_ */
