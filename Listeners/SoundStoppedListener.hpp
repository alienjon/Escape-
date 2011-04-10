/*
 * SoundLoopListener.hpp
 *
 *  Created on: Aug 11, 2010
 *      Author: the-saint
 */
#ifndef SOUNDLOOPLISTENER_HPP_
#define SOUNDLOOPLISTENER_HPP_

/**
 * @brief A listener for when a sound has stopped.
 */
class SoundStoppedListener
{
	public:
	/**
	 * @brief Called when a sound has stopped.
	 * @param channel The channel of the sound that has stopped.
	 */
	virtual void soundStopped(int channel) = 0;
};

#endif /* SOUNDLOOPLISTENER_HPP_ */
