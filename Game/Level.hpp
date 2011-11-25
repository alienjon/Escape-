/*
 * Level.hpp
 *
 *  Created on: Apr 29, 2009
 *      Author: alienjon
 */
#ifndef LEVEL_HPP_
#define LEVEL_HPP_

#include <list>
#include "../Engine/guichan.hpp"
#include "../Engine/Guichan/sfml.hpp"

#include "../Interfaces/ActionInterface.hpp"
#include "../Interfaces/ChangeScoreInterface.hpp"
#include "../Listeners/ChangeScoreListener.hpp"
#include "../Listeners/DeathListener.hpp"
#include "../Listeners/FloatingTextListener.hpp"
#include "../Interfaces/GCNActionInterface.hpp"
#include "../Listeners/LevelCompleteListener.hpp"
#include "../Game/Map.hpp"
#include "../Entities/Portal.hpp"
#include "../Engine/Timer.hpp"

class Entity;
class Player;

/**
 * @brief A level is a single contained area in the game.
 *
 * The level essentially acts as a manager between all objects (creatures, items, traps)
 * and a single map.  It is literally a solitary contained area in the game.
 */
class Level : public ActionInterface, public ChangeScoreInterface, public ChangeScoreListener, public DeathListener, public GCNActionInterface, public FloatingTextListener, public LevelCompleteListener
{
    public:
    /**
     * @brief Construct a new level.
     * @param difficulty The difficulty of the level to create.
     */
    Level(unsigned int difficulty, Player& player);
    virtual ~Level();

    /**
     * @brief Display a floating text on the screen for a short period of time.
     * @param str The text to display.
     * @param position The initial position to display the text (it will float up over a short period of time)
     * @param color The color of the text to display.
     * @param size The character size of the text.
     */
    virtual void addFloatingText(const std::string& str, const sf::Vector2f& position, const sf::Color& color, unsigned int size);

	/**
	 * @brief Change the score by the provided amount.
	 * @param change The amount to change the score.
	 */
	virtual void changeScore(int change);

    /**
     * @brief Check if the provided entity collides with anything in the map.
     * @param entity The entity to check collisions against.
     * @return The entity that was collided against, or null if no collisions detected.
     */
    virtual Entity* checkEntityCollision(const Entity& entity) const;

    /**
     * @brief Check if the provided entity collides with the map.
     * @param entity The entity to check collisions against.
     * @return True if a collision was found.
     */
    virtual bool checkMapCollision(const Entity& entity) const;

    /**
     * @brief Called when the entity has died.
     * @param entity The entity who died.
     */
    inline void deathOccurred(Entity* entity)
    {
    	mDeadEntities.push_back(entity);
    }

    /**
     * @brief Draw, from gcn::Widget
     * @param graphics The graphics object.
     */
    virtual void draw(gcn::Graphics* graphics)
    {}

    /**
     * @brief Draw the map to the screen.
     * @param renderer The graphics object to draw with.
     */
    virtual void draw(gcn::SFMLGraphics& renderer);

    /**
     * @brief Flip the level upside-down.
     */
    virtual void flip();

    /**
     * @brief Get the map.
     * @return The map.
     */
    const Map& getMap() const;

    /**
     * @brief Checks whether the level has completed.
     * @return True if the level has completed.
     */
    virtual bool isDone() const;

    /**
     * @brief A level complete signal is called.
     */
    virtual void levelComplete();

    /**
     * @brief Calling logic for a level will call logic for all map tiles (if necessary), creatures and objects.
     * @param camera The camera that is looking at the level.
     */
    virtual void logic(sf::View& camera);

    /**
     * @brief Called when the player finds the exit.
     */
    virtual void playerFoundExit();

    private:
    /**
     * @brief Add an entity to the level.
     * @param entity The entity to add.
     */
    void mAddEntity(Entity* entity);

    /**
     * @brief Remove an entity to the level.
     * @param entity The entity to remove.
     */
    void mRemoveEntity(Entity* entity);

    /**
     * True if the level has completed.
     */
    bool mIsDone;

    // The player handle.
    Player& mPlayer;

    // The portal.
    Portal mPortal;

    // The entities in the level.
    std::list<Entity*> mEntities;

    // These are the floating texts found in the level.
    std::list<sf::Text> mFloatingTexts;

    // This is the floating text timer.
    Timer mFloatingTextTimer;

    // A level has a map.
    Map mMap;

    // A list of dead entities (to remove in logic).
    std::list<Entity*> mDeadEntities;

    // A list of pickups that could still be picked up and a toggle to check if an award has been given for picking all items up.
    std::list<Entity*> mPickups;
    bool mPickupAward;

    // The flip screen animation timer.
    Timer mFlipTimer;
    float mFlipAngle;
    bool mFlipped;
};

#endif /* LEVEL_HPP_ */
