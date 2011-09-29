/*
 * GreenZombie.cpp
 *
 *  Created on: Jun 19, 2009
 *      Author: alienjon
 */
#include "GreenZombie.hpp"

#include <stdexcept>

#include "../../../Entities/Templates/EntityTemplate.hpp"
#include "../../../Game/Game.hpp"
#include "../../../main.hpp"

using std::string;
//@fixme fix this
const string GREENZOMBIE_PREFIX = "GREENZOMBIE";

const EntityTemplate GREENZOMBIETEMPLATE("", GREENZOMBIE_PREFIX, Rectangle(0, 0, 30, 30));

//@todo make sure the collision area is correct
GreenZombie::GreenZombie() : Creature("Green Zombie", GREENZOMBIETEMPLATE, "ZOMBIE", 100) // @todo should these be defined in a configuration file somewhere? Also, what about the name?
{
    // Randomize the initial facing direction.
    switch(random(1, 4))
    {
        case 1:
        {

            mFacingDirection = DIR_LEFT;
            break;
        }
        case 2:
        {
            mFacingDirection = DIR_RIGHT;
            break;
        }
        case 3:
        {
            mFacingDirection = DIR_UP;
            break;
        }
        default:
        {
            mFacingDirection = DIR_DOWN;
        }
    }

    mSetAnimation(CREATUREANIMATION_STANDING);

    // Green zombies are the weakest and do small amounts of damage. @todo update
//    mMaxDefense = 75;
//    mDefense = mMaxDefense;
//    mDamage = 10;
//    mMaxHealth = 50;
//    mHealth = mMaxHealth;
}

GreenZombie::GreenZombie(const string& data) : Creature(data) // @todo should these be defined in a configuration file somewhere? What about the name?
{
    string::size_type pos = 0;

    /*
     * Load this entity in the following manner:
     * 1) Entity id
     * 2) X position
     * 3) Y position
     * 4) Facing direction
     * 5) Alignment
     * 6) Max health
     * 7) Current health
     * @note The type isn't loaded, as it should be used by whatever is creating the entity.
     */
    mId = (unsigned int)toInt(extractDataLine(data, pos, CHAR_DELIMITER));
    setX(toInt(extractDataLine(data, pos, CHAR_DELIMITER)));
    setY(toInt(extractDataLine(data, pos, CHAR_DELIMITER)));
//    mSetStopAnimation(getDirection(toInt(extractDataLine(data, pos, CHAR_DELIMITER)))); @todo fix
//    mAlignment = ::getAlignment(toInt(extractDataLine(data, pos, CHAR_DELIMITER)));
    mMaxHealth = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
    mHealth = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
}

string GreenZombie::extract() const
{
    // Store the value's, with a delimiter between each value, and then return the encoded value.
    return toString(getId()) + CHAR_DELIMITER + toString(getX()) + CHAR_DELIMITER + toString(getY()) +
           CHAR_DELIMITER + toString(getFacingDirection()) + CHAR_DELIMITER + toString(getAlignment()) +
           CHAR_DELIMITER + toString(mMaxHealth) + CHAR_DELIMITER + toString(mHealth);
}
