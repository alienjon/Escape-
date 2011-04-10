///*
// * ExplodingTrigger.hpp
// *
// *  Created on: Aug 14, 2009
// *      Author: alienjon
// */
//
//#ifndef EXPLODINGTRIGGER_HPP_
//#define EXPLODINGTRIGGER_HPP_
//
//#include "Trigger.hpp"
//
//#include "../Listeners/AnimationCycleListener.hpp"
//#include "../Math/Rectangle.hpp"
//#include "../Engine/Renderer.hpp"
//#include "../Engine/Sprite.hpp"
//
//class Entity;
//class EnvironmentData;
//class Level;
//
///*
// * @brief A trigger to tie to either another object or an area and will cause an explosion.
// *
// * While the explosion itself will do damage to nearby creatures, if there is an object
// * tied to the explosion, it is destroyed regardless.
// *
// * @todo Implement a way to have a trigger trip more than once for explosions.Trigger(level),
//
// */
//class ExplodingTrigger : public Trigger, public AnimationCycleListener
//{
//    public:
//    /**
//     * @brief This trigger trips when an entity enters the designated area.
//     * @param area The detonation area.
//     * @param damage The damage to perform on the entities in the explosion area.
//     */
//    ExplodingTrigger(const Rectangle& area, int damage);
//
//    /**
//     * @brief Load the trigger from the data string.
//     * @param data The data string.
//     */
//    ExplodingTrigger(const std::string& data);
//    virtual ~ExplodingTrigger();
//
//    /**
//     * @brief A drawing of the animation has been cycled.
//     */
//    virtual void animationCycled();
//
//    /**
//     * @brief Draw the explosion, if it is exploding.
//     * @param renderer The graphics object with which to draw.
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
//     * @brief Perform logic.
//     * @param eData The environmental data.
//     */
//    virtual void logic(EnvironmentData& eData);
//
//    protected:
//    /**
//     * @brief Start blowing up this explosion.
//     * @param eData The environment's data.
//     */
//    virtual void mExplode(EnvironmentData& eData);
//
//    private:
//    /**
//     * The detonation area.
//     */
//    Rectangle mDetonationArea;
//
//    /**
//     * A handle to the explosion sprite.
//     */
//    Sprite mSprite;
//
//    /**
//     * The damage to perform.
//     */
//    int mDamage;
//
//    /**
//     * The number of levels the explosion will branch out to.
//     * Row levels: The number of vertical (up and down) levels.
//     * Col levels: The number of horizontal (left and right) levels.
//     */
//    int mTotalRowLevels;
//    int mTotalColLevels;
//
//    /**
//     * The current number of levels.
//     */
//    int mCurrentLevel;
//
//    /**
//     * The exploding states.
//     */
//    bool mExplodingStarted;
//    bool mExplodingStopped;
//};
//
//#endif /* EXPLODINGTRIGGER_HPP_ */
