///*
// * LoadLevelTrigger.hpp
// *
// *  Created on: Aug 12, 2009
// *      Author: alienjon
// */
//
//#ifndef LEVELLEVELTRIGGER_HPP_
//#define LEVELLEVELTRIGGER_HPP_
//
//#include "Trigger.hpp"
//
//#include "../LevelInfo/Level.hpp"
//#include "../Entities/Misc/NonDisplayingEntity.hpp"
//#include "../Entities/Creatures/Player.hpp"
//#include "../Engine/Renderer.hpp"
//
//class EnvironmentData;
//
///**
// * @brief A trigger that listens for a being's interaction with a player and then loads the next level.
// */
//class LoadLevelTrigger : public Trigger, public InteractionListener
//{@todo need to implement loading levels
//    public:
//    /**
//     * @brief A trigger to load the next level.
//     * @param level The current level.
//     * @param being The non displaying being that acts as the physical trigger.
//     * @param player Only the player can activate this trigger.
//     */
//	LoadLevelTrigger(Level* level, Entity* trigger, Entity* player);
//
//    /**
//     * @brief Load the trigger from the data string.
//     * @param level The current level.
//     * @param data The data string.
//     */
//	LoadLevelTrigger(Level* level, const std::string& data);
//    virtual ~LoadLevelTrigger();
//
//    /**
//     * @brief Draw the trigger, if necessary.
//     * @param graphics The graphics object with which to draw.
//     */
//    virtual void draw(Renderer& renderer);
//
//    /**
//     * @brief Extract this trigger as a data string.
//     * @return The data string representation of this trigger.
//     */
//    virtual std::string extract() const;
//
//    /**
//     * @brief A being was interacted with.
//     * @param actor The acting being.
//     * @param interacter The being being interacted with.
//     */
//    virtual void interactionOccurred(Entity* actor, Entity* interacter);
//
//    /**
//     * @brief A trigger logic function.
//     * @param eData The environment data.
//     * @note As this trigger functions as a listener, the logic method is empty.
//     */
//    virtual void logic(EnvironmentData& eData);
//
//    private:
//    /**
//     * This trigger activates via player interaction with this non displaying being.
//     */
//    Entity* mTrigger;
//
//    /**
//     * The player itself.
//     */
//    Entity* mPlayer;
//};
//
//#endif /* LOADLEVELTRIGGER_HPP_ */
