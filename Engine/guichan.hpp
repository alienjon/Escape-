/*      _______   __   __   __   ______   __   __   _______   __   __
 *     / _____/\ / /\ / /\ / /\ / ____/\ / /\ / /\ / ___  /\ /  |\/ /\
 *    / /\____\// / // / // / // /\___\// /_// / // /\_/ / // , |/ / /
 *   / / /__   / / // / // / // / /    / ___  / // ___  / // /| ' / /
 *  / /_// /\ / /_// / // / // /_/_   / / // / // /\_/ / // / |  / /
 * /______/ //______/ //_/ //_____/\ /_/ //_/ //_/ //_/ //_/ /|_/ /
 * \______\/ \______\/ \_\/ \_____\/ \_\/ \_\/ \_\/ \_\/ \_\/ \_\/
 *
 * Copyright (c) 2004 - 2008 Olof Naess�n and Per Larsson
 *
 *
 * Per Larsson a.k.a finalman
 * Olof Naess�n a.k.a jansem/yakslem
 *
 * Visit: http://guichan.sourceforge.net
 *
 * License: (BSD)
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of Guichan nor the names of its contributors may
 *    be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef GCN_GUICHAN_HPP
#define GCN_GUICHAN_HPP

#include "Guichan/actionevent.hpp"
#include "Guichan/actionlistener.hpp"
#include "Guichan/cliprectangle.hpp"
#include "Guichan/color.hpp"
#include "Guichan/deathlistener.hpp"
#include "Guichan/event.hpp"
#include "Guichan/exception.hpp"
#include "Guichan/focushandler.hpp"
#include "Guichan/focuslistener.hpp"
#include "Guichan/font.hpp"
#include "Guichan/genericinput.hpp"
#include "Guichan/graphics.hpp"
#include "Guichan/gui.hpp"
#include "Guichan/image.hpp"
#include "Guichan/imagefont.hpp"
#include "Guichan/imageloader.hpp"
#include "Guichan/input.hpp"
#include "Guichan/inputevent.hpp"
#include "Guichan/key.hpp"
#include "Guichan/keyevent.hpp"
#include "Guichan/keyinput.hpp"
#include "Guichan/keylistener.hpp"
#include "Guichan/listmodel.hpp"
#include "Guichan/mouseevent.hpp"
#include "Guichan/mouseinput.hpp"
#include "Guichan/mouselistener.hpp"
#include "Guichan/rectangle.hpp"
#include "Guichan/selectionevent.hpp"
#include "Guichan/selectionlistener.hpp"
#include "Guichan/widget.hpp"
#include "Guichan/widgetlistener.hpp"
#include "Guichan/widgets/button.hpp"
#include "Guichan/widgets/checkbox.hpp"
#include "Guichan/widgets/container.hpp"
#include "Guichan/widgets/dropdown.hpp"
#include "Guichan/widgets/icon.hpp"
#include "Guichan/widgets/imagebutton.hpp"
#include "Guichan/widgets/label.hpp"
#include "Guichan/widgets/listbox.hpp"
#include "Guichan/widgets/scrollarea.hpp"
#include "Guichan/widgets/slider.hpp"
#include "Guichan/widgets/radiobutton.hpp"
#include "Guichan/widgets/tab.hpp"
#include "Guichan/widgets/tabbedarea.hpp"
#include "Guichan/widgets/textbox.hpp"
#include "Guichan/widgets/textfield.hpp"
#include "Guichan/widgets/window.hpp"

#include "Guichan/platform.hpp"


class Widget;

extern "C"
{
    /**
     * Gets the the version of Guichan. As it is a C function
     * it can be used to check for Guichan with autotools.
     *
     * @return the version of Guichan.
     */
    extern const char* gcnGuichanVersion();
}

#endif // end GCN_GUICHAN_HPP
