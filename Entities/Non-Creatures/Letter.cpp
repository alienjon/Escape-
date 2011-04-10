/*
 * Letter.cpp
 *
 *  Created on: Aug 18, 2009
 *      Author: alienjon
 */

#include "Letter.hpp"

#include <stdexcept>

#include "../../Managers/AnimationManager.hpp"
#include "../../Game/Game.hpp"
#include "../../LevelInfo/Level.hpp"
#include "../../main.hpp"
#include "../Creatures/Player.hpp"

using std::string;

Letter::Letter(const std::string& name, const EntityTemplate& temp, const std::string& subject, const std::string& message) : Item(name, temp),
	mSubject(subject),
    mMessage(message)
{
    // Load the letter's animation.
// @todo need to implement letters    mSetAnimation(AnimationManager::getEntityAnimation(ENTITY_LETTER, ANIMATIONTYPE_NULL, DIR_NONE));
}

string Letter::extract() const
{
    // Store the value's, with a delimiter between each value, and then return the encoded value.
    return toString(getId()) + CHAR_DELIMITER + toString(getX()) + CHAR_DELIMITER + toString(getY()) +
           CHAR_DELIMITER + mSubject + CHAR_DELIMITER + mMessage;
}

const string& Letter::getSubject() const
{
    return mSubject;
}

const string& Letter::getMessage() const
{
    return mMessage;
}

void Letter::interact(Player* player)
{
	// @todo the player should pick up the letter when it is walked into, not interacted with
//    // Add this letter to the list of letters collected by the player.
//    player->addLetter(this);
//
//    // Now tell the level that this letter has been found.
//    mLevel->removeLetter(this);
}
