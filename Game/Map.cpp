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

#include "SDL/SDL.h"

#include "../Engine/Colors.hpp"
#include "../Game/Game.hpp"
#include "../Engine/Logger.hpp"
#include "../main.hpp"
#include "../Math/Point.hpp"
#include "../Managers/TilesetManager.hpp"
#include "../Managers/VideoManager.hpp"

using std::ostream;
using std::pair;
using std::runtime_error;
using std::stack;
using std::vector;

const unsigned int MAP_CELL_SIDE = 4; // The number of tiles on a single side of a cell - It has to be >= 3 and should be an even number (Because of the doors)

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
	mWidth(width),
	mHeight(height),
	mTileset(TilesetManager::getRandom())
{
	// Calculate the entrance position.
	mPortal = Vector((((mWidth / 2) * MAP_CELL_SIDE) + (MAP_CELL_SIDE / 2)) * mTileset->getWidth(),
					 (((mHeight/ 2) * MAP_CELL_SIDE) + (MAP_CELL_SIDE / 2)) * mTileset->getHeight());
	if(Game::isDebug())
		Logger::log("Portal(" + toString((mPortal.x * 2) / mTileset->getWidth() / MAP_CELL_SIDE) + ", " +
					toString((mPortal.y * 2) / mTileset->getHeight() / MAP_CELL_SIDE) + ")");

	// Begin by populating the map with closed cells.
	Cell cells[mHeight][mWidth];
	for(unsigned int y = 0; y != mHeight; y++)
		for(unsigned int x = 0; x != mWidth; x++)
			cells[y][x] = Cell();

	// The stuff needed to create a random map.
	unsigned int totalCells   = mWidth * mHeight,
				 visitedCells = 1;
	stack<Point> cellStack;
	Point currentCell(random<int>(0, mWidth - 1), random<int>(0, mHeight - 1));

	// Generate the map.
	while(visitedCells != totalCells)
	{
		// This list holds all neighboring cells that have not been visited (walls are all intact).
		std::vector<pair<Point, int> > neighborCells;
		pair<Point, int> pair;
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
			unsigned int pos = random<int>(0, neighborCells.size() - 1);

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
	{
		mMap.push_back(pair<Point, Rectangle>());
		mCollisions.push_back(CollisionArea());
	}

	int tile_width = mTileset->getWidth(), tile_height = mTileset->getHeight();
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
					mMap.at(pos).first.x = (cell_x * MAP_CELL_SIDE * tile_width) + (x * tile_width);
					mMap.at(pos).first.y = (cell_y * MAP_CELL_SIDE * tile_height)+ (y * tile_height);
					mMap.at(pos).second  = mTileset->getTile(tile);
					mCollisions.at(pos) = mTileset->getTileCollision(tile);
//					mCollisions.at(pos).vector.x = (cell_x * MAP_CELL_SIDE * tile_width) + (x * tile_width);
//					mCollisions.at(pos).vector.y = (cell_y * MAP_CELL_SIDE * tile_height) + (y * tile_height);
					mCollisions.at(pos).addX((cell_x * MAP_CELL_SIDE * tile_width) + (x * tile_width));
					mCollisions.at(pos).addY((cell_y * MAP_CELL_SIDE * tile_height) + (y * tile_height));
				}
			}
		}
	}

//	for(vector<Rectangle>::iterator it = mCollisions.begin(); it != mCollisions.end(); it++)
//	{
//		cout << "[";
//		for(unsigned int i = 0; i != it->getNumberOfPoints(); ++i)
//			cout << it->getPoint(i) << ", ";
//		cout << "]" << endl;
//	}
}

bool Map::checkCollision(const Quadrilateral& area) const
{
	return checkCollision(area.getBoundingBox());
}

bool Map::checkCollision(const Rectangle& area) const
{
	// The width of the map in tiles.
	unsigned int width_in_tiles = mWidth * MAP_CELL_SIDE;

	// Calculate the start and end x,y values.
	int start_y = area.vector.y / mTileset->getHeight() - 1,
		end_y   = (area.vector.y + area.height) / mTileset->getHeight() + 1,
		start_x = area.vector.x / mTileset->getWidth() - 1,
		end_x   = (area.vector.x + area.width) / mTileset->getWidth() + 1;

	// Correct for min,max.
	start_y = (start_y < 0) ? 0 : start_y;
	end_y   = ((unsigned int)end_y >= mHeight * MAP_CELL_SIDE) ? mHeight * MAP_CELL_SIDE : end_y;
	start_x = (start_x < 0) ? 0 : start_x;
	end_x   = (end_x >= (int)(mWidth * MAP_CELL_SIDE)) ? (int)(mWidth * MAP_CELL_SIDE) : end_x;

	for(int y = start_y; y != end_y; ++y)
		for(int x = start_x; x != end_x; ++x)
			if(mCollisions.at(x + y * width_in_tiles).isIntersecting(area))
				return true;
	return false;
}

Surface* Map::copyMapImage() const
{
	// Create a blank surface.
	Surface* destSurface = VideoManager::createSDL_Surface(getWidth(), getHeight());

	// Copy the map to the surface.
	unsigned int width_in_tiles = mWidth * MAP_CELL_SIDE;
	const Surface* srcSurface = mTileset->getTilesetSurface();
	SDL_Rect destArea, area;
	destArea.w = (Uint16)mTileset->getWidth();
	destArea.h = (Uint16)mTileset->getHeight();

	for(int y = 0; y != (int)(getHeight() / mTileset->getHeight());  ++y)
	{
		for(int x = 0; x != (int)(getWidth() / mTileset->getWidth()); ++x)
		{
			destArea.x = (Uint16)x * mTileset->getWidth();
			destArea.y = (Uint16)y * mTileset->getHeight();

			area.x = mMap.at(y * width_in_tiles + x).second.vector.x;
			area.y = mMap.at(y * width_in_tiles + x).second.vector.y;
			area.w = mMap.at(y * width_in_tiles + x).second.width;
			area.h = mMap.at(y * width_in_tiles + x).second.height;
			SDL_BlitSurface(srcSurface->getSurface(), &area, destSurface->getSurface(), &destArea);
		}
	}

	if(Game::isDebug())
		SDL_SaveBMP(destSurface->getSurface(), "minimap.bmp");
	return destSurface;
}

void Map::draw(Renderer& renderer, const Viewport& viewport)
{
	/*
	 * Based on the size of the viewport and its current location, calculate
	 * which tiles in this level will be drawn. Calculate some values ahead
	 * of time to save some time in the subsequent loop.
	 */
	const Surface* surface = mTileset->getTilesetSurface();
	unsigned int width_in_tiles = mWidth * MAP_CELL_SIDE;

	// Calculate the start and end x,y values.
	int start_y = viewport.getY() / mTileset->getHeight() - 1,
		end_y   = (viewport.getY() + viewport.getHeight()) / mTileset->getHeight() + 1,
		start_x = viewport.getX() / mTileset->getWidth() - 1,
		end_x   = (viewport.getX() + viewport.getWidth()) / mTileset->getWidth() + 1;

	// Correct for min,max.
	start_y = (start_y < 0) ? 0 : start_y;
	end_y   = ((unsigned int)end_y >= mHeight * MAP_CELL_SIDE) ? mHeight * MAP_CELL_SIDE : end_y;
	start_x = (start_x < 0) ? 0 : start_x;
	end_x   = (end_x >= (int)(mWidth * MAP_CELL_SIDE)) ? (int)(mWidth * MAP_CELL_SIDE) : end_x;

	for(int y = start_y; y != end_y; ++y)
	{
		for(int x = start_x; x != end_x; ++x)
		{
			Rectangle src = mMap.at(x + y * width_in_tiles).second;
			Point dest = mMap.at(x + y * width_in_tiles).first;
			Rectangle actual(dest.x, dest.y, src.width, src.height);
			renderer.drawImage(surface, src.vector.x, src.vector.y, dest.x, dest.y, src.width, src.height);

			// Draw the collision areas if testing.
			if(Game::isDebug())
			{
				renderer.setColor(COLOR_ORANGE);
				mCollisions.at(x + y * width_in_tiles).draw(renderer);
			}
		}
	}
}

unsigned int Map::getComplexity() const
{
	return mWidth * mHeight;
}

const Vector& Map::getPortal() const
{
	return mPortal;
}

const Tileset& Map::getTileset() const
{
	return *mTileset;
}

unsigned int Map::getHeight() const
{
	return mHeight * mTileset->getHeight() * MAP_CELL_SIDE;
}

unsigned int Map::getWidth() const
{
    return mWidth * mTileset->getWidth() * MAP_CELL_SIDE;
}

bool Map::isOnMap(int x, int y, int width, int height) const
{
    return x >= 0 && y >= 0 && x + width <= (int)getWidth() && y + height <= (int)getHeight();
}

bool Map::isOutOfBounds(const Rectangle& area) const
{
    return !isOnMap(area.vector.x, area.vector.y, area.width, area.height);
}
