/*
 * Creature.cpp
 *
 *  Created on: Apr 1, 2009
 *      Author: alienjon
 */
#include "Creature.hpp"

#include <fstream>
#include <stdexcept>
#include <vector>

#include "../Actions/AlphaCycleAction.hpp"
#include "../Actions/CheckCollisionAction.hpp"
#include "../Game/Level.hpp"
#include "../Engine/Logger.hpp"
#include "../main.hpp"
#include "../Actions/MoveToAction.hpp"
#include "../Actions/MultipleActionsAction.hpp"
#include "../Actions/SetCollidableAction.hpp"
#include "../Actions/SetInteractableAction.hpp"
#include "../Engine/VideoManager.hpp"

using std::ifstream;
using std::list;
using std::queue;
using std::runtime_error;
using std::string;
using std::vector;

const unsigned int CREATURE_MOVEMENT_DISTANCE = 1;
const double CREATURE_ACCELERATION_RATE = 0.075;

void fillAnimationData(vector<unsigned int>& dList, const string& data)
{
	string::size_type pos = 0;
	while(pos != data.length())
		dList.push_back(toInt(extractDataLine(data, pos, ':')));
}

Creature::Creature(const string& imageData) :
	mUp(false), mDown(false), mLeft(false), mRight(false),
	mSpeed(1.f),
	mCurrentSpeed(0.f),
	mMovable(true)
{
	// Initializations.
	mType = ENTITY_CREATURE;
    mMovementTimer.start();
    for(int i = 0; i != 9; ++i) // Populate the directions sprite.
    	mDirections.push_back(AnimatedSprite());

    // Load the image data and process the images.
    ifstream dataFile;
    dataFile.open(imageData.c_str(), ifstream::in);
    string line, keyword, value, metaImage;
    sf::IntRect imageArea(0, 0, 0, 0);
    vector<unsigned int> frameData[9] = {vector<unsigned int>(), vector<unsigned int>(), vector<unsigned int>(), vector<unsigned int>(), vector<unsigned int>(), vector<unsigned int>(), vector<unsigned int>(), vector<unsigned int>(), vector<unsigned int>()}; // An array of lists of IDs. Each ID represents an image in the frame for the referring image in the array.
    unsigned int animation_speed = 100;
    if(dataFile.good())
    {
    	while(getline(dataFile, line))
    	{
			string::size_type pos = 0;
			keyword = extractDataLine(line, pos, '=');
			value	= line.substr(pos);

			if(keyword.empty() || keyword[0] == '#') // If blank or a comment then skip the line.
				continue;
			else if(keyword == "file") // If this is the file line then load the image and its size.
			{
				string::size_type im_pos = 0;
				metaImage = extractDataLine(value, im_pos, ':');
				animation_speed = toInt(extractDataLine(value, im_pos, ':'));
				imageArea.width = toInt(extractDataLine(value, im_pos, ':'));
				imageArea.height = toInt(extractDataLine(value, im_pos, ':'));
			}
			else // Otherwise, load the specified image data.
			{
				switch(toInt(keyword))
				{
					case 0: {fillAnimationData(frameData[0], value); break;}
					case 1: {fillAnimationData(frameData[1], value); break;}
					case 2: {fillAnimationData(frameData[2], value); break;}
					case 3: {fillAnimationData(frameData[3], value); break;}
					case 4: {fillAnimationData(frameData[4], value); break;}
					case 5: {fillAnimationData(frameData[5], value); break;}
					case 6: {fillAnimationData(frameData[6], value); break;}
					case 7: {fillAnimationData(frameData[7], value); break;}
					case 8: {fillAnimationData(frameData[8], value); break;}
					default: {LOG("Creature() -> Unknown keyword: " + keyword); break;}
				}
			}
    	}
    }
    else
    {
    	string err = "Creature: Unable to open " + imageData;
    	throw std::runtime_error(err.c_str());
    }

    // Now load the animation frames from the meta image.
    const sf::Texture& tex = VideoManager::getTexture(metaImage);
    unsigned int imageWidth = tex.getSize().x / imageArea.width;

    for(unsigned int image = 0; image != 9; ++image)
    {
    	for(unsigned int id = 0; id != frameData[image].size(); ++id)
    	{
    		imageArea.left = frameData[image][id] * imageArea.width; // update the x position
    		imageArea.top  = (frameData[image][id] / imageWidth) * imageArea.height; // update the y position
    		mDirections[image].addFrame(tex, imageArea); // add the frame
    		mDirections[image].setAnimationSpeed(animation_speed);
    		mDirections[image].setOrigin(imageArea.width / 2, imageArea.height / 2);
    	}
    }

    // Start off in the neutral state.
    mSprite = mDirections[FACINGDIRECTION_NEUTRAL];
}

Creature::~Creature()
{
    // Need to delete the actions here, because if I wait until the creature is deleted, certain
    // objects that are part of an entity (or other sub-classes) may get removed while still
    // needing the creature-like aspects of this object {cough cough moveToAction() cough cough}
    clearActions();
}

void Creature::mDie()
{
    // Stop moving.
    setMovable(false);

    // Continue dying.
    Entity::mDie();
}

void Creature::mMovedToWaypoint()
{
    // Tell all listeners that the creature has moved to the next path point.
    for(list<CreatureWaypointListener*>::iterator it = mWaypointListeners.begin(); it != mWaypointListeners.end(); it++)
        (*it)->creatureMoved(*this);
}

void Creature::mUpdateFacingAnimation()
{
	if(mUp && mRight)
		mSprite = mDirections[FACINGDIRECTION_UPRIGHT];
	else if(mDown && mRight)
		mSprite = mDirections[FACINGDIRECTION_DOWNRIGHT];
	else if(mDown && mLeft)
		mSprite = mDirections[FACINGDIRECTION_DOWNLEFT];
	else if(mUp && mLeft)
		mSprite = mDirections[FACINGDIRECTION_UPLEFT];
	else if(mUp)
		mSprite = mDirections[FACINGDIRECTION_UP];
	else if(mRight)
		mSprite = mDirections[FACINGDIRECTION_RIGHT];
	else if(mDown)
		mSprite = mDirections[FACINGDIRECTION_DOWN];
	else if(mLeft)
		mSprite = mDirections[FACINGDIRECTION_LEFT];
	else
		mSprite = mDirections[FACINGDIRECTION_NEUTRAL];
}

void Creature::logic(Level& level, int delta)
{
	// If the creature is moving towards a waypoint, determine the direction to move.
	if(!mWaypoints.empty())
	{
		mUp = mDown = mLeft = mRight = false;
		if(mWaypoints.front().y < getY() - CREATURE_MOVEMENT_DISTANCE * mSpeed)
			mUp = true;
		if(mWaypoints.front().y > getY() + CREATURE_MOVEMENT_DISTANCE * mSpeed)
			mDown = true;
		if(mWaypoints.front().x < getX() - CREATURE_MOVEMENT_DISTANCE * mSpeed)
			mLeft = true;
		if(mWaypoints.front().x > getX() + CREATURE_MOVEMENT_DISTANCE * mSpeed)
			mRight = true;
	}

	// If the creature is moving in at least one direction then move.
	if(isMovable() && (mUp || mDown || mLeft || mRight))
	{
		// If we're moving, then do the generic stuff.
		if(mMovementTimer.getTime() > 15)
		{
			// Handle acceleration.
			mCurrentSpeed = mCurrentSpeed + CREATURE_ACCELERATION_RATE < getSpeed() ? mCurrentSpeed + CREATURE_ACCELERATION_RATE : getSpeed(); // Increment the current speed, but cap it at mSpeed.

			float dist = mCurrentSpeed * delta;
			if(mUp)
			{
				setY(getY() - dist);
				bool entity = level.checkEntityCollision(*this);
				if(level.checkMapCollision(*this) || entity)
					setY(getY() + dist);
				if(entity && !mWaypoints.empty())
					mUp = false;
			}
			if(mDown)
			{
				setY(getY() + dist);
				bool entity = level.checkEntityCollision(*this);
				if(level.checkMapCollision(*this) || entity)
					setY(getY() - dist);
				if(entity && !mWaypoints.empty())
					mDown = false;
			}
			if(mLeft)
			{
				setX(getX() - dist);
				bool entity = level.checkEntityCollision(*this);
				if(level.checkMapCollision(*this) || entity)
					setX(getX() + dist);
				if(entity && !mWaypoints.empty())
					mLeft = false;
			}
			if(mRight)
			{
				setX(getX() + dist);
				bool entity = level.checkEntityCollision(*this);
				if(level.checkMapCollision(*this) || entity)
					setX(getX() - dist);
				if(entity && !mWaypoints.empty())
					mRight = false;
			}

			// Restart the timer.
			mMovementTimer.start();
		}
	}

	// Run any logic for the creature having stopped moving.
	if(!mUp && !mDown && !mLeft && !mRight)
	{
		// Reset the acceleration counter.
		mCurrentSpeed = 0.f;

		// If the creature is moving to a waypoint, then go to the next waypoint.
		if(!mWaypoints.empty())
		{
			mWaypoints.pop(); // Go to the next waypoint.
			mMovedToWaypoint(); // Run any 'moved to waypoint' code.
			mUpdateFacingAnimation(); // Update the facing direction.
		}
	}

    // Call the entity's logic.
    Entity::logic(level, delta);
}

void Creature::phaseTo(const sf::Vector2f& vec)
{
	// Create the action list of what is to be done for phasing.
	ActionList* lst = new ActionList();

	// Start oscillating the player alpha.
	AlphaCycleAction* alpha = new AlphaCycleAction(*this);
	addCreatureWaypointListener(alpha);
	lst->push_back(alpha);

	// Check the collidable and interactable states and set as appropriate (they need to be false for the phase walk, but set it back afterwards)
	if(isCollidable())
		lst->push_back(new SetCollidableAction(*this, false));
	if(isInteractable())
		lst->push_back(new SetInteractableAction(*this, false));
	lst->push_back(new MoveToAction(*this, vec));

	// Combine the actions together in a multiple action.
	addAction(new MultipleActionsAction(lst));

	// Create the action list of what is to be done to cleanup from phasing.
	lst = new ActionList();
	if(isCollidable())
		lst->push_back(new SetCollidableAction(*this, true));
	if(isInteractable())
		lst->push_back(new SetInteractableAction(*this, true));
	addAction(new MultipleActionsAction(lst));

	// After all the rest of this, check to see if the creature landed on something.
	addAction(new CheckCollisionAction(*this));
}

void Creature::setWaypoint(const sf::Vector2f& waypoint)
{
	while(!mWaypoints.empty())
		mWaypoints.pop();
	addWaypoint(waypoint);
}

void Creature::stop()
{
    // Stop all movements.
	mUp = mDown = mLeft = mRight = false;

    // Consider the creature to have moved to its next waypoint.
	while(!mWaypoints.empty())
		mWaypoints.pop();
    mMovedToWaypoint();

	// Also stop doing stuff.
	clearActions();
}
