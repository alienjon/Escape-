//#include <fstream>
//#include <stdexcept>
//#include <vector>
//
//#include "../Entities/Alignment.hpp"
//#include "../Entities/Creatures/Creature.hpp"
//#include "../Entities/Entity.hpp"
//#include "../Game/Game.hpp"
//#include "../Game/Keywords.hpp"
//#include "../LevelInfo/Level.hpp"
//#include "../Engine/Logger.hpp"
//#include "../main.hpp"
//#include "../Entities/Non-Creatures/Object.hpp"
//
//using std::deque;
//using std::ifstream;
//using std::list;
//using std::runtime_error;
//using std::set;
//using std::string;
//using std::vector;
//
//const string KEYWORD_TEMPLATE_OBJECT = "OBJECT";
//const string KEYWORD_TEMPLATE_CREATURE = "CREATURE";
//
//EnvironmentData::EnvironmentData(Map& map, const std::list<Entity*>& entities, const std::list<RectData> areas) :
//	mMap(map),
//	mEntities(entities),
//	mLightingState(true)
//{
//	// Listen to the initial entities (objects, creatures, etc...) for deaths.  Tiles and areas aren't listened to because they don't die.
//	for(list<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
//	{
//		(*it)->addDeathListener(this);
//		(*it)->addEventListener(this);
//		(*it)->addMovementListener(this);
//	}
//
//    // Add the middle layer of the map as entities.
//    for(vector<Tile>::iterator it = mMap.mMMap.begin(); it != mMap.mMMap.end(); ++it)
//    {
//    	// Ignore null tiles.
//    	if(it->getWidth() == 0 || it->getHeight() == 0)
//    	{
//    		continue;
//    	}
//    	mEntities.push_back(&(*it));
//    }
//
//    // Add the areas.
//    for(list<RectData>::const_iterator it = areas.begin(); it != areas.end(); ++it)
//    {
//    	mAreas.push_back(*it);
//    }
//
//	// Add this environment as a request listener.
//	Level::addEnvironmentalRequestListener(this); // @todo needed, or can I use the pushEvent() and event interface?
//	PlotManager::addEnvironmentalRequestListener(this); // @todo actually, these both might be able to be implemented in pushEvent().  Look into this to simplify things.
//}
//
//EnvironmentData::EnvironmentData(const EnvironmentData& eData) :
//	mMap(eData.mMap)
//{
//    // Check to make sure we aren't doing stuff with the same object.
//    if(&eData != this)
//    {
//        // Copy the entities.
//    	// NOTE: The entities are copied from one to the next, but they are NOT deleted.  This could result in segfaults later
//    	//		 because two EnvironmentData's might point to the same entities, but as there is probably only one environment
//    	//		 for any given level (and as the player/tiles are managed separately) this will likely not be an issue.
//        for(list<Entity*>::const_iterator it = eData.mEntities.begin(); it != eData.mEntities.end(); ++it)
//        {
//        	(*it)->addDeathListener(this);
//        	(*it)->addEventListener(this);
//        	(*it)->addMovementListener(this);
//            mEntities.push_back(*it);
//        }
//    }
//}
//
//EnvironmentData::~EnvironmentData()
//{
//	// Remove this environment as a request listener.
//	Level::removeEnvironmentalRequestListener(this);
//	PlotManager::removeEnvironmentalRequestListener(this);
//
//	// Remove this object as listeners.
//	for(list<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
//	{
//		(*it)->removeMovementListener(this);
//		(*it)->removeDeathListener(this);
//		(*it)->removeEventListener(this);
//	}
//}
//
//void EnvironmentData::mClearRemoved()
//{
//    // Go through all entities listed for removal and remove them (don't delete them, thats the game data's job).
//    for(deque<Entity*>::iterator it = mRemoval.begin(); it != mRemoval.end(); ++it)
//    {
//        // Remove from the objects list.
//        mEntities.remove(*it);
//    }
//
//    // Clear the removal list.
//    mRemoval.clear();
//}
//
//void EnvironmentData::addEntity(Entity* entity)
//{
//	// Add the entity.
//	mEntities.push_back(entity);
//
//	// Don't forget to listen to it.
//	entity->addDeathListener(this);
//	entity->addEventListener(this);
//	entity->addMovementListener(this);
//}
//
//void EnvironmentData::addLight(const Ellipse& area)
//{
//	mEllipseLights.push_back(area);
//}
//
//void EnvironmentData::addLight(const Quadrilateral& area)
//{
//	mQuadLights.push_back(area);
//}
//
//set<Entity*> EnvironmentData::checkCollision(Entity& entity)
//{
//	set<Entity*> caller;
//	caller.insert(&entity);
//	return checkCollision(entity.getDimension(), caller);
//}
//
//set<Entity*> EnvironmentData::checkCollision(const Quadrilateral& area, const set<Entity*>& callers)
//{
//	// The return list.
//	set<Entity*> found_entities;
//	for(list<Entity*>::const_iterator it = mEntities.begin(); it != mEntities.end(); ++it)
//	{
//		if(callers.find((*it)) == callers.end() && (*it)->isIntersecting(area))
//		{
//			found_entities.insert(*it);
//		}
//	}
//
//	// Return the generated list.
//	return found_entities;
//}
//
//void EnvironmentData::draw(Renderer& renderer)
//{
//	// @todo Only draw objects which are in a light somewhere (plus the player)
//    // Draw all objects.
//    for(list<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
//    {
//        (*it)->draw(renderer);
//    }
//}
//
//void EnvironmentData::drawLighting(Renderer& renderer)
//{
//	// If environmental lighting is enabled, then the entire area environment is visible.  Otherwise draw only specified lights.
//	if(!mLightingState)
//	{
//		// Lighting works on the upper layer.
//		renderer.setRenderingLayer(1);
//
//		// Clear the screen to black.
//		renderer.setColor(gcn::Color(0, 0, 0, SDL_ALPHA_OPAQUE));
//		renderer.clearScreen();
//
//		// Draw each light onto the screen as the transparent color.
//		renderer.setColor(gcn::Color(255, 0, 255, SDL_ALPHA_OPAQUE));
//		for(list<Ellipse>::iterator it = mEllipseLights.begin(); it != mEllipseLights.end(); ++it)
//		{
//			renderer.fillEllipse(*it);
//		}
//		for(list<Quadrilateral>::iterator it = mQuadLights.begin(); it != mQuadLights.end(); ++it)
//		{
//			renderer.fillQuadrilateral(*it);
//		}
//
//		// Return the renderer to the lower surface.
//		renderer.setRenderingLayer(0);
//	}
//	else
//	{
//		renderer.setRenderingLayer(1);
//		renderer.setColor(gcn::Color(255, 0, 255, SDL_ALPHA_OPAQUE));
//		renderer.clearScreen();
//		renderer.setRenderingLayer(0);
//	}
//}
//
//void EnvironmentData::entityMoved(Entity& entity)
//{
//	// If the creature entered any of the provided area's, push a plot event.
//	for(list<RectData>::iterator it = mAreas.begin(); it != mAreas.end(); ++it)
//	{
//		// If the creature has intersected with the area, then throw the plot device.
//		if(entity.isIntersecting(it->area))
//		{
//			pushEvent(EVENT_PLOTOCCURRENCE, KEYWORD_COLLISION_AREA + CHAR_DELIMITER_ALTERNATE + entity.getName() + CHAR_DELIMITER_ALTERNATE + it->name);
//		}
//	}
//}
//
//void EnvironmentData::eventOccurred(Event event, const std::string& content, CreatureMovedToPointListener* creatureMovedToPointListener)
//{
//	// Push the event to the level (or whomever else is listening).
//	pushEvent(event, content, creatureMovedToPointListener);
//}
//
//Entity* EnvironmentData::getEntity(unsigned int id)
//{
//	for(list<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
//	{
//		if((*it)->getId() == id)
//		{
//			return *it;
//		}
//	}
//	return 0;
//}
//
//Entity* EnvironmentData::getEntity(const string& name)
//{
//	for(list<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
//	{
//		if((*it)->getName() == name)
//		{
//			return *it;
//		}
//	}
//	return 0;
//}
//
//bool EnvironmentData::getLightingState() const
//{
//	return mLightingState;
//}
//
//const Vector& EnvironmentData::getOffset() const
//{
//	return mViewportOffset;
//}
//
//int EnvironmentData::getXOffset() const
//{
//	return mViewportOffset.x;
//}
//
//int EnvironmentData::getYOffset() const
//{
//	return mViewportOffset.y;
//}
//
//void EnvironmentData::load(const std::string& data)
//{
////	@todo need to implement loading the game.
//	Logger::warn("EnvironmentData::load() -> Not yet implemented.");
//}
//
//void EnvironmentData::logic()
//{
//	// Clear the lights.
//	mEllipseLights.clear();
//	mQuadLights.clear();
//
//    // Clear any entities set for removal.
//    mClearRemoved();
//
//	// Entity logic wuz here.
//
//    // Reorganize the sprites by their Z index.
//    mEntities.sort(sortByZIndex);
//}
//
//void EnvironmentData::removeEntity(const std::string& name)
//{
//	for(list<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); ++it)
//	{
//		if((*it)->getName() == name)
//		{
//			mRemoval.push_back(*it);
//		}
//	}
//}
//
//void EnvironmentData::setLightingState(bool state)
//{
//	mLightingState = state;
//}
//
//void EnvironmentData::setOffset(const Vector& offset)
//{
//	mViewportOffset = offset;
//}
