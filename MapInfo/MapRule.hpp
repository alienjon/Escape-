/*
 * MapRule.hpp
 *
 *  Created on: Jun 19, 2009
 *      Author: alienjon
 */

#ifndef MAPRULE_HPP_
#define MAPRULE_HPP_

#include <string>

typedef unsigned int uint;

/**
 * A MapRule stores information for how a map should be created (map size, room size, etc...)
 * @todo Do I want to do indoor maps?
 */
struct MapRule
{
    /**
     * @brief A MapRule defines the properties to generate a map.
     * @param _tileset The name of the tileset to use.
     * @param m_w_mn The minimum possible width of the map.
     * @param m_w_mx The maximum possible width of the map.
     * @param m_h_mn The minimum possible height of the map.
     * @param m_h_mx The maximum possible height of the map.
     * @param mn_r The minimum possible rooms for this map.
     * @param mx_r The maximum possible rooms for this map.
     * @param r_w_mn The minimum possible room width.
     * @param r_w_mx The maximum possible room width.
     * @param r_h_mn The minimum possible room_height.
     * @param r_h_mx The maximum possible room_height.
     * @param r_buf The tile buffer required between rooms.
     * @param r_d_mn The minimum possible doors for a single room.
     * @param r_d_mx The maximum possible doors for a single room.
     * @param _outdoors True if this is an outdoor map. (default tiles are blank - indoor maps are dungeon-like)
     */
    MapRule(const char* _tileset, uint m_w_mn, uint m_w_mx, uint m_h_mn, uint m_h_mx, uint mn_r, uint mx_r,
            uint r_w_mn, uint r_w_mx, uint r_h_mn, uint r_h_mx, uint r_buf, uint r_d_mn, uint r_d_mx, bool _outdoors);

    // The maps tileset.
    std::string tileset;

    // The dimentions of the map.
    uint map_width_min, map_width_max, map_height_min, map_height_max;
    uint map_width, map_height; // The calculated size of the map.

    // The minimum and maximum number of rooms possible for this map.
    uint min_rooms, max_rooms;
    uint rooms; // The randomly determined number of rooms.

    // The room sizes.
    uint room_width_min, room_width_max, room_height_min, room_height_max;

    // The minimum distance between rooms.
    uint room_buffer;

    // The number of doors for the room.
    uint room_doors_min, room_doors_max;

    // If outdoors == true, then the map itself is empty of tiles and is filed with buildings (rooms)
    // If outdoors == false, then the map is filled with walls and a final check must be made to ensure that
    //  rooms all connect to each other (hallways)
    bool outdoors;
};

/**
 * @brief Retrieve the maprule for the requested level.
 * @param level The level whose maprule we want to retrieve.
 * @return A pre-determined maprule for the provided level.
 */
const MapRule& getMapRuleByLevel(unsigned int level);

extern const MapRule MAPRULE_OFFICE_SMALL_FEW;
extern const MapRule MAPRULE_OFFICE_SMALL_MOD;
extern const MapRule MAPRULE_OFFICE_SMALL_MANY;
extern const MapRule MAPRULE_OFFICE_MEDIUM_FEW;
extern const MapRule MAPRULE_OFFICE_MEDIUM_MOD;
extern const MapRule MAPRULE_OFFICE_MEDIUM_MANY;
extern const MapRule MAPRULE_OFFICE_LARGE_FEW;
extern const MapRule MAPRULE_OFFICE_LARGE_MOD;
extern const MapRule MAPRULE_OFFICE_LARGE_MANY;
extern const MapRule MAPRULE_MENUSCREEN;

#endif /* MAPRULE_HPP_ */
