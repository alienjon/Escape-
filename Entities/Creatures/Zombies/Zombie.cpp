///*
// * Zombie.cpp
// *
// *  Created on: Aug 20, 2009
// *      Author: alienjon
// */
//
//#include "Zombie.hpp"
//
//#include "../../../Managers/AudioManager.hpp"
//#include "../../../main.hpp"
//#include "../../../Managers/ObjectManager.hpp"
//#include "../../../Actions/PlaySoundAction.hpp"
//#include "../../../Actions/WanderAction.hpp"
//
//Zombie::Zombie()
//{
//    // Zombie's initially wander.
//    setWandering(true);
//    addAction(new WanderAction(this));
//
//    // Find the initial groan pause time.
//    mGroanTimer.start();
//    mGroanCountTo = random(ZOMBIE_GROAN_PAUSE_MIN, ZOMBIE_GROAN_PAUSE_MAX);
//}
//
//Zombie::~Zombie()
//{
//}
//
//void Zombie::mDied()
//{
//    // Play a sound before the zombie dies.
//    addAction(new PlaySoundAction(SOUND_ZOMBIE_DEATH, 0));
//
//    // Continue with the death.
//    Enemy::mDied();
//
//    // Stop the groaning.
//    mGroanTimer.stop();
//}
//
//void Zombie::mPushedBackActions(Direction dir)
//{
//    // Play a sound that the zombie is being pushed back.
//    addAction(new PlaySoundAction(SOUND_ZOMBIE_PUSHED, 0));
//
//    // Continue with being pushed.
//    Enemy::mPushedBackActions(dir);
//}
//
//void Zombie::mRunOverTo(Entity& being)
//{
//    // Play the attack sound.
//    addAction(new PlaySoundAction(SOUND_ZOMBIE_ATTACK1, 0));
//
//    // Continue with the running already!
//    Enemy::mRunOverTo(being);
//}
//
//void Zombie::logic(EnvironmentData& eData)
//{
//    // Perform enemy logic.
//    Enemy::logic(eData);
//
//    // Update groan counter.
//    if(mGroanTimer.isStarted() && mGroanTimer.getTime() >= mGroanCountTo)
//    {
//        // Play a random sound.
//        int i = random(1, 2); // Between 1 and n, where n is the number of 'grunting/moaning' sounds.
//        switch(i)
//        {
//            case 1:
//            {
//                AudioManager::play(SOUND_ZOMBIE_MOAN1);
//                break;
//            }
//            default:
//            {
//                AudioManager::play(SOUND_ZOMBIE_MOAN2);
//            }
//        }
//
//        // Reset the timer.
//        mGroanTimer.start();
//        mGroanCountTo = random(ZOMBIE_GROAN_PAUSE_MIN, ZOMBIE_GROAN_PAUSE_MAX);
//    }
//}
//
//// In milliseconds.
//const unsigned int Zombie::ZOMBIE_GROAN_PAUSE_MIN = 1000;
//const unsigned int Zombie::ZOMBIE_GROAN_PAUSE_MAX = 15000;
