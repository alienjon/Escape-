/*
 * Keywords.cpp
 *
 *  Created on: Oct 31, 2011
 *      Author: alienjon
 */
#include "Keywords.hpp"

using std::string;

// These are the actions.
const string ACTION_SHOWCURSOR = "ACTION_SHOWCURSOR";
const string ACTION_HIDECURSOR = "ACTION_HIDECURSOR";
const string ACTION_PAUSE = "ACTION_PAUSE";
const string ACTION_TO_MAINMENU = "ACTION_TO_MAINMENU";
const string ACTION_SLIDE_CREDITSMENU = "ACTION_SLIDE_CREDITSMENU";
const string ACTION_SLIDE_MAINMENU = "ACTION_SLIDE_MAINMENU";
const string ACTION_SLIDE_NEWMENU = "ACTION_SLIDE_NEWMENU";
const string ACTION_SLIDE_OPTIONSMENU = "ACTION_SLIDE_OPTIONSMENU";
const string ACTION_SLIDE_STARTGAME = "ACTION_SLIDE_STARTGAME";
const string ACTION_STARTGAME_EASY = "ACTION_STARTGAME_EASY";
const string ACTION_STARTGAME_HARD = "ACTION_STARTGAME_HARD";
const string ACTION_STARTGAME_NORMAL = "ACTION_STARTGAME_NORMAL";
const string ACTION_UNPAUSE = "ACTION_UNPAUSE";
const string ACTION_QUIT = "ACTION_QUIT";

// Data information.
const string DATA_PLAYER = "Images/player.dat";

// These are the images.
const string IMAGE_DIRECTIONAL_ARROW_UP = "Images/arrow_up.png";
const string IMAGE_DIRECTIONAL_ARROW_DOWN = "Images/arrow_down.png";
const string IMAGE_DIRECTIONAL_ARROW_LEFT = "Images/arrow_left.png";
const string IMAGE_DIRECTIONAL_ARROW_RIGHT = "Images/arrow_right.png";
const string IMAGE_FASTPLAYER = "Images/fastplayer.png";
const string IMAGE_ITEM_NULLIFY = "Images/nullify.png";
const string IMAGE_ITEM_PHASE = "Images/phase.png";
const string IMAGE_KEY = "Images/key.png";
const string IMAGE_PICKUP = "Images/pickup.png";
const string IMAGE_PORTAL = "Images/portal.png";
const string IMAGE_FLIPSCREEN = "Images/rotate.png";
const string IMAGE_SLOWPLAYER = "Images/slowplayer.png";
const string IMAGE_SURPRISEPICKUP = "Images/questionmark.png";
const string IMAGE_TIMEGAIN	  = "Images/timegain.png";
const string IMAGE_TIMELOSS	  = "Images/timeloss.png";
const string IMAGE_ZOOMSCREEN = "Images/zoom.png";

// These are the fonts.
const string FONT_DEFAULT = "Fonts/VeraMono.ttf";
const string FONT_TEXT = "Fonts/VeraMono.ttf";
const string FONT_CAPTION = "Fonts/Perfect.ttf";

// These are the sounds.
const string SOUND_LEVELCOMPLETE_FINISH = "Audio/LevelComplete1.wav";
const string SOUND_LEVELCOMPLETE_ITEMDISPLAY = "Audio/rollover_10.wav";
const string SOUND_MENU_CLICK = "Audio/MenuButton.ogg";
const string SOUND_PICKUP = "Audio/rollover_5.wav";
const string SOUND_PICKUP_KEY = "Audio/rollover_6.wav";
const string SOUND_PICKUP_SPECIAL = "Audio/rollover_3.wav";
const string SOUND_SURPRISEPICKUP = "Audio/transport_collide.wav";
