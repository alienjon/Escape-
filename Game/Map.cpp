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

#include "../Engine/Colors.hpp"
#include "../Game/Game.hpp"
#include "../Engine/Logger.hpp"
#include "../main.hpp"
#include "../Math/Point.hpp"
#include "../Game/TileLevel.hpp"
#include "../Game/TileType.hpp"

using std::ostream;
using std::pair;
using std::runtime_error;
using std::stack;
using std::vector;

#include <iostream>
using namespace std;//@todo remove when done testing

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

void Map::mDrawLevel(Renderer& renderer, const Viewport& viewport, vector<pair<Point, Rectangle> >& tiles, int end_y)
{
	/*
	 * Based on the size of the viewport and its current location, calculate
	 * which tiles in this level will be drawn. Calculate some values ahead
	 * of time to save some time in the subsequent loop.
	 */
	const Surface* surface = mTileset->getTilesetSurface();
	unsigned int width_in_tiles = mWidth * MAP_CELL_SIDE;

	// Calculate the start and end x,y values.
	int start_y = (end_y < 0) ? viewport.getY() / mTileset->getHeight() - 1 : end_y;
	end_y = (end_y < 0) ? (viewport.getY() + viewport.getHeight()) / mTileset->getHeight() + 1: end_y + 1; // The +1 compensates for the first Y layer of floor tiles.
	int start_x = viewport.getX() / mTileset->getWidth() - 1,
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
			Rectangle src = tiles.at(x + y * width_in_tiles).second;
			Point dest = tiles.at(x + y * width_in_tiles).first;
			Rectangle actual(dest.x, dest.y, src.width, src.height);
			renderer.drawImage(surface, src.vector.x, src.vector.y, dest.x, dest.y, src.width, src.height);
		}
	}
}

Map::Map(unsigned int width, unsigned int height, const Tileset* tileset) :
	mWidth(width),
	mHeight(height),
	mTileset(tileset)
{
	// Make sure the tileset was provided.
	if(!mTileset)
	{
		throw runtime_error("Map::Map() -> Null tileset provided.");
	}

	// Begin by populating the map with closed cells.
	Cell cells[mHeight][mWidth];
	for(unsigned int y = 0; y != mHeight; y++)
	{
		for(unsigned int x = 0; x != mWidth; x++)
		{
			cells[y][x] = Cell();
		}
	}

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
		{
			for(unsigned int x = 0; x != mWidth; ++x)
			{
				mapfile << cells[y][x];
			}
		}
	}

	// Populate the levels with the correct number of cells.
	for(unsigned int i = 0; i != (mWidth * MAP_CELL_SIDE) * (mHeight * MAP_CELL_SIDE + 1); ++i)
	{
		mLMap.push_back(pair<Point, Rectangle>());
		mMMap.push_back(pair<Point, Rectangle>());
		mU1Map.push_back(pair<Point, Rectangle>());
		mU2Map.push_back(pair<Point, Rectangle>());
		mU3Map.push_back(pair<Point, Rectangle>());
		mCollisionAreas.push_back(Quadrilateral());
	}

	int tile_width = mTileset->getWidth(), tile_height = mTileset->getHeight();
	unsigned int width_in_tiles = mWidth * MAP_CELL_SIDE;

	// These are the cell locations for the entrance and exit.
	Point entrance(random<int>(0, mWidth - 1), random<int>(0, mHeight - 1)), exit(random<int>(0, mWidth - 1), random<int>(0, mHeight - 1));
	while(!cells[entrance.y][entrance.x].northWall)
		entrance = Point(random<int>(0, mWidth - 1), random<int>(0, mHeight - 1));
	mEntranceLocation.x = (entrance.x * MAP_CELL_SIDE * tile_width) + (tile_width * 2);
	mEntranceLocation.y = (entrance.y * MAP_CELL_SIDE * tile_height)+ (2.5 * tile_height); //@todo review

//@todo need to make sure that the entrance and exit are not within 1/3 of the map from each other
//		int third_width = mWidth / 3, third_height = mHeight / 3;
//			(exit.x > entrance.x - third_width) && (exit.x < entrance.x + third_width) &&
//		  (exit.y > entrance.y - third_height) && (exit.y < entrance.y + third_height) &&
	while(!cells[exit.y][exit.x].northWall)
		exit = Point(random<int>(0, mWidth - 1), random<int>(0, mHeight - 1));
	int exitareaheight = 4;
	mExitArea.vector.x = (exit.x * MAP_CELL_SIDE * tile_width) + (tile_width);
	mExitArea.vector.y = (exit.y * MAP_CELL_SIDE * tile_height)+ (2 * tile_height - exitareaheight);//@todo review
	mExitArea.width	   = tile_width * 2;
	mExitArea.height   = exitareaheight;

cout << "entrance->" << entrance << " - " << "exit->" << exit << endl;//@todo remove when done

	// Now create the rest of the tiles.
	for(unsigned int cell_y = 0; cell_y != mHeight; ++cell_y)
	{
		for(unsigned int cell_x = 0; cell_x != mWidth; ++cell_x)
		{
			// Single cells are square collections of tiles.
			for(unsigned int y = 0; y != MAP_CELL_SIDE; ++y)
			{
				for(unsigned int x = 0; x != MAP_CELL_SIDE; ++x)
				{
					// The current cell and the tile type.
					Cell cell = cells[cell_y][cell_x];
					TileType tile = TILE_EMPTYFLOOR;

					// If this cell is the entrance or exit, and if this is the second or third tile in those cells, put in the door.
					if((((int)cell_x == entrance.x && (int)cell_y == entrance.y) || ((int)cell_x == exit.x && (int)cell_y == exit.y)) && y == 0 && (x == 1 || x == 2))
					{
						if(x == 1)
						{
							tile = TILE_CLOSEDDOOR_WEST;
						}
						else if(x == 2)
						{
							tile = TILE_CLOSEDDOOR_EAST;
						}
					}

					// This is the northwest corner of the cell.
					else if(x == 0 && y == 0)
					{
						if(cell.northWall && cell.westWall)
							tile = TILE_CORNER_NORTHWEST;
						else if(cell.northWall && !cell.westWall)
							tile = TILE_NORTH;
						else if(!cell.northWall && cell.westWall)
							tile = TILE_WEST;
						else
							tile = TILE_CORNER_SOUTHEAST;
					}

					// This is the northeast corner of the cell.
					else if(x == MAP_CELL_SIDE - 1 && y == 0)
					{
						if(cell.northWall && cell.eastWall)
							tile = TILE_CORNER_NORTHEAST;
						else if(cell.northWall && !cell.eastWall)
							tile = TILE_NORTH;
						else if(!cell.northWall && cell.eastWall)
							tile = TILE_EAST;
						else
							tile = TILE_CORNER_SOUTHWEST;
					}

					// This is the southwest corner of the cell.
					else if(x == 0 && y == MAP_CELL_SIDE - 1)
					{
						if(cell.southWall && cell.westWall)
							tile = TILE_CORNER_SOUTHWEST;
						else if(cell.southWall && !cell.westWall)
							tile = TILE_SOUTH;
						else if(!cell.southWall && cell.westWall)
							tile = TILE_WEST;
						else
							tile = TILE_CORNER_NORTHEAST;
					}

					// This is the southeast corner of the cell.
					else if(x == MAP_CELL_SIDE - 1 && y == MAP_CELL_SIDE - 1)
					{
						if(cell.southWall && cell.eastWall)
							tile = TILE_CORNER_SOUTHEAST;
						else if(cell.southWall && !cell.eastWall)
							tile = TILE_SOUTH;
						else if(!cell.southWall && cell.eastWall)
							tile = TILE_EAST;
						else
							tile = TILE_CORNER_NORTHWEST;
					}

					// This is the north side of the cell.
					else if(y == 0 && cell.northWall)
						tile = TILE_NORTH;

					// This is the south side of the cell.
					else if(y == MAP_CELL_SIDE - 1 && cell.southWall)
						tile = TILE_SOUTH;

					// This is the west side of the cell.
					else if(x == 0 && cell.westWall)
						tile = TILE_WEST;

					// This is the east side of the cell.
					else if(x == MAP_CELL_SIDE - 1 && cell.eastWall)
						tile = TILE_EAST;

					// Configure the entries and collisions.
					//                {this places the tile in the cell}  {this moves the tile over within the cell block}
					mLMap.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).first.x = (cell_x * MAP_CELL_SIDE * tile_width) + (x * tile_width);
					mLMap.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).first.y = (cell_y * MAP_CELL_SIDE * tile_height)+ (y * tile_height) +  (1 * tile_height);
					mLMap.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).second  = mTileset->getTile(tile, TILELEVEL_LOWER);
					mMMap.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).first.x = (cell_x * MAP_CELL_SIDE * tile_width) + (x * tile_width);
					mMMap.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).first.y = (cell_y * MAP_CELL_SIDE * tile_height)+ (y * tile_height) +  (1 * tile_height);
					mMMap.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).second  = mTileset->getTile(tile, TILELEVEL_MIDDLE);
					mU1Map.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).first.x = (cell_x * MAP_CELL_SIDE * tile_width) + (x * tile_width);
					mU1Map.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).first.y = (cell_y * MAP_CELL_SIDE * tile_height)+ (y * tile_height) + (0 * tile_height);
					mU1Map.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).second  = mTileset->getTile(tile, TILELEVEL_UPPER1);
					mU2Map.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).first.x = (cell_x * MAP_CELL_SIDE * tile_width) + (x * tile_width);
					mU2Map.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).first.y = (cell_y * MAP_CELL_SIDE * tile_height)+ (y * tile_height) - (1 * tile_height);
					mU2Map.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).second  = mTileset->getTile(tile, TILELEVEL_UPPER2);
					mU3Map.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).first.x = (cell_x * MAP_CELL_SIDE * tile_width) + (x * tile_width);
					mU3Map.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).first.y = (cell_y * MAP_CELL_SIDE * tile_height)+ (y * tile_height) - (2 * tile_height);
					mU3Map.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).second  = mTileset->getTile(tile, TILELEVEL_UPPER3);
					mCollisionAreas.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)) = mTileset->getTileCollision(tile);
					mCollisionAreas.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).p1.x += mLMap.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).first.x;
					mCollisionAreas.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).p1.y += mLMap.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).first.y;
					mCollisionAreas.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).p2.x += mLMap.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).first.x;
					mCollisionAreas.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).p2.y += mLMap.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).first.y;
					mCollisionAreas.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).p3.x += mLMap.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).first.x;
					mCollisionAreas.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).p3.y += mLMap.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).first.y;
					mCollisionAreas.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).p4.x += mLMap.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).first.x;
					mCollisionAreas.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).p4.y += mLMap.at((cell_y * MAP_CELL_SIDE + y) * width_in_tiles + (cell_x * MAP_CELL_SIDE + x)).first.y;
				}
			}
		}
	}
}

bool Map::checkCollision(const Quadrilateral& area) const
{
	return checkCollision(area.getBoundingBox());
}

bool Map::checkCollision(const Rectangle& area) const
{
	for(vector<Quadrilateral>::const_iterator it = mCollisionAreas.begin(); it != mCollisionAreas.end(); it++)
		if(it->isIntersecting(area))
			return true;
	return false;
}

void Map::drawLower(Renderer& renderer, const Viewport& viewport)
{
	// The map is shifted down to see the upper layers of the top Y level.  This leaves a blank 'dead' space
	//  in the top Y level that needs to be covered up.  If the upper part of the viewport is in this area, draw that area.
	if((int)mTileset->getHeight() > viewport.getY())
	{
		renderer.setColor(COLOR_BLACK);
		renderer.fillRectangle(Rectangle(0, 0, viewport.getWidth() + viewport.getX(), mTileset->getHeight() - viewport.getY()));
	}

	mDrawLevel(renderer, viewport, mLMap);
}

void Map::drawMiddle(Renderer& renderer, const Viewport& viewport, int end_y)
{
	mDrawLevel(renderer, viewport, mMMap, end_y);
}

void Map::drawUpper(Renderer& renderer, const Viewport& viewport)
{
	mDrawLevel(renderer, viewport, mU1Map);
	renderer.setColor(COLOR_RED);//@todo remove when done
	renderer.fillRectangle(mExitArea);
//	mDrawLevel(renderer, viewport, mU2Map);
//	mDrawLevel(renderer, viewport, mU3Map);
}

const Vector& Map::getEntrance() const
{
	return mEntranceLocation;
}

const Tileset& Map::getTileset() const
{
	return *mTileset;
}

const Rectangle& Map::getExit() const
{
	return mExitArea;
}

unsigned int Map::getHeight() const
{
    return (mHeight * MAP_CELL_SIDE + 1) * mTileset->getHeight();
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
