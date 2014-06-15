/*
 * This source file is part of libRocket, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://www.librocket.com
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "EventHandlerOptionsPreferences.h"
#include <Rocket/Core/Context.h>
#include <Rocket/Core/ElementDocument.h>
#include <Rocket/Core/ElementUtilities.h>
#include <Rocket/Core/Event.h>
#include <Rocket/Controls/ElementFormControlInput.h>
#include "../engine/EventManager.h"
//#include "GameDetails.h"
#include <stdlib.h>     /* atoi */
#include <iostream>
#include "Amos.h"
#include "legion.h"
#include "lgn_mapa.h"
#include "lgn_util.h"
#include "lgn_diskacs.h"
#include "EventHandlerOptions.h"
#include "../engine/Core.h"

EventHandlerOptionsPreferences::EventHandlerOptionsPreferences()
{
}

EventHandlerOptionsPreferences::~EventHandlerOptionsPreferences()
{
}

void EventHandlerOptionsPreferences::ProcessEvent(Rocket::Core::Event& event, const Rocket::Core::String& value)
{
    Rocket::Core::StringList values;
    Rocket::Core::StringUtilities::ExpandString(values, value, ' ');

    if (values.empty())
        return;

    if (values[0] == "restore")
    {
		Rocket::Core::ElementDocument* options_body = event.GetTargetElement()->GetOwnerDocument();
		if (options_body == NULL)
			return;

        Rocket::Controls::ElementFormControlInput* random_names = dynamic_cast< Rocket::Controls::ElementFormControlInput* >(options_body->GetElementById("random_names"));
		if (random_names != NULL)
		{
			if (PREFS[1] == 1)
				random_names->SetAttribute("checked", "");
			else
				random_names->RemoveAttribute("checked");
		}

        Rocket::Controls::ElementFormControlInput* fast_scrolling = dynamic_cast< Rocket::Controls::ElementFormControlInput* >(options_body->GetElementById("fast_scrolling"));
		if (fast_scrolling != NULL)
		{
			if (PREFS[2] == 1)
				fast_scrolling->SetAttribute("checked", "");
			else
				fast_scrolling->RemoveAttribute("checked");
		}

        Rocket::Controls::ElementFormControlInput* music = dynamic_cast< Rocket::Controls::ElementFormControlInput* >(options_body->GetElementById("music"));
		if (music != NULL)
		{
			if (PREFS[3] == 1)
				music->SetAttribute("checked", "");
			else
				music->RemoveAttribute("checked");
		}

        Rocket::Controls::ElementFormControlInput* dead_bodies = dynamic_cast< Rocket::Controls::ElementFormControlInput* >(options_body->GetElementById("dead_bodies"));
		if (dead_bodies != NULL)
		{
			if (PREFS[4] == 1)
				dead_bodies->SetAttribute("checked", "");
			else
				dead_bodies->RemoveAttribute("checked");
		}

        Rocket::Controls::ElementFormControlInput* windows_97 = dynamic_cast< Rocket::Controls::ElementFormControlInput* >(options_body->GetElementById("windows_97"));
		if (windows_97 != NULL)
		{
			if (PREFS[5] == 1)
				windows_97->SetAttribute("checked", "");
			else
				windows_97->RemoveAttribute("checked");
		}
    }
    else if (values[0] == "toggle_option")
    {
        int zone = atoi(values[1].CString());
        if (PREFS[zone] == 1)
        {
            if (event.GetTargetElement()->GetTagName() == "input")
            {
                event.GetTargetElement()->RemoveAttribute("checked");
            }
            else
            {
                event.GetTargetElement()->GetChild(0)->RemoveAttribute("checked");
            }
            PREFS[zone] = 0;
        }
        else
        {
            if (event.GetTargetElement()->GetTagName() == "input")
            {
                event.GetTargetElement()->SetAttribute("checked", "");
            }
            else
            {
                event.GetTargetElement()->GetChild(0)->SetAttribute("checked", "");
            }
            PREFS[zone] = 1;
        }
        if (zone == 3)
        {
            if (PREFS[zone] == 0)
            {
                _TRACK_FADE(1);																			//	                  _TRACK_FADE[1]
                Erase(3);
            }
            else
            {															//	               If STREFA=3
                _LOAD(KAT_S+"mod.legion","legion:mod.legion","Legion",6);//	                  _LOAD[KAT$+"mod.legion","legion:mod.legion","Legion",6]
                TrackLoop(true);
                TrackPlay(3);
            }
        }
    }
    else if (values[0] == "cancel")
    {
        if (EventManager::LoadWindow("options"))
        {
            event.GetTargetElement()->GetOwnerDocument()->Close();
        }
    }
}
