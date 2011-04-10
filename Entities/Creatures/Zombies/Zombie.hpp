///*
// * Zombie.hpp
// *
// *  Created on: Aug 20, 2009
// *      Author: alienjon
// */
//
//#ifndef ZOMBIE_HPP_
//#define ZOMBIE_HPP_
//
//#include "../Enemy.hpp"
//#include "../../../Engine/Timer.hpp"
//
///*
// * @brief A generic zombie class.
// */
//class Zombie : public Enemy
//{
//    public:
//    virtual ~Zombie();
//
//    /**
//     * @brief Perform internal logic.
//     * @param eData The level environment in which this entity resides.
//     */
//    virtual void logic(EnvironmentData& eData);
//
//    protected:
//    /**
//     * The zombie groan pause range.
//     */
//    static const unsigned int ZOMBIE_GROAN_PAUSE_MIN;
//    static const unsigned int ZOMBIE_GROAN_PAUSE_MAX;
//
//    /**
//     * @brief A default zombie.
//     */
//    Zombie();
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
//    /**
//     * @brief Run over to the given sprite.
//     * @param being The sprite to run towards.
//     */
//    void mRunOverTo(Entity& being);
//
//    /**
//     * The timer and counter to determine when the zombie will groan next.
//     */
//    Timer mGroanTimer;
//    unsigned int mGroanCountTo;
//};
//
//#endif /* ZOMBIE_HPP_ */
