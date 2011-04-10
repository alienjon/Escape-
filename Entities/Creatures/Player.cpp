/*
 * Player.cpp
 *
 *  Created on: Apr 1, 2009
 *      Author: alienjon
 */
#include "Player.hpp"

#include <set>
#include <stdexcept>

#include "Enemy.hpp"

#include "../../Actions/Action.hpp"
#include "../../Managers/AudioManager.hpp"
#include "../../Math/Base64Functions.hpp"
#include "../../Game/Direction.hpp"
#include "../../Actions/DisplayAnimationAction.hpp"
#include "../../Math/Ellipse.hpp"
#include "../../Entities/Templates/EntityTemplate.hpp"
#include "../../Game/EnvironmentData.hpp"
#include "../../Game/Game.hpp"
#include "../../Entities/Non-Creatures/Item.hpp"
#include "../../Game/Keywords.hpp"
#include "../../Engine/Logger.hpp"
#include "../../main.hpp"
#include "../../Actions/MultipleActionsAction.hpp"
#include "../../Actions/PlaySoundAction.hpp"
#include "../../Actions/SlideAction.hpp"
#include "../../Engine/Surface.hpp"
#include "../../Math/Vector.hpp"

using std::list;
using std::runtime_error;
using std::set;
using std::string;

//@todo fix this!
const string PLAYER_PREFIX = "PLAYER";

const EntityTemplate PLAYERTEMPLATE("", PLAYER_PREFIX, Rectangle(0, 0, 30, 30));// @todo how to handle game-alignments? ie: set values of NEUTRAL, FRIENDLY, ENEMY?

// @todo Check to make sure the provided collision area's are correct.
Player::Player() : Creature("Player", PLAYERTEMPLATE, "FRIENDLY", 100, 100), // @todo should these be defined in a configuration file somewhere? also, what about the name of the player?
	mAllowInput(true),
	mIsStaringAtPoint(false),
	mIsInteracting(false)
{
    // This is the player.
    mType = ENTITY_PLAYER;

    // The player moves slightly faster than standard.
    setSpeed(1.5);

    // Start the interacting timer.
    mInteractingTimer.start();
}

Player::Player(const string& data) : Creature(data),
	mAllowInput(true),
	mIsStaringAtPoint(false),
	mIsInteracting(false)
{
    // This is the player.
    mType = ENTITY_PLAYER;

    // The player moves slightly faster than standard.
    setSpeed(1.5);

    // This is a friendly being.
    setAlignment("FRIENDLY");

    string::size_type pos = 0;

    /*
     * Load this entity in the following manner:
     * 1) Entity id
     * 2) Facing direction
     * 3) Max health
     * 4) Current health
     * @note The type isn't loaded, as it should be used by whatever is creating the entity.
     * @note Don't store the position, as each level will determine that.
     */
    mId = (unsigned int)toInt(extractDataLine(data, pos, CHAR_DELIMITER));
//    mSetStopAnimation(getDirection(toInt(extractDataLine(data, pos, CHAR_DELIMITER)))); @todo review
    mSetAnimation(CREATUREANIMATION_STANDING); // @todo temporary
    mMaxHealth = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
    mHealth = toInt(extractDataLine(data, pos, CHAR_DELIMITER));

    // Start the interacting timer.
    mInteractingTimer.start();
}

Player::~Player()
{
}

void Player::mCollision(Entity& collidee)
{
	// The player doesn't act with collisions the way other creatures might.
}


void Player::mCreatureInteract(Entity* object)
{
//    object->interact(this);
}

void Player::mDie()
{
    // Stop accepting player input.
    mAllowInput = false;

    // Continue dying.
    Creature::mDie();
}

string Player::extract() const
{
    // Store the value's, with a delimiter between each value, and then return the encoded value.// @todo implement saving
    string ret;/* = toString(getId()) + CHAR_DELIMITER + toString(getFacingDirection()) + CHAR_DELIMITER
                 + toString(mMaxHealth) + CHAR_DELIMITER + toString(mHealth);*/

    // @todo letters should be saved in the level/game screen
//    for(list<Letter*>::const_iterator it = mLetters.begin(); it != mLetters.end(); ++it)
//    {
//        ret += encodeBase64((*it)->extract()) + CHAR_DELIMITER;
//    }

    return ret;
}

void Player::handleInput(const Input& input)
{
	// Reset the velocity.
	mXVelocity = mYVelocity = 0;

	// Check for allowing input.
    if(!mAllowInput)
    {
        return;
    }

    // Calculate the velocity.
    if(input.isKeyPressed(SDLK_UP) || input.isKeyPressed(SDLK_w))
    {
    	mYVelocity--;
    }

    if(input.isKeyPressed(SDLK_DOWN) || input.isKeyPressed(SDLK_s))
    {
    	mYVelocity++;
    }

    if(input.isKeyPressed(SDLK_LEFT) || input.isKeyPressed(SDLK_a))
    {
    	mXVelocity--;
    }

    if(input.isKeyPressed(SDLK_RIGHT) || input.isKeyPressed(SDLK_d))
    {
    	mXVelocity++;
    }

    // Set the point being looked at unless the shift key is being pressed, then the player is focusing on something.
    if(input.isKeyPressed(SDLK_z))
    {
    	mIsStaringAtPoint = true;
    }
    else
    {
    	// Not staring.
    	mLookingAt = input.getMousePosition();
    	mIsStaringAtPoint = false;
    }

    // Press 'SPACE' or the left mouse button to interact.
    if((input.isKeyClicked(SDLK_SPACE) || input.isMousePressed(SDL_BUTTON_LEFT)) && mInteractingTimer.getTime() >= 250)
    {
    	mIsInteracting = true;
    	mInteractingTimer.start();
    }
}

void Player::interact(Entity& entity)
{
	// If the entity is an item, then pick the item up.
	if(entity.getType() == ENTITY_ITEM)
	{

		// Pick the item up.
		Item* item = dynamic_cast<Item*>(&entity);
		if(!item)
		{
			throw runtime_error("Player::interact() -> Error converting Entity* to Item*.");
		}
		pickupItem(*item);

		// Also remove it from the level.
		pushEvent(EVENT_ENTITY_REMOVE, entity.getName());
		pushEvent(EVENT_PLOTOCCURRENCE, KEYWORD_INTERACTION + CHAR_DELIMITER_ALTERNATE + getName() + CHAR_DELIMITER_ALTERNATE + entity.getName());
	}
	// If the entity is an enemy (not of the same alignment and not neutral) then attack it.
	else if(entity.getAlignment() == mAlignment || entity.getAlignment() == "NEUTRAL") // @todo create a neutral keyword
	{
		// Interact with the entity.
		pushEvent(EVENT_PLOTOCCURRENCE, KEYWORD_INTERACTION + CHAR_DELIMITER_ALTERNATE + getName() + CHAR_DELIMITER_ALTERNATE + entity.getName());
	}
	else
	{
		// Attack the entity.
		entity.push(getVectorOnLine(getPosition(), entity.getPosition(), 100), 40); // @todo what should the force be and how far should the entity be pushed?
	}
}

void Player::logic(EnvironmentData& eData)
{
	// Update the looking at position if not staring and if the player is accepting input.
	if(!mIsStaringAtPoint && mAllowInput)
	{
		mLookingAt.x += eData.getXOffset();
		mLookingAt.y += eData.getYOffset();
	}

	// If interacting, then interact with the environment.
	if(mIsInteracting)
	{
		// Interact.
		set<Entity*> e_set;
		e_set.insert(this);
		Entity* closest_entity = getClosestEntity(eData.checkCollision(mGetAreaInFront((getWidth() + getHeight()) / 2, 0, 0), e_set), *this);

		// If a closest entity was found, interact with it.
		if(closest_entity)
		{
			interact(*closest_entity);
		}

		// Not interacting anymore.
		mIsInteracting = false;
	}

    // Perform creature logic.
    Creature::logic(eData);
}

void Player::setInputState(bool state)
{
	mAllowInput = state;
}

const int PLAYER_PUSH_FORCE = 50;
const SDLKey PLAYER_ACTION_KEY = SDLK_SPACE;
const int Player::PLAYER_ACTION_DISTANCE = 2;