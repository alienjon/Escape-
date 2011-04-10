///*
// * ExplodingTrigger.cpp
// *
// *  Created on: Aug 14, 2009
// *      Author: alienjon
// */
//
//#include "ExplodingTrigger.hpp"
//
//#include <list>
//
//#include "../Actions/Action.hpp"
//#include "../Managers/AnimationManager.hpp"
//#include "../Managers/AudioManager.hpp"
//#include "../Engine/Colors.hpp"
//#include "../Entities/Entity.hpp"
//#include "../Game/EnvironmentData.hpp"
//#include "../Game/Game.hpp"
//#include "../LevelInfo/Level.hpp"
//#include "../main.hpp"
//
//using std::list;
//using std::string;
//
//ExplodingTrigger::ExplodingTrigger(const Rectangle& area, int damage) : mDetonationArea(area),
//// @todo need to implement explosions                                                                        mSprite(AnimationManager::getGameAnimation(GAMEANIMATIONTYPE_EXPLOSION_FIRE)),
//                                                                        mDamage(damage),
//                                                                        mTotalRowLevels(1),
//                                                                        mTotalColLevels(1),
//                                                                        mCurrentLevel(1),
//                                                                        mExplodingStarted(false),
//                                                                        mExplodingStopped(false)
//{
//    // This is an exploding trigger.
//    mType = TRIGGERTYPE_EXPLOSION;
//
//    // Determine the number of levels that will be drawn upon explosion.
//    int temp = mDetonationArea.height / mSprite.getHeight();
//    mTotalRowLevels = (temp < 1) ? 1 : temp - 1;
//    temp = mDetonationArea.width / mSprite.getWidth();
//    mTotalColLevels = (temp < 1) ? 1 : temp - 1;
//
//    // Don't have the sprite animate until we are ready to explode.
//    mSprite.setAnimating(false);
//    mSprite.setVisible(false);
//}
//
//ExplodingTrigger::ExplodingTrigger(const string& data) : // @todo need to implement explosions mSprite(AnimationManager::getGameAnimation(GAMEANIMATIONTYPE_EXPLOSION_FIRE)),
//                                                         mDamage(0),
//                                                         mTotalRowLevels(1),
//                                                         mTotalColLevels(1),
//                                                         mCurrentLevel(1),
//                                                         mExplodingStarted(false),
//                                                         mExplodingStopped(false)
//{
//    /**
//     * Load the trigger in the following order:
//     * 1) Detonation x
//     * 2) Detonation y
//     * 3) Detonation width
//     * 4) Detonation height
//     * 5) Damage
//     * 6) Exploding started
//     * 7) Exploding stopped
//     */
//    string::size_type pos = 0;
//    mDetonationArea.x = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
//    mDetonationArea.y = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
//    mDetonationArea.width = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
//    mDetonationArea.height = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
//    mDamage = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
//    mExplodingStarted = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
//    mExplodingStopped = toInt(extractDataLine(data, pos, CHAR_DELIMITER));
//
//    // Determine the number of levels that will be drawn upon explosion.
//    int temp = mDetonationArea.height / mSprite.getHeight();
//    mTotalRowLevels = (temp < 1) ? 1 : temp - 1;
//    temp = mDetonationArea.width / mSprite.getWidth();
//    mTotalColLevels = (temp < 1) ? 1 : temp - 1;
//
//    // Don't have the sprite animate until we are ready to explode.
//    mSprite.setAnimating(false);
//    mSprite.setVisible(false);
//}
//
//ExplodingTrigger::~ExplodingTrigger()
//{
//    // Stop listening to the sprite.
//    mSprite.removeAnimationCycleListener(this);
//}
//
//void ExplodingTrigger::mExplode(EnvironmentData& eData)
//{
//    // Make an explody sound.
//    AudioManager::play(SOUND_EXPLOSION);
//
//    // Start listening to when the animation has cycled.
//    mSprite.addAnimationCycleListener(this);
//
//    // Start animating.
//    mSprite.setAnimating(true);
//    mSprite.setVisible(true);
//
//    // Do immediate damage to any and all entities in the area.
//    list<Entity*> entities = eData.checkAllCollisions(mDetonationArea);
//    for(list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
//    {
//        (*it)->damage(mDamage);
//    }
//
//    // The explosion has finished starting.
//    mExplodingStarted = true;
//}
//
//void ExplodingTrigger::animationCycled()
//{
//    // A level has finished exploding
//    mCurrentLevel++;
//
//    // Determine if the explosion has finished.
//    if((mCurrentLevel >= mTotalRowLevels) && (mCurrentLevel >= mTotalColLevels))
//    {
//        mExplodingStopped = true;
//    }
//    else
//    {
//        // Make an explody sound, but only if this wasn't the last animation cycle.
//        AudioManager::play(SOUND_EXPLOSION);
//
//        // Perform damage to any creatures in the area.
//        // @todo Do damage on creatures each cycle, or just initially?
////        list<Entity*> entities = Entity::getLevel()->checkAllCollisions(mDetonationArea);
////        for(list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
////        {
////            (*it)->damage(mDamage);
////        }
//    }
//}
//
//void ExplodingTrigger::draw(Renderer& renderer)
//{
//    // If we are debugging, then draw the detonation area.
//    if(Game::isDebug())
//    {
//        renderer.setColor(COLOR_ORANGE);
//        Rectangle area(mDetonationArea);
//        renderer.fillRectangle(area);
//    }
//
//    // If the sprite isn't visible, don't bother drawing anything.
//    if(!mSprite.isVisible())
//    {
//        return;
//    }
//
//    // The center point.
//    Point center = mDetonationArea.getCenterPoint();
//
//    // If we are drawing the first level, only draw a single image.
//    if(mCurrentLevel == 1)
//    {
//    	mSprite.draw(renderer, center.x - (mSprite.getWidth() / 2), center.y - (mSprite.getHeight() / 2));
//    }
//    // Otherwise, determine the animations to draw on each side and draw the correct number of images in the correct positions.
//    // @note This will also draw a single level, if necessary, but it will be duplicated (extra overhead)
//    else
//    {
//        // Determine the number of row and column levels that will be drawn.
//        int rowLevel = (mCurrentLevel < mTotalRowLevels) ? mCurrentLevel : mTotalRowLevels;
//        int colLevel = (mCurrentLevel < mTotalColLevels) ? mCurrentLevel : mTotalColLevels;
//
//        // Now determine the number of rows and columns to draw (total #)
//        int rowLength = (rowLevel * 3) - (rowLevel + 1);
//        int colLength = (colLevel * 3) - (colLevel + 1);
//
//        // As I am drawing a box, the row loop and the column loop will both draw twice (once for the top/left and
//        //  the second for the bottom/right).
//        //
//        //  The first point in the location equation is the center point from which
//        //  we are starting.
//        //
//        //  From this we subtract half of the sprite width (this places us at the very center sprite
//        //  which could be drawn (if mCurrentLevel == 1).
//        //
//        //  Then the invariant calculation is included for the appropriate x, y position (y for rows
//        //  (which go up and down) and x for columns (which go left and right)).  This essentially calculates the
//        //  position from the sprite that we are drawing.  Note that this is only present for the corresponding
//        //  loop (y for rows and x for cols).
//        //
//        //  Next the distance based on the current col level or row level (if it is x or y, respectively) is
//        //  calculated (the '- 1' compensates for the central image). This is either added to the equation
//        //  (if we are to the right or bottom) or subtracted (if to the left or top).
//        //
//        //  Lastly, the offset is removed from the whole picture.
//        for(int i = 0; i != rowLength; ++i) // This will draw all items in both columns.
//        {
//            // Draw the left column.
//        	mSprite.draw(renderer, center.x - (mSprite.getWidth() / 2) - ((colLevel - 1) * mSprite.getWidth()),
//								   center.y - (mSprite.getHeight() / 2) - (mSprite.getHeight() * i) + ((rowLevel - 1) * mSprite.getHeight()));
//
//            // Draw the right column.
//        	mSprite.draw(renderer, center.x - (mSprite.getWidth() / 2) + ((colLevel - 1) * mSprite.getWidth()),
//								   center.y - (mSprite.getHeight() / 2) - (mSprite.getHeight() * i) + ((rowLevel - 1) * mSprite.getHeight()));
//        }
//        for(int i = 1; i < colLength; ++i) // To avoid repetition of drawing, this will not draw the first and last image (because the above loop already draws those)
//        {
//            // Draw the top row.
//        	mSprite.draw(renderer, center.x - (mSprite.getWidth() / 2) - (mSprite.getWidth() * i) + ((colLevel - 1) * mSprite.getWidth()),
//								   center.y - (mSprite.getHeight() / 2) - ((rowLevel - 1) * mSprite.getHeight()));
//
//            // Draw the bottom row.
//        	mSprite.draw(renderer, center.x - (mSprite.getWidth() / 2) - (mSprite.getWidth() * i) + ((colLevel - 1) * mSprite.getWidth()),
//								   center.y - (mSprite.getHeight() / 2) + ((rowLevel - 1) * mSprite.getHeight()));
//        }
//    }
//}
//
//string ExplodingTrigger::extract() const
//{
//    /**
//     * Extract the trigger in the following order:
//     * 1) Detonation x
//     * 2) Detonation y
//     * 3) Detonation width
//     * 4) Detonation height
//     * 5) Damage
//     * 6) Exploding started
//     * 7) Exploding stopped
//     */
//    return toString(mDetonationArea.x) + CHAR_DELIMITER + toString(mDetonationArea.y) + CHAR_DELIMITER +
//           toString(mDetonationArea.width) + CHAR_DELIMITER + toString(mDetonationArea.height) + CHAR_DELIMITER +
//           CHAR_DELIMITER + toString(mDamage) + CHAR_DELIMITER + toString((mExplodingStarted) ? "1" : "0") +
//           CHAR_DELIMITER + toString((mExplodingStopped) ? "1" : "0");
//}
//
//void ExplodingTrigger::logic(EnvironmentData& eData)
//{
//    // Sprite logic.
//    mSprite.logic();
//
//    // If an entity has entered the area and the explosion hasn't started, then start exploding.
//    if(!mExplodingStarted && eData.checkCollision(mDetonationArea))
//    {
//        // Start the explosion.
//        mExplode(eData);
//    }
//
//    // If the explosion has finished, then the trigger has been tripped.
//    if(mExplodingStopped)
//    {
//        mTripped = true;
//    }
//}
