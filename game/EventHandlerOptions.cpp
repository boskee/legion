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

#include "EventHandlerOptions.h"
#include <Rocket/Core/Context.h>
#include <Rocket/Core/ElementDocument.h>
#include <Rocket/Core/ElementUtilities.h>
#include <Rocket/Core/Event.h>
#include <Rocket/Controls/ElementFormControlInput.h>
#include "../engine/EventManager.h"
//#include "GameDetails.h"
#include <iostream>
#include "Amos.h"
#include "legion.h"
#include "lgn_mapa.h"
#include "lgn_opcje.h"
#include "lgn_diskacs.h"
#include "../engine/Core.h"
#include "lgn_util.h"
#include "utl_locale.h"

EventHandlerOptions::EventHandlerOptions()
{
}

EventHandlerOptions::~EventHandlerOptions()
{
}

void EventHandlerOptions::ProcessEvent(Rocket::Core::Event& event, const Rocket::Core::String& value)
{
    Rocket::Core::ElementDocument* options_body = event.GetTargetElement()->GetOwnerDocument();
    if (options_body == NULL)
        return;

    Rocket::Core::StringList values;
    Rocket::Core::StringUtilities::ExpandString(values, value, ' ');

    if (values.empty())
        return;

    if (values[0] == "restore")
    {
        Rocket::Core::Element* day_info = options_body->GetElementById("day_info");
		if (day_info != NULL)
		{
            astr SZMAL_S="",DZIEN_S="",DZIEN_TEXT="";
            SZMAL_S=Str_S(GRACZE[1][1]);				//	   SZMAL$=Str$(GRACZE(1,1))-" "
            DZIEN_S=Str_S(DZIEN);								//	   DZIEN$=Str$(DZIEN)-" "
            DZIEN_TEXT = GS("122")+DZIEN_S+GS("123")+SZMAL_S;
			Rocket::Core::ElementText *text_el = dynamic_cast< Rocket::Core::ElementText* >(day_info->GetFirstChild());
			text_el->SetText(DZIEN_TEXT.c_str());
		}
    } else if (values[0] == "stats")
    {
        options_body->Close();											//	            ZOKNO
        STATUS();											//	            STATUS
    }
    else if (values[0] == "save")
    {
        options_body->Close();											//	            ZOKNO
        _SAVE_GAME();									//	            _SAVE_GAME
    }
    else if (values[0] == "preferences")
    {									//	            ZOKNO
        if (EventManager::LoadWindow("options_preferences"))
        {
            options_body->Close();
        }
    }
    else if (values[0] == "cancel")
    {
        options_body->Close();
        EventManager::SetActiveHandler("map");
    }
    else if (values[0] == "end_game")
    {
        options_body->Close();
        EventManager::Shutdown();
        Core::Context->UnloadAllDocuments();

        REAL_KONIEC=-1;								//	            REAL_KONIEC=True
    }
}
