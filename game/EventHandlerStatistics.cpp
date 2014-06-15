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

#include "EventHandlerStatistics.h"
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
#include "utl_locale.h"

EventHandlerStatistics::EventHandlerStatistics()
{
}

EventHandlerStatistics::~EventHandlerStatistics()
{
}

void EventHandlerStatistics::ProcessEvent(Rocket::Core::Event& event, const Rocket::Core::String& value)
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
            astr DZIEN_TEXT="";

					//	Procedure STATUS
            aint A=0, AM=0, I=0, WOJ=0, M=0, MS=0, LUDZIE=0, POD=0,
                     RES=0;
            astr KON_S="", KON2_S="", A_S="";

            for( A=0; A<=19; ++A ) {																			//	   For A=0 To 19
                if( ARMIA[A][0][TE]>0 ) {																		//	      If ARMIA(A,0,TE)>0
                    AM++;																											//	         Inc AM
                    for( I=1; I<=10; ++I ) {																	//	         For I=1 To 10
                        if( ARMIA[A][I][TE]>0 ) {																//	            If ARMIA(A,I,TE)>0
                            WOJ++;																								//	               Inc WOJ
                        }																												//	            End If
                    }																													//	         Next I
                }																														//	      End If
            }																															//	   Next A
            KON_S=GS("142"); KON2_S=GS("143");														//	   KON$="s" : KON2$="s"
            RES=AM % 10;																									//		RES=AM mod 10
            if( RES<=1 || RES>4 ) KON_S=GS("144");												//		If RES<=1 or RES>4 : KON$="—w" : End If
            if( RES> 1 &&	RES<5 ) KON_S=GS("145");												//		If RES>1 and RES<5 : KON$="y" : End If
            if( AM==1 ) KON_S="";																					//	   If AM=1 : KON$="" : End If
            if( WOJ==1 ) KON2_S="";																				//	   If WOJ=1 : KON2$="" : End If
            A_S=Str_S(AM)+GS("146")+KON_S+", "+Str_S(WOJ)+GS("147")+KON2_S;//	   A$=Str$(AM)+" legion"+KON$+", "+Str$(WOJ)+" worrior"+KON2$
            for( M=0; M<=49; M++ ) {																			//	   For M=0 To 49
                if( MIASTA[M][0][M_CZYJE]==1 ) {														//	      If MIASTA(M,0,M_CZYJE)=1
                    MS++;																											//	         Inc MS
                    LUDZIE+=MIASTA[M][0][M_LUDZIE];														//	         Add LUDZIE,MIASTA(M,0,M_LUDZIE)
                    POD+=MIASTA[M][0][M_PODATEK]*MIASTA[M][0][M_LUDZIE]/25;		//	         Add POD,MIASTA(M,0,M_PODATEK)*MIASTA(M,0,M_LUDZIE)/25
                }																														//	      End If
            }																															//	   Next M
            KON_S=GS("148");																							//	   KON$="s"
            RES=MS % 10;																									//		RES=MS mod 10
            if( RES>1 && RES<5 ) KON_S=GS("149");													//		If RES>1 and RES<5 : KON$="a" : End If
            if( MS==1 ) KON_S=GS("150");																	//	   If MS=1 : KON$="" : End If

            DZIEN_TEXT = GS("137")+Str_S(DZIEN)+"<br />"+GS("138")+"<br /><br />"+A_S+"<br />"+Str_S(MS)+GS("151")+KON_S+", "+Str_S(LUDZIE)+GS("152")+"<br /><br />"+GS("153")+Str_S(POD)+"<br />"+GS("139")+Str_S(players[1]->gold);
			day_info->SetInnerRML(DZIEN_TEXT.c_str());
		    aint WYS=0, KOL=0;

            for( int I=1; I<=4; ++I ) {																	//	            For I=1 To 4
                astr EL_ID = "bar" + toString(I);
                astr NAME_ID = "name" + toString(I);
                Rocket::Core::Element* graph_bar = options_body->GetElementById(EL_ID.c_str());
                Rocket::Core::Element* name_cell = options_body->GetElementById(NAME_ID.c_str());
                WYS=players[I]->power/250;																	//	               WYS=GRACZE(I,2)/250
                KOL=players[I]->colour;																			//	               KOL=GRACZE(I,3)
                if( WYS>100 ) WYS=100;																//	               If WYS>100 : WYS=100 : End If
                if( WYS<4 ) WYS=4;																		//	               If WYS<4 : WYS=4 : End If
                /*
                gad_text(1.0); Text(OKX+8,OKY+4+I*20,players[I]->playerName);		//	               Ink 1,30 : Text OKX+8,OKY+4+I*20,IMIONA$(I)
                                                                                                                            //	               '               Ink KOL+1 : Box OKX+50,OKY-8+I*20 To OKX+50+WYS,OKY-8+I*20+15
                switch(I) {
                    case 1: Gfx::Color(1.0f, 0.0f, 0.0f); break;
                    case 2: Gfx::Color(0.0f, 0.0f, 1.0f); break;
                    case 3: Gfx::Color(0.0f, 1.0f, 0.0f); break;
                    case 4: Gfx::Color(1.0f, 1.0f, 0.0f); break;
                }
                _Box(OKX+50,OKY-8+I*20,OKX+49+WYS,OKY-9+I*20+15);			//	               Ink KOL+1 : Box OKX+50,OKY-8+I*20 To OKX+49+WYS,OKY-9+I*20+15

                gad_shadow(1.0); _Box(OKX+51,OKY-7+I*20,OKX+50+WYS,OKY-8+I*20+15);//	               Ink 25 : Box OKX+51,OKY-7+I*20 To OKX+50+WYS,OKY-8+I*20+15
                */

                astr COLOUR_STR = "", BORDER_STR = "";

                switch(I) {
                    case 1: COLOUR_STR = "#b20000"; BORDER_STR = "#ff0000"; /*Gfx::Color(0.7f, 0.0f, 0.0f);*/ break;
                    case 2: COLOUR_STR = "#0000b2"; BORDER_STR = "#0000ff"; /*Gfx::Color(0.0f, 0.0f, 0.7f);*/ break;
                    case 3: COLOUR_STR = "#00b200"; BORDER_STR = "#00ff00"; /*Gfx::Color(0.0f, 0.7f, 0.0f);*/ break;
                    case 4: COLOUR_STR = "#b2b200"; BORDER_STR = "#ffff00"; /*Gfx::Color(0.7f, 0.7f, 0.0f);*/ break;
                }
                /*																										//
                _Bar(OKX+51,OKY-7+I*20,OKX+50+WYS,OKY-9+I*20+15);			//	               Ink KOL : Bar OKX+51,OKY-7+I*20 To OKX+49+WYS,OKY-9+I*20+15
                */

                astr WIDTH_STR = toString(WYS * 2) + "px";

                name_cell->SetInnerRML(players[I]->playerName.c_str());
                graph_bar->SetProperty("width", WIDTH_STR.c_str());
                graph_bar->SetProperty("background", COLOUR_STR.c_str());
                graph_bar->SetProperty("border-left-color", BORDER_STR.c_str());
                graph_bar->SetProperty("border-top-color", BORDER_STR.c_str());
            }
		}
    }
    else if (values[0] == "graphs")
    {
        Rocket::Core::Element* day_info = options_body->GetElementById("day_info");
        Rocket::Core::Element* graphs = options_body->GetElementById("graphs");
		if (day_info != NULL && graphs != NULL)
		{
		    const Rocket::Core::Property *displayProp = day_info->GetProperty("display");
		    if (displayProp->ToString() == "block")
            {
                day_info->SetProperty("display", "none");
                graphs->SetProperty("display", "block");
            }
            else
            {
                day_info->SetProperty("display", "block");
                graphs->SetProperty("display", "none");
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
