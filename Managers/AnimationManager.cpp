/*
 * AnimationManager.cpp
 *
 *  Created on: May 3, 2009
 *      Author: alienjon
 */
#include "AnimationManager.hpp"

#include <stdexcept>

#include "../Entities/Creatures/Creature.hpp"
#include "../Game/Game.hpp"
#include "../Engine/Logger.hpp"
#include "../main.hpp"
#include "VideoManager.hpp"

using std::ifstream;
using std::list;
using std::map;
using std::runtime_error;
using std::string;

// File information.
const string ANIMATIONMANAGER_METAFILE			  = "animations.dat";
const string ANIMATIONMANAGER_ANIMATION_PREFIX	  = "Animation Data/";
const string FILE_IMAGES_DIR 					  = "Images/";
const string ANIMATIONMANAGER_ANIMATION_EXTENSION = ".ani";

AnimationManager::AnimationManager() :
	mAnimationDataIt(mAnimationData.begin())
{
	// A collection of animation filenames.
	list<string> animations;

	// Load the levels from the meta level data file.
    ifstream file(ANIMATIONMANAGER_METAFILE.c_str(), ifstream::in);

    // If the file opened successfully, then we are loading a game, otherwise start a new one.
    if(!file.good())
    {
        // Bad file opening.
        throw runtime_error("AnimationManager() -> Problem opening '" + ANIMATIONMANAGER_METAFILE + "'.");
    }

    // The current level name.
    string meta_file_line;

    // Iterate throughout the file and store each line as the name of a different animation file.
    while(!file.eof())
    {
    	// Get the line.
    	getline(file, meta_file_line);

    	// Ignore comments.
    	if(meta_file_line.empty() || meta_file_line[0] == '#')
    	{
    		continue;
    	}

    	// Get the current keyword.
    	string::size_type pos = 0;
    	string keyword = extractDataLine(meta_file_line, pos, CHAR_DELIMITER);
    	animations.push_back(ANIMATIONMANAGER_ANIMATION_PREFIX + meta_file_line + ANIMATIONMANAGER_ANIMATION_EXTENSION);
    }

    // Close the file.
    file.close();

    // Also add internal game images.
    list<string> frames;
    frames.push_back("Cursor/cursor.png");
    mAnimationData[ANIMATION_CURSOR] = frames;
    frames.clear();

    frames.push_back("null conversation.png");
    mAnimationData[ANIMATION_NULL_CONVERSATION] = frames;
    frames.clear();

    // For each animation file, open and store the data.
    string level_line;
    for(list<string>::iterator it = animations.begin(); it != animations.end(); ++it)
    {
    	// Open the file, but error if the file is not found.
    	file.open(it->c_str(), ifstream::in);
    	if(!file.good())
    	{
    		throw runtime_error("AnimationManager() -> Error loading animation file '" + *it + "'.");
    	}

    	// Process the file.
    	while(!file.eof())
    	{
			// Get the current line.
			getline(file, level_line);

			// Ignore comments.
			if(level_line.empty() || level_line[0] == '#')
			{
				continue;
			}

			// Get the data.
			string::size_type pos = 0;
			string keyword = extractDataLine(level_line, pos, CHAR_DELIMITER);
			list<string> frames;
			while(pos != level_line.size())
			{
				frames.push_back(extractDataLine(level_line, pos, CHAR_DELIMITER));
			}

			// Add the keyword-frames mapping to the data.
			mAnimationData[keyword] = frames;
    	}

    	// Close the file.
    	file.close();
    }

    // Set the animation data iterator.
    mAnimationDataIt = mAnimationData.begin();
}

void AnimationManager::create()
{
	if(mAnimationManager)
	{
		terminate();
	}
	mAnimationManager = new AnimationManager;
}

unsigned int AnimationManager::determineSize()
{
    return (unsigned int)mAnimationManager->mAnimationData.size();
}

const Sprite& AnimationManager::get(const string& name)
{
	map<string, Sprite>::const_iterator it = mAnimationManager->mAnimations.find(name);

	// If the sprite was not found, exit out (we don't know what to do, so error)
	if(it == mAnimationManager->mAnimations.end())
	{
		throw runtime_error("AnimationManager::get() -> Sprite with name '" + name + "' not found.");
	}

	return it->second;
}

const string AnimationManager::getCurrentResourceName()
{
    // Get the next data entry.
	return mAnimationManager->mAnimationDataIt->first;
}

bool AnimationManager::loadResource()
{
	// First make sure that we have not loaded all of the resources.
	if(mAnimationManager->mAnimationDataIt == mAnimationManager->mAnimationData.end())
	{
		return false;
	}

    // The new sprite.
    Sprite sprite;

    // Load all the frames of the current animation.
    for(list<string>::const_iterator it = mAnimationManager->mAnimationDataIt->second.begin(); it != mAnimationManager->mAnimationDataIt->second.end(); ++it)
    {
    	sprite.mAddFrame(VideoManager::loadSurface(FILE_IMAGES_DIR + (*it)));
    }

    // Add the newly generated animation to the animation list.
    mAnimationManager->mAnimations[mAnimationManager->mAnimationDataIt->first] = sprite;

    // Go to the next image.
    mAnimationManager->mAnimationDataIt++;

    // If this is the last data to load, return false.
    return mAnimationManager->mAnimationDataIt != mAnimationManager->mAnimationData.end();
}

void AnimationManager::terminate()
{
	delete mAnimationManager;
	mAnimationManager = 0;
}

AnimationManager* AnimationManager::mAnimationManager = 0;

const string ANIMATION_CURSOR = "CURSOR";
const string ANIMATION_NULL_CONVERSATION = "NULL_CONVERSATION";

const char CHAR_SLASH = '/';
