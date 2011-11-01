/*
 * CreditsMenu.cpp
 *
 *  Created on: Jul 1, 2009
 *      Author: alienjon
 */
#include "CreditsMenu.hpp"

#include "../../Game/Keywords.hpp"
#include "../MenuScreen.hpp"
#include "../../Managers/VideoManager.hpp"

CreditsMenu::CreditsMenu() : mBackButton(ID_MAINMENU_BUTTON_MAIN)
{
    // Set and configure the credits.
    mText.setText("CODING CREDITS");
     mText.addRow("Jonathan Rosen    - I did 99.9% of the code, design,");
     mText.addRow("                    and management as well as some");
     mText.addRow("                    media content.");
     mText.addRow("Accelerated C++   - Used some code from this book. It");
     mText.addRow("                    was also great in helping me");
     mText.addRow("                    understand new concepts.");
     mText.addRow("Lazy Foo          - I studied several of the Lazy Foo");
     mText.addRow("                    tutorials and some code is");
     mText.addRow("                    mimicked in that, such as the");
     mText.addRow("                    tiling tutorial");
     mText.addRow("René Nyffenegger  - I made my own base64 code but his");
     mText.addRow("                    works better:");
     mText.addRow("                    adp-gmbh.ch/cpp/common/base64.html");
     mText.addRow("blackspawn        - Some geometrical code (for");
     mText.addRow("                    triangle calculation came from");
     mText.addRow("                    his site: www.blackspwan.com");
     mText.addRow("");
     mText.addRow("GRAPHICS CREDITS");
     mText.addRow("Reiner`s Tilesets - Great site for 2d graphics. URL is");
     mText.addRow("                    reinerstileset.4players.de");
     mText.addRow("The GIMP          - All of my poor excuses for artwork");
     mText.addRow("                    was done in good excuse of a");
     mText.addRow("                    program, The GIMP.  Fonts used");
     mText.addRow("                    from The GIMP include 'Marked Fool'");
     mText.addRow("                    and 'It Wasn't Me'.");
     mText.addRow("");
     mText.addRow("AUDIO CREDITS");
     mText.addRow("Tribe of Noise    - An excellent site for musical");
     mText.addRow("                    artists to freely express their");
     mText.addRow("                    work. Site URL is");
     mText.addRow("                    www.tribeofnoise.com");
     mText.addRow("Intelligence      - Tribe of Noise member who");
     mText.addRow("                    contributed Anitras Dance.");
     mText.addRow("RubX Project      - Tribe of Noise member who");
     mText.addRow("                    contributed Human Drums.");
     mText.addRow("Partners in Rhyme - Several menu sound effects.");
     mText.addRow("opengameart.org   - Obtained several sound effects.");
     mText.addRow("                    I would specifically like to note");
     mText.addRow("                    some sounds from Michel Baradari.");
     mText.addRow("Mike Koenig       - Created fizzle.wav.  It was found at");
     mText.addRow("                    http://soundbible.com/1308-Fizzle.html");
     mText.addRow("Stephan           - Created creaking_door.wav.  It was found");
     mText.addRow("                    at:");
     mText.addRow("                    http://soundbible.com/1362-Old-Door-Creaking.html");
     mText.addRow("Matthew Newman    - Created grunt.wav.  Downloaded from:");
     mText.addRow("                    http://opengameart.org/content/vocal-grunts-tribeewav");
     mText.setEditable(false);
    mText.setOpaque(false);

    // Configure the scroll area to be of a set size and show the text.
    mScrollArea.setContent(&mText);
    mScrollArea.setScrollPolicy(gcn::ScrollArea::SHOW_NEVER, gcn::ScrollArea::SHOW_ALWAYS);
    mScrollArea.setSize(mText.getWidth() + mScrollArea.getScrollbarWidth(), 350);
    mScrollArea.setBaseColor(getBaseColor());
    mScrollArea.setBackgroundColor(COLOR_MENU_LIGHT);
    mScrollArea.setFrameSize(2);
    add(&mScrollArea, (getWidth() / 2) - (mScrollArea.getWidth() / 2), 150);

    // Place the button in the lower right corner.
    add(&mBackButton, getWidth() - mBackButton.getWidth() - 5, getHeight() - mBackButton.getHeight() - 5);
    mBackButton.setActionEventId(ACTION_SLIDE_MAINMENU);
    mBackButton.addActionListener(this);
}

CreditsMenu::~CreditsMenu()
{
    remove(&mScrollArea);
    remove(&mBackButton);

    mBackButton.removeActionListener(this);
}
