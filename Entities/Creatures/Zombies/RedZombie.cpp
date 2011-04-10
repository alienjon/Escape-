///*
// * RedZombie.cpp
// *
// *  Created on: Jun 19, 2009
// *      Author: alienjon
// */
//
//#include "RedZombie.hpp"
//
//#include <stdexcept>
//
//#include "../../../Game/Game.hpp"
//
//using std::string;
//
//RedZombie::RedZombie()
//{
//    // This is a red zombie.
//    mType = ENTITY_ZOMBIE_RED;
//
//    // Randomize the initial facing direction.
//    switch(random(1, 4))
//    {
//        case 1:
//        {
//            mSetStopAnimation(DIR_LEFT);
//            break;
//        }
//        case 2:
//        {
//            mSetStopAnimation(DIR_RIGHT);
//            break;
//        }
//        case 3:
//        {
//            mSetStopAnimation(DIR_UP);
//            break;
//        }
//        default:
//        {
//            mSetStopAnimation(DIR_DOWN);
//        }
//    }
//
//    // Red zombies are moderately strong and do moderate damage.
//    mMaxDefense = 100;
//    mDefense = mMaxDefense;
//    mDamage = 15;
//    mMaxHealth = 100;
//    mHealth = mMaxHealth;
//}
//
//RedZombie::RedZombie(const string& data)
//{
//    // This is a red zombie.
//    mType = ENTITY_ZOMBIE_RED;
//
//    string::size_type pos = 0;
//
//    /*
//     * Load this entity in the following manner:
//     * 1) Entity id
//     * 2) X position
//     * 3) Y position
//     * 4) Facing direction
//     * 5) Alignment
//     * 6) Max health
//     * 7) Current health
//     * @note The type isn't loaded, as it should be used by whatever is creating the entity.
//     */
//    mId = (unsigned int)toInt(extractDataLine(data, pos, CHAR_DELIMITER));
//    setX(toInt(extractDataLine(data, pos, CHAR_DELIMITER)));
//    setY(toInt(extractDataLine(data, pos, CHAR_DELIMITER)));
//    mSetStopAnimation(getDirection(toInt(extractDataLine(data, pos, CHAR_DELIMITER))));
//    mAlignment = ::getAlignment(toInt(extractDataLine(data, pos, CHAR_DELIMITER)));
//    mMaxHealth = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
//    mHealth = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
//}
//
//string RedZombie::extract() const
//{
//    // Store the value's, with a delimiter between each value, and then return the encoded value.
//    return toString(getId()) + CHAR_DELIMITER + toString(getX()) + CHAR_DELIMITER + toString(getY()) +
//           CHAR_DELIMITER + toString(getFacingDirection()) + CHAR_DELIMITER + toString(getAlignment()) +
//           CHAR_DELIMITER + toString(mMaxHealth) + CHAR_DELIMITER + toString(mHealth);
//}
