///*
// * Enemy.hpp
// *
// *  Created on: Apr 2, 2009
// *      Author: alienjon
// */
//
//#ifndef ENEMY_HPP_
//#define ENEMY_HPP_
//
//#include <string>
//
//#include <guichan.hpp>
//
//#include "Creature.hpp"
//
//#include "../../main.hpp"
//#include "../../Engine/Renderer.hpp"
//#include "../../Engine/Timer.hpp"
//
//class Entity;
//class EnvironmentData;
//class CreatureManager;
//class ObjectManager;
//
///**
// * @brief A base class for all enemies.
// */
//class Enemy : public Creature
//{
//	public:
//	/**
//	 * @brief Attack the provided creature.
//	 * @param creature The creature to attack.
//	 * @note This will focus the enemy's attention on the provided enemy.
//	 */
//	virtual void attack(Creature* creature);
//
//	/**
//	 * @brief Draw the enemy.
//	 * @param renderer The graphics object.
//	 */
//	virtual void draw(Renderer& renderer);
//
//    /**
//     * @brief Called when the the player was seen and the enemy is frantically looking for him.
//     */
//    virtual void fastSearch();
//
//    /**
//     * @brief Interact with the player.
//     * @param player The player.
//     */
//    virtual void interact(Player* player);
//
//    /**
//     * @brief Perform internal logic.
//     * @param eData The level environment in which this entity resides.
//     */
//    virtual void logic(EnvironmentData& eData);
//
//    /**
//     * @brief Set the searching state of this enemy.
//     * @param state True if the enemy is to search and attack the player.
//     */
//    virtual void setSearching(bool state);
//
//    /**
//     * @brief Stop all movement.
//     */
//    virtual void stop();
//
//	protected:
//    /**
//     * The fast search max and min times.
//     */
//    static const int FASTSEARCH_MIN;
//    static const int FASTSEARCH_MAX;
//
//   /**
//     * @brief The enemy creature.
//     */
//    Enemy();
//
//    /**
//     * @brief Interact with the object.
//     * @param object The object.
//     */
//    virtual void mCreatureInteract(Entity* object);
//
//    /**
//     * @brief The enemy has died.
//     */
//    virtual void mDied();
//
//    /**
//     * @brief The actions to perform when the enemy is pushed backwards.
//     * @param dir The direction being pushed.
//     */
//    virtual void mPushedBackActions(Direction dir);
//
//	/**
//	 * @brief Run over to the given sprite.
//     * @param being The sprite to run towards.
//	 */
//	void mRunOverTo(Entity& being);
//
//	private:
//	/**
//	 * True if the enemy is searching for the player to attack.
//	 */
//	bool mIsSearching;
//
//    /**
//     * The timer for the fast search.
//     */
//    Timer mFastSearchTimer;
//
//    /**
//     * The time to wait until the creature turns again during a fast search.
//     */
//    uint mFastSearchTime;
//
//	/**
//	 * This is the default speed of an enemy.
//	 */
//	double mDefaultSpeed;
//
//	/**
//	 * This is the speed of the enemy when it is chasing the player.
//	 */
//	double mChasingSpeed;
//};
//
//#endif /* ENEMY_HPP_ */
