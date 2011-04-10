/*
 * MapRule.cpp
 *
 *  Created on: Jun 19, 2009
 *      Author: alienjon
 */

#include "MapRule.hpp"

#include <stdexcept>

#include "../main.hpp"

using std::out_of_range;
using std::string;

MapRule::MapRule(const char* _tileset, uint m_w_mn, uint m_w_mx, uint m_h_mn, uint m_h_mx, uint mn_r, uint mx_r,
                 uint r_w_mn, uint r_w_mx, uint r_h_mn, uint r_h_mx, uint r_buf, uint r_d_mn, uint r_d_mx, bool _outdoors)
                : tileset(_tileset), map_width_min(m_w_mn), map_width_max(m_w_mx), map_height_min(m_h_mn), map_height_max(m_h_mx),
                min_rooms(mn_r), max_rooms(mx_r), room_width_min(r_w_mn), room_width_max(r_w_mx), room_height_min(r_h_mn),
                room_height_max(r_h_mx), room_buffer(r_buf), room_doors_min(r_d_mn), room_doors_max(r_d_mx), outdoors(_outdoors)
{
    // Just making sure that the lower values are, indeed, lower than the higher values.
    checkFlip(map_width_min, map_width_max);
    checkFlip(map_height_min, map_height_max);
    checkFlip(room_width_min, room_width_max);
    checkFlip(room_height_min, room_height_max);
    checkFlip(room_doors_min, room_doors_max);

    // Determine the width, height and number of rooms.
    map_width = random(map_width_min, map_width_max);
    map_height = random(map_height_min, map_height_max);
    rooms = random(min_rooms, max_rooms);
}

const MapRule& getMapRuleByLevel(unsigned int level)
{
    if(level < 5)
    {
        return MAPRULE_OFFICE_SMALL_FEW;
    }
    else if(level < 10)
    {
        return MAPRULE_OFFICE_SMALL_MOD;
    }
    else if(level < 15)
    {
        return MAPRULE_OFFICE_MEDIUM_MOD;
    }
    else if(level < 20)
    {
        return MAPRULE_OFFICE_MEDIUM_MOD;
    }
    else if(level < 25)
    {
        return MAPRULE_OFFICE_LARGE_MOD;
    }
    else if(level < 29)
    {
        return MAPRULE_OFFICE_LARGE_MANY;
    }
    else if(level == 30)
    {
        return MAPRULE_OFFICE_SMALL_MANY;
    }
    else
    {
        throw out_of_range("getMapRuleByLevel() -> Cannot have levels greater than 30.");
    }
}

const MapRule MAPRULE_OFFICE_SMALL_FEW("office", 60, 80, 20, 30, 8, 12, 2, 5, 2, 5, 3, 1, 2, true);
const MapRule MAPRULE_OFFICE_SMALL_MOD("office", 60, 80, 30, 40, 8, 12, 2, 5, 2, 5, 3, 1, 2, true);
const MapRule MAPRULE_OFFICE_SMALL_MANY("office", 60, 80, 50, 60, 8, 12, 2, 5, 2, 5, 3, 1, 2, true);
const MapRule MAPRULE_OFFICE_MEDIUM_FEW("office", 90, 120, 30, 40, 15, 25, 2, 6, 2, 6, 3, 1, 2, true);
const MapRule MAPRULE_OFFICE_MEDIUM_MOD("office", 90, 120, 30, 40, 15, 25, 2, 6, 2, 6, 3, 1, 2, true);
const MapRule MAPRULE_OFFICE_MEDIUM_MANY("office", 90, 120, 30, 40, 15, 25, 2, 6, 2, 6, 3, 1, 2, true);
const MapRule MAPRULE_OFFICE_LARGE_FEW("office", 120, 150, 50, 60, 50, 70, 2, 8, 2, 8, 3, 1, 2, true);
const MapRule MAPRULE_OFFICE_LARGE_MOD("office", 120, 150, 50, 60, 90, 110, 2, 8, 2, 8, 3, 1, 2, true);
const MapRule MAPRULE_OFFICE_LARGE_MANY("office", 120, 150, 50, 60, 110, 150, 2, 8, 2, 8, 3, 1, 2, true);
const MapRule MAPRULE_MENUSCREEN("office", 38, 38, 38, 38, 4, 8, 2, 4, 3, 5, 3, 1, 2, true);
