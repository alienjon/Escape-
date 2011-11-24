///*
// * MoveToAction.hpp
// *
// *  Created on: Apr 19, 2009
// *      Author: alienjon
// */
//#ifndef MOVETOACTION_HPP_
//#define MOVETOACTION_HPP_
//
//#include <SFML/System.hpp>
//
//#include "../Actions/Action.hpp"
//#include "../Listeners/CreatureMovedToPointListener.hpp"
//
//class Creature;
//
///**
// * @brief An action that tells a creature to move to a certain point.
// */
//class MoveToAction : public Action, public CreatureMovedToPointListener
//{
//    public:
//    /**
//     * @brief Move the creature to the specified point.
//     * @param creature The creature to move.
//     * @param loc The point to move the creature to.
//     * @note The location to move to is the center of the creature where the creature will come to rest.
//     */
//    MoveToAction(Creature& creature, const sf::Vector2& loc);
//    virtual ~MoveToAction();
//
//    /**
//     * @brief Activate the action.
//     * @param level The level in which the action takes place.
//     */
//    virtual void activate(Level& level);
//
//    /**
//     * @brief The creature has moved to the next point on a path.
//     * @param creature The creature that moved.
//     */
//    virtual void creatureMoved(Creature& creature);
//
//    protected:
//    /**
//     * The creature to move.
//     */
//    Creature& mCreature;
//
//    /**
//     * The point to move to.
//     */
//    sf::Vector2 mLoc;
//};
//
//#endif /* MOVETOACTION_HPP_ */
