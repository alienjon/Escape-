/*
 * Tileset.cpp
 *
 *  Created on: May 25, 2009
 *      Author: alienjon
 */
#include "Tileset.hpp"

#include <stdexcept>

#include "../main.hpp"
#include "../Engine/VideoManager.hpp"

using std::map;
using std::runtime_error;
using std::string;

Tileset::Tileset(const string& filename, unsigned int width, unsigned int height) :
	mWidth(width),
	mHeight(height)
{
	// Calculate the width and height.
	sf::Texture meta;// = VideoManager::getTexture(filename);
//	mWidth  = meta.getSize().x / 3;//meta.getLocalBounds().width / 3;@todo cleanup?
//	mHeight = meta.getSize().y / 3;	//meta.getLocalBounds().height / 3;@todo cleanup?

	// Create the map areas.
	meta.loadFromFile(filename, sf::IntRect(0, 0, mWidth, mHeight));
	mTiles[NORTHWEST] = meta.copyToImage();//sf::Sprite(VideoManager::getTexture(filename));
//	mTiles[NORTHWEST].setTextureRect(sf::IntRect(0, 0, mWidth, mHeight));

	meta.loadFromFile(filename, sf::IntRect(mWidth, mHeight * 2, mWidth, mHeight));
	mTiles[NORTH] = meta.copyToImage();//sf::Sprite(VideoManager::getTexture(filename));
//	mTiles[NORTH].setTextureRect(sf::IntRect(mWidth, mHeight * 2, mWidth, mHeight));

	meta.loadFromFile(filename, sf::IntRect(mWidth * 2, 0, mWidth, mHeight));
	mTiles[NORTHEAST] = meta.copyToImage();//sf::Sprite(VideoManager::getTexture(filename));
//	mTiles[NORTHEAST].setTextureRect(sf::IntRect(mWidth * 2, 0, mWidth, mHeight));

	meta.loadFromFile(filename, sf::IntRect(0, mHeight, mWidth, mHeight));
	mTiles[WEST] = meta.copyToImage();//sf::Sprite(VideoManager::getTexture(filename));
//	mTiles[WEST].setTextureRect(sf::IntRect(0, mHeight, mWidth, mHeight));

	meta.loadFromFile(filename, sf::IntRect(mWidth * 2, mHeight, mWidth, mHeight));
	mTiles[EAST] = meta.copyToImage();//sf::Sprite(VideoManager::getTexture(filename));
//	mTiles[EAST].setTextureRect(sf::IntRect(mWidth * 2, mHeight, mWidth, mHeight));

	meta.loadFromFile(filename, sf::IntRect(0, mHeight * 2, mWidth, mHeight));
	mTiles[SOUTHWEST] = meta.copyToImage();//sf::Sprite(VideoManager::getTexture(filename));
//	mTiles[SOUTHWEST].setTextureRect(sf::IntRect(0, mHeight * 2, mWidth, mHeight));

	meta.loadFromFile(filename, sf::IntRect(mWidth, 0, mWidth, mHeight));
	mTiles[SOUTH] = meta.copyToImage();//sf::Sprite(VideoManager::getTexture(filename));
//	mTiles[SOUTH].setTextureRect(sf::IntRect(mWidth, 0, mWidth, mHeight));

	meta.loadFromFile(filename, sf::IntRect(mWidth * 2, mHeight * 2, mWidth, mHeight));
	mTiles[SOUTHEAST] = meta.copyToImage();//sf::Sprite(VideoManager::getTexture(filename));
//	mTiles[SOUTHEAST].setTextureRect(sf::IntRect(mWidth * 2, mHeight * 2, mWidth, mHeight));

	sf::Image emptyfloor;
	emptyfloor.create(mWidth, mHeight, sf::Color(0, 0, 0, 0));
	mTiles[EMPTYFLOOR]= emptyfloor;//sf::Sprite(VideoManager::getTexture(filename));
//	mTiles[EMPTYFLOOR].setTextureRect(sf::IntRect(0, 0, 0, 0));

	/* Create the collision areas based on the width of the collision area. */
	int col_size = 8; // @todo Should this be fixed or set with the tileset?
	// The empty floor.
	CollisionArea area;
	mCollisions[EMPTYFLOOR]= area;
	sf::FloatRect rect;

	// The north wall.
	area = CollisionArea();
	area.add(sf::FloatRect(0, (mHeight / 2) - (col_size / 2), mWidth, col_size));
	mCollisions[NORTH] = area;

	// The south wall.
	area = CollisionArea();
	area.add(sf::FloatRect(0, (mHeight / 2) - (col_size / 2), mWidth, col_size));
	mCollisions[SOUTH] = area;

	// The west wall.
	area = CollisionArea();
	area.add(sf::FloatRect((mWidth / 2) - (col_size / 2), 0, col_size, mHeight));
	mCollisions[WEST] = area;

	// The east wall.
	area = CollisionArea();
	area.add(sf::FloatRect((mWidth / 2) - (col_size / 2), 0, col_size, mHeight));
	mCollisions[EAST] = area;

	// The northwest wall.
	area = CollisionArea();
	area.add(sf::FloatRect((mWidth / 2) - (col_size / 2), (mHeight / 2) - (col_size / 2), (mWidth / 2) + (col_size / 2), col_size));
	area.add(sf::FloatRect((mWidth / 2) - (col_size / 2), (mHeight / 2) - (col_size / 2), col_size, (mHeight / 2) + (col_size / 2)));
	mCollisions[NORTHWEST] = area;

	// The northeast wall.
	area = CollisionArea();
	area.add(sf::FloatRect(0, (mHeight / 2) - (col_size / 2), (mWidth / 2) + (col_size / 2), col_size));
	area.add(sf::FloatRect((mWidth / 2) - (col_size / 2), (mHeight / 2) - (col_size / 2), col_size, (mHeight / 2) + (col_size / 2)));
	mCollisions[NORTHEAST] = area;

	// The southeast wall.
	area = CollisionArea();
	area.add(sf::FloatRect((mWidth / 2) - (col_size / 2), 0, col_size, (mHeight / 2) + (col_size / 2)));
	area.add(sf::FloatRect(0, (mHeight / 2) - (col_size / 2), (mWidth / 2) + (col_size / 2), col_size));
	mCollisions[SOUTHEAST] = area;

	// The southwest wall.
	area = CollisionArea();
	area.add(sf::FloatRect((mWidth / 2) - (col_size / 2), 0, col_size, (mHeight / 2) + (col_size / 2)));
	area.add(sf::FloatRect((mWidth / 2) - (col_size / 2), (mHeight / 2) - (col_size / 2), (mWidth / 2) + (col_size / 2), col_size));
	mCollisions[SOUTHWEST] = area;
}

const sf::Image& Tileset::getTile(Tileset::TileType type) const
{
	map<Tileset::TileType, sf::Image>::const_iterator it = mTiles.find(type);
	if(it == mTiles.end())
		throw runtime_error("Tileset::getTile() -> Invalid tile type provided.");
	return it->second;
}

const CollisionArea& Tileset::getTileCollision(Tileset::TileType type) const
{
	map<Tileset::TileType, CollisionArea>::const_iterator it = mCollisions.find(type);
	if(it == mCollisions.end())
		throw runtime_error("Tileset::getTileCollision() -> Invalid tile type provided.");
	return it->second;
}
