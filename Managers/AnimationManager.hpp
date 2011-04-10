/*
 * AnimationManager.hpp
 *
 *  Created on: May 3, 2009
 *      Author: alienjon
 */

#ifndef ANIMATIONMANAGER_HPP_
#define ANIMATIONMANAGER_HPP_

#include <list>
#include <map>
#include <string>

#include "../Engine/Sprite.hpp"

/**
 * @brief An object to manage all animations for in game usage.
 */
class AnimationManager
{
    public:
	/**
	 * @brief Create the animation manager.
	 */
	static void create();

    /**
     * @brief Determine the size of the resources to load.
     * @return The number of resources this manager manages.
     */
    static unsigned int determineSize();

    /**
     * @brief Get the sprite based on the provided keyword.
     * @param name The name of the sprite to retrieve.
     * @return The requested sprite.
     */
    static const Sprite& get(const std::string& name);

    /**
     * @brief Get the name of the current resource.
     * @return The name of the next resource that will be loaded.
     */
    static const std::string getCurrentResourceName();

    /**
     * @brief Load a single resource.
     * @return True if more resources are to be loaded.
     */
    static bool loadResource();

    /**
     * @brief Terminate the manager.
     */
    static void terminate();

    protected:
    /**
     * The animation manager.
     */
    static AnimationManager* mAnimationManager;

    /**
     * @brief Manages all animations.
     */
    AnimationManager();

    private:
    /**
     * These containers hold the frames for the various animations.
     */
    std::map<std::string, std::list<std::string> > mAnimationData;

    /**
     * The iterator to the currently loading animation data.
     */
    std::map<std::string, std::list<std::string> >::const_iterator mAnimationDataIt;

    /**
     * These are the various animations and their keywords.
     */
    std::map<std::string, Sprite> mAnimations;
};

// In-game animations.
extern const std::string ANIMATION_CURSOR;
extern const std::string ANIMATION_NULL_CONVERSATION;

#endif /* ANIMATIONMANAGER_HPP_ */
