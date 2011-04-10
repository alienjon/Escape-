/*
 * EntityType.cpp
 *
 *  Created on: May 17, 2010
 *      Author: the-saint
 */
#include "EntityType.hpp"

using std::string;

string getEntityType(EntityType type)
{
    switch(type)
    {
    	case ENTITY_CREATURE: return "ENTITY_CREATURE";
    	case ENTITY_PLAYER: return "ENTITY_PLAYER";
    	case ENTITY_NONDISPLAYING: return "ENTITY_NONDISPLAYING";
    	case ENTITY_EXPLOSION: return "ENTITY_EXPLOSION";
    	case ENTITY_OBJECT: return "ENTITY_OBJECT";
    	case ENTITY_ITEM: return "ENTITY_ITEM";
    	case ENTITY_TILE: return "ENTITY_TILE";
        default: return "NULL ENTITY TYPE";
    }
}

EntityType getEntityType(const string& type)
{
    if(type == "ENTITY_CREATURE")
    {
        return ENTITY_CREATURE;
    }
    else if(type == "ENTITY_PLAYER")
    {
        return ENTITY_PLAYER;
    }
    else if(type == "ENTITY_NONDISPLAYING")
    {
        return ENTITY_NONDISPLAYING;
    }
    else if(type == "ENTITY_EXPLOSION")
    {
    	return ENTITY_EXPLOSION;
    }
    else if(type == "ENTITY_OBJECT")
    {
    	return ENTITY_OBJECT;
    }
    else if(type == "ENTITY_ITEM")
    {
    	return ENTITY_ITEM;
    }
    else if(type == "ENTITY_TILE")
    {
    	return ENTITY_ITEM;
    }
    else
    {
        return ENTITY_NULL;
    }
}
