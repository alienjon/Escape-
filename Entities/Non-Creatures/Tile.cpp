/*
 * Tile.cpp
 *
 *  Created on: May 5, 2009
 *      Author: alienjon
 */
#include "Tile.hpp"

#include <string>

#include "../../Entities/EntityType.hpp"
#include "../../Engine/Logger.hpp"

using std::string;

const string TILE_NAME = "WALL TILE";

Tile::Tile() : Entity(TILE_NAME, 0, 0, Rectangle(0, 0, 0, 0)),
	mSurface(0)
{
	// Set the entity type.
	mType = ENTITY_TILE;
}

Tile::Tile(Surface* meta, const Rectangle& area) : Entity(TILE_NAME, 0, 0, area),
	mSurface(meta)

{
	// Set the entity type.
	mType = ENTITY_TILE;

    // If the surface wasn't provided then error.
    if(!mSurface)
    {
        Logger::warn("Null surface provided as the meta surface for a tile.");
    }
}

void Tile::draw(Renderer& renderer)
{
	if(mSurface)
	{
		const Rectangle& area = mGetCollisionArea();
		renderer.drawImage(mSurface, area.vector.x, area.vector.y, getX(), getY(), area.width, area.height);
	}
}

void Tile::logic()
{
	// Tiles don't perform logic.
}
