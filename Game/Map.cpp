/*
 * Map.cpp
 *
 *  Created on: May 5, 2009
 *      Author: alienjon
 */
#include "Map.hpp"

#include <fstream>
#include <stdexcept>
#include <stack>

#include "../Game/Game.hpp"
#include "../Engine/Logger.hpp"
#include "../main.hpp"
#include "../Game/Math.hpp"
#include "../Game/TilesetManager.hpp"

using std::ostream;
using std::pair;
using std::runtime_error;
using std::stack;
using std::vector;

// The number of tiles on a single side of a cell - It has to be >= 3 and should be an even number (Because of the doors)
const unsigned int MAP_CELL_SIDE = 4;

struct Cell
{
	Cell() :
		northWall(true),
		southWall(true),
		eastWall(true),
		westWall(true)
	{
	}

	bool wasVisited() const
	{
		return !northWall || !southWall || !eastWall || !westWall;
	}

	bool northWall, southWall, eastWall, westWall;
};

// This is used to save the map data to a file for external viewing.
ostream& operator<<(ostream& os, const Cell& cell)
{
	os << (cell.northWall ? '1' : '0')
	   << (cell.southWall ? '1' : '0')
	   << (cell.westWall ? '1' : '0')
	   << (cell.eastWall ? '1' : '0');
	return os;
}

Map::Map(unsigned int width, unsigned int height) :
	mWidth(width < 3 ? 3 : width),
	mHeight(height < 3 ? 3 : height),
	mTileset(TilesetManager::getRandom())
{
	// Begin by populating the map with closed cells.
	Cell cells[mHeight][mWidth];
	for(unsigned int y = 0; y != mHeight; y++)
		for(unsigned int x = 0; x != mWidth; x++)
			cells[y][x] = Cell();

	// The stuff needed to create a random map.
	unsigned int totalCells   = mWidth * mHeight,
				 visitedCells = 1;
	stack<sf::Vector2i> cellStack;
	sf::Vector2i currentCell(random((unsigned int)0, mWidth - 1), random((unsigned int)0, mHeight - 1));

	// Generate the map.
	while(visitedCells != totalCells)
	{
		// This list holds all neighboring cells that have not been visited (walls are all intact).
		std::vector<pair<sf::Vector2i, int> > neighborCells;
		pair<sf::Vector2i, int> pair;
		if(currentCell.y != 0 && !cells[currentCell.y - 1][currentCell.x].wasVisited()) // Up
		{
			pair.first.x = currentCell.x;
			pair.first.y = currentCell.y - 1;
			pair.second = 0;
			neighborCells.push_back(pair);
		}
		if(currentCell.y != (int)mHeight - 1 && !cells[currentCell.y + 1][currentCell.x].wasVisited()) // Down
		{
			pair.first.x = currentCell.x;
			pair.first.y = currentCell.y + 1;
			pair.second = 1;
			neighborCells.push_back(pair);
		}
		if(currentCell.x != 0 && !cells[currentCell.y][currentCell.x - 1].wasVisited()) // Left
		{
			pair.first.x = currentCell.x - 1;
			pair.first.y = currentCell.y;
			pair.second = 2;
			neighborCells.push_back(pair);
		}
		if(currentCell.x != (int)mWidth - 1 && !cells[currentCell.y][currentCell.x + 1].wasVisited()) // Right
		{
			pair.first.x = currentCell.x + 1;
			pair.first.y = currentCell.y;
			pair.second = 3;
			neighborCells.push_back(pair);
		}

		// If there is at least 1 neighboring cell then move there.
		if(!neighborCells.empty())
		{
			// Choose a neighbor at random.
			unsigned int pos = random(0, (int)neighborCells.size() - 1);

			// Based on the direction of the cell, knock down the appropriate walls.
			switch(neighborCells.at(pos).second)
			{
				case 0: // Up
				{
					cells[currentCell.y][currentCell.x].northWall = false;
					cells[neighborCells.at(pos).first.y][neighborCells.at(pos).first.x].southWall = false;
					currentCell.y--;
					break;
				}
				case 1: // Down
				{
					cells[currentCell.y][currentCell.x].southWall = false;
					cells[neighborCells.at(pos).first.y][neighborCells.at(pos).first.x].northWall = false;
					currentCell.y++;
					break;
				}
				case 2: // Left
				{
					cells[currentCell.y][currentCell.x].westWall = false;
					cells[neighborCells.at(pos).first.y][neighborCells.at(pos).first.x].eastWall = false;
					currentCell.x--;
					break;
				}
				case 3: // Right
				{
					cells[currentCell.y][currentCell.x].eastWall = false;
					cells[neighborCells.at(pos).first.y][neighborCells.at(pos).first.x].westWall = false;
					currentCell.x++;
					break;
				}
				default:
					throw runtime_error("Map::Map() -> Invalid direction provided.");
			}

			// Push the current cell onto the cell stack.
			cellStack.push(currentCell);

			// Add 1 to visited cells.
			visitedCells++;
		}
		// Otherwise, move back a cell in the stack.
		else
		{
			currentCell = cellStack.top();
			cellStack.pop();
		}
	}

	// If debugging, output the map for testing.
	if(Game::isDebug())
	{
		std::ofstream mapfile;
		mapfile.open("mapfile.txt", std::fstream::out | std::fstream::trunc);
		mapfile << mWidth << ',' << mHeight << "," << 0 << "," << 0 << "," << 0 << "," << 0 << ",";
		for(unsigned int y = 0; y != mHeight; ++y)
			for(unsigned int x = 0; x != mWidth; ++x)
				mapfile << cells[y][x];
	}

	// Populate the levels with the correct number of cells.
	for(unsigned int i = 0; i != (mWidth * MAP_CELL_SIDE) * (mHeight * MAP_CELL_SIDE); ++i)
		mMap.push_back(pair<sf::Sprite, CollisionArea>());

	int tile_width = mTileset.getWidth(), tile_height = mTileset.getHeight();
	unsigned int width_in_tiles = mWidth * MAP_CELL_SIDE;

	// Now create the rest of the tiles.
	for(int cell_y = 0; cell_y != (int)mHeight; ++cell_y)
	{
		for(int cell_x = 0; cell_x != (int)mWidth; ++cell_x)
		{
			// Single cells are square collections of tiles.
			for(int y = 0; y != (int)MAP_CELL_SIDE; ++y)
			{
				for(int x = 0; x != (int)MAP_CELL_SIDE; ++x)
				{
					// The current cell and the tile type.
					Cell cell = cells[cell_y][cell_x];
					Tileset::TileType tile = Tileset::EMPTYFLOOR;

					// This is the northwest corner of the cell.
					if(x == 0 && y == 0)
					{
						if(cell.northWall && cell.westWall)
							tile = Tileset::NORTHWEST;
						else if(cell.northWall && !cell.westWall)
							tile = Tileset::NORTH;
						else if(!cell.northWall && cell.westWall)
							tile = Tileset::WEST;
						else
							tile = Tileset::SOUTHEAST;
					}

					// This is the northeast corner of the cell.
					else if(x == MAP_CELL_SIDE - 1 && y == 0)
					{
						if(cell.northWall && cell.eastWall)
							tile = Tileset::NORTHEAST;
						else if(cell.northWall && !cell.eastWall)
							tile = Tileset::NORTH;
						else if(!cell.northWall && cell.eastWall)
							tile = Tileset::EAST;
						else
							tile = Tileset::SOUTHWEST;
					}

					// This is the southwest corner of the cell.
					else if(x == 0 && y == MAP_CELL_SIDE - 1)
					{
						if(cell.southWall && cell.westWall)
							tile = Tileset::SOUTHWEST;
						else if(cell.southWall && !cell.westWall)
							tile = Tileset::SOUTH;
						else if(!cell.southWall && cell.westWall)
							tile = Tileset::WEST;
						else
							tile = Tileset::NORTHEAST;
					}

					// This is the southeast corner of the cell.
					else if(x == MAP_CELL_SIDE - 1 && y == MAP_CELL_SIDE - 1)
					{
						if(cell.southWall && cell.eastWall)
							tile = Tileset::SOUTHEAST;
						else if(cell.southWall && !cell.eastWall)
							tile = Tileset::SOUTH;
						else if(!cell.southWall && cell.eastWall)
							tile = Tileset::EAST;
						else
							tile = Tileset::NORTHWEST;
					}

					// This is the north side of the cell.
					else if(y == 0 && cell.northWall)
						tile = Tileset::NORTH;

					// This is the south side of the cell.
					else if(y == MAP_CELL_SIDE - 1 && cell.southWall)
						tile = Tileset::SOUTH;

					// This is the west side of the cell.
					else if(x == 0 && cell.westWall)
						tile = Tileset::WEST;

					// This is the east side of the cell.
					else if(x == MAP_CELL_SIDE - 1 && cell.eastWall)
						tile = Tileset::EAST;

					// Configure the entries and collisions.
                    //{this places the tile in the cell}  {this moves the tile over within the cell block}
					unsigned int pos = (cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x);
					mMap.at(pos).first = mTileset.getTile(tile);
					mMap.at(pos).first.setPosition((cell_x * MAP_CELL_SIDE * tile_width) + (x * tile_width), (cell_y * MAP_CELL_SIDE * tile_height)+ (y * tile_height));
					mMap.at(pos).second = mTileset.getTileCollision(tile);
					mMap.at(pos).second.setPosition((cell_x * MAP_CELL_SIDE * tile_width) + (x * tile_width),
													(cell_y * MAP_CELL_SIDE * tile_height) + (y * tile_height));
				}
			}
		}
	}
}

bool Map::checkCollision(const sf::FloatRect& area) const
{
	// The width of the map in tiles.
	unsigned int width_in_tiles = mWidth * MAP_CELL_SIDE;

	// Calculate the start and end x,y values.
	int start_y = (area.top				 / mTileset.getHeight()) - 1,
		end_y   = ((area.top + area.height) / mTileset.getHeight()) + 1,
		start_x = ((area.left)			 / mTileset.getWidth())  - 1,
		end_x   = ((area.left + area.width) / mTileset.getWidth())  + 1;

	// Correct for min,max.
	start_y = (start_y < 0) ? 0 : start_y;
	end_y   = ((unsigned int)end_y >= mHeight * MAP_CELL_SIDE) ? mHeight * MAP_CELL_SIDE : end_y;
	start_x = (start_x < 0) ? 0 : start_x;
	end_x   = (end_x >= (int)(mWidth * MAP_CELL_SIDE)) ? (int)(mWidth * MAP_CELL_SIDE) : end_x;

	for(int y = start_y; y != end_y; ++y)
		for(int x = start_x; x != end_x; ++x)
			if(mMap.at(x + y * width_in_tiles).second.isIntersecting(area))
				return true;
	return false;
}

void Map::draw(sf::RenderWindow& renderer)
{
	/* Only draw tiles in the bounds of the screen */
	// Calculate the start and end x,y values.
	unsigned int width_in_tiles = mWidth * MAP_CELL_SIDE;
	sf::Vector2f pos = renderer.getView().getCenter(),
				 siz = renderer.getView().getSize();
	int start_x = (pos.x - (siz.x / 2)) / mTileset.getWidth() - 1,
	    end_x   = (pos.x + (siz.x / 2)) / mTileset.getWidth() + 1,
		start_y = (pos.y - (siz.y / 2)) / mTileset.getHeight() - 1,
		end_y   = (pos.y + (siz.y / 2)) / mTileset.getHeight() + 1;

	// Correct for min, max.
	start_y = (start_y < 0) ? 0 : start_y;
	end_y   = ((unsigned int)end_y >= mHeight * MAP_CELL_SIDE) ? mHeight * MAP_CELL_SIDE : end_y;
	start_x = (start_x < 0) ? 0 : start_x;
	end_x   = (end_x >= (int)(mWidth * MAP_CELL_SIDE)) ? (int)(mWidth * MAP_CELL_SIDE) : end_x;

	// Draw the tiles in the determined area.
	for(int y = start_y; y != end_y; ++y)
		for(int x = start_x; x != end_x; ++x)
			renderer.draw(mMap.at(x + y * width_in_tiles).first);
}

unsigned int Map::getComplexity() const
{
	return mWidth * mHeight;
}

const Tileset& Map::getTileset() const
{
	return mTileset;
}

unsigned int Map::getHeight() const
{
	return mHeight * mTileset.getHeight() * MAP_CELL_SIDE;
}

unsigned int Map::getWidth() const
{
    return mWidth * mTileset.getWidth() * MAP_CELL_SIDE;
}
