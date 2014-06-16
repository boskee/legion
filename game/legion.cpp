#include "../engine/Gfx.h"

#include "Amos.h"
#include "legion.h"
#include "lgn_armia.h"
#include "lgn_diskacs.h"
#include "lgn_intro.h"
#include "lgn_mapa.h"
#include "lgn_miasto.h"
#include "lgn_przygoda.h"
#include "lgn_util.h"
#include "lgn_wczytaj.h"
#include "utl_locale.h"
#include "version.h"

// VOITEK: TEST
#include "../engine/Core.h"

using namespace std;

astr gs_language = "EN";
astr gs_default_language = "PL";

																//	Set Buffer 150
																//	'słoma off
																//	'MLech - usuniecie
																//	'Request Wb : Hide On : Erase All : Led Off : Auto View Off
																//	'Amos Lock : Break Off
																//
astr KAT_S = DATA_DIR;					//	KAT$=Dir$
aint LEWY=1,PRAWY=2;						//	Global KAT$,LEWY,PRAWY
																// LEWY=1+Mouse Key : PRAWY=2+Mouse Key

																//
																//	'MLech - usuniecie
																//	'If Exist(KAT$+"rtdd") : Exec KAT$+"rtdd" : End If
																//
																//	Assign "legion:" To KAT$
																//	Assign "dane:" To KAT$
																//
																//	Assign "fonts:" To KAT$+"fonts"
																//	Get Fonts

//! aint M_X = (aint)sin(2);				//	M_X=Sin(2)

aint ARMIA[40+1][10+1][30+1]
	 , WOJNA[5+1][5+1];					//	Dim ARMIA(40,10,30),WOJNA(5,5)

World::Player *players[4+1];                        // Dim IMIONA$(4),GRACZE(4,3)

astr ARMIA_S[40+1][10+1];							//	Dim ARMIA$(40,10)

aint AN[4+1];										//	Dim AN(4)

aflt VEKTOR_F[20+1][5+1];				//	Dim VEKTOR#(20,5)

aint PREFS[10+1];								//	Dim PREFS(10)

			//	Dim MIASTA(50,20,6),MIASTA$(50),MUR(10),SKLEP(20,21),STRZALY(10),ZNAKI$(30)
aint MIASTA[50+1][20+1][6+1+1], MUR[10+1], SKLEP[20+1][21+1], STRZALY[10+1];
astr MIASTA_S[50+1];

			//	Dim BOARD#(125)

			//	Global ARMIA(),ARMIA$(),VEKTOR#(),AN(),PREFS(),MIASTA(),MIASTA$(),MUR()
			//	Global GRACZE(),WOJNA(),SKLEP(),IMIONA$(),STRZALY(),ZNAKI$(),BOARD#()
			//	'--

			//	Global TEM,TX,TY,TSI,TSZ,TCELX,TCELY,TTRYB,TE,TKLAT,TP,TBOB,TAMO
			//-bedzie nizezj- aint TEM,TX,TY,TSI,TSZ,TCELX,TCELY,TTRYB,TE,TKLAT,TP,TBOB,TAMO;

			//	Global TLEWA,TPRAWA,TNOGI,TGLOWA,TKORP,TPLECAK,TMAG,TDOSW,TRASA,TWAGA,TMAGMA
			//-bedzie nizej- aint TLEWA,TPRAWA,TNOGI,TGLOWA,TKORP,TPLECAK,TMAG,TDOSW,TRASA,TWAGA,TMAGMA;

			//	'--
			//	Global M_X,M_Y,M_LUDZIE,M_PODATEK,M_CZYJE,M_MORALE,M_MUR
			//	M_X=1 : M_Y=2 : M_LUDZIE=3 : M_PODATEK=4 : M_CZYJE=5 : M_MORALE=6 : M_MUR=0
aint M_X=1 , M_Y=2 , M_LUDZIE=3 , M_PODATEK=4 , M_CZYJE=5 , M_MORALE=6 , M_MUR=0;
aint M_BOB=7;

			//	'--
			//	Global OX,OY,NUMER,ARM,WRG,SX,SY,MSX,MSY,FONT,FONR,FONTSZ,LOK,DZIEN,FON1,FON2
aint OX,OY,NUMER,SX,SY,MSX,MSY,FONT,FONR,FONTSZ,LOK,DZIEN,FON1,FON2,FON3;

			//	Global AMIGA,WPI$,WPI,WPI#,IMIONA,ODLEG,WIDOCZNOSC,BUBY,BIBY,PIKIETY,POTWORY
aint AMIGA,WPI,IMIONA,ODLEG,WIDOCZNOSC,BUBY,BIBY,PIKIETY,POTWORY;
astr WPI_S;
aflt WPI_F;

			//	Global CENTER_V,SCENERIA,LAST_GAD,KANAL,POWER,REZULTAT,GOBY,MUZYKA,KONIEC_INTRA
			//	CENTER_V=100
aint CENTER_V=100,SCENERIA,LAST_GAD,KANAL,POWER,REZULTAT,GOBY,MUZYKA,KONIEC_INTRA;

			//	'--
			//	Global BSIBY
aint BSIBY;

/* przeniesione do main_code() */			//	SPEED_CHECK

			//	Dim RASY(20,7),RASY$(20)
aint RASY[20+1][7+1];
astr RASY_S[20+1];

			//	Dim BRON(120,11),BRON$(120),BRON2$(25)
aint BRON[120+1][11+1];
astr BRON_S[120+1];
astr BRON2_S[25+1];

			//	Dim GLEBA(110,4),PLAPKI(10,4)
aint GLEBA[110+1][4+1], PLAPKI[10+1][4+1];

			//	Dim BUDYNKI(12,6),BUDYNKI$(12),GUL$(10)
aint BUDYNKI[12+1][6+1];
astr BUDYNKI_S[12+1], GUL_S[10+1];

			//	Dim ROZMOWA$(5,5),ROZMOWA2$(50),PRZYGODY$(20,10),IM_PRZYGODY$(3),PRZYGODY(3,10)
			//	Global ROZMOWA$(),ROZMOWA2$(),PRZYGODY$(),IM_PRZYGODY$(),PRZYGODY(),GUL$(),TRWA_PRZYGODA
astr ROZMOWA_S[5+1][5+1], ROZMOWA2_S[50+1], PRZYGODY_S[20+1][10+1], IM_PRZYGODY_S[3+1];
aint PRZYGODY[3+1][10+1], TRWA_PRZYGODA;

			//	P_TYP=0 : P_X=1 : P_Y=2 : P_TERMIN=3 : P_KIERUNEK=4 : P_LEVEL=5 : P_CENA=6 : P_NAGRODA=7 : P_BRON=8 : P_TEREN=9 : P_STAREX=10
			//	Global P_TYP,P_X,P_Y,P_TERMIN,P_KIERUNEK,P_LEVEL,P_CENA,P_NAGRODA,P_BRON,P_TEREN,P_STAREX
aint P_TYP=0, P_X=1, P_Y=2, P_TERMIN=3, P_KIERUNEK=4, P_LEVEL=5, P_CENA=6, P_NAGRODA=7, P_BRON=8, P_TEREN=9, P_STAREX=10;

			//	BROBY=15
			//	Global RASY(),RASY$(),BRON(),BRON$(),BRON2$(),GLEBA(),BROBY,BUDYNKI(),BUDYNKI$(),PLAPKI()
aint BROBY=15;

			//	ARM=0 : WRG=40
aint ARM=0, WRG=40;

			//	B_SI=1 : B_PAN=2 : B_SZ=3 : B_EN=4 : B_TYP=5 : B_WAGA=6
			//	B_PLACE=7 : B_DOSW=8 : B_MAG=9 : B_CENA=10 : B_BOB=11
			//	Global B_SI,B_PAN,B_SZ,B_EN,B_TYP,B_WAGA
			//	Global B_PLACE,B_DOSW,B_MAG,B_CENA,B_BOB
aint B_SI=1, B_PAN=2, B_SZ=3, B_EN=4, B_TYP=5, B_WAGA=6
	 , B_PLACE=7, B_DOSW=8, B_MAG=9, B_CENA=10, B_BOB=11;

			//	Global OKX,OKY,SPX,SPY,REAL_KONIEC,KONIEC_AKCJI,WYNIK_AKCJI,KTO_ATAKUJE,TESTING,CELOWNIK
aint OKX,OKY,SPX,SPY,REAL_KONIEC,KONIEC_AKCJI,WYNIK_AKCJI,KTO_ATAKUJE,TESTING,CELOWNIK;

			//	Global GAME_OVER,_MODULO,SUPERVISOR,MX_WEAPON
aint GAME_OVER,_MODULO,SUPERVISOR,MX_WEAPON;

			//	TEM=0 : TX=1 : TY=2 : TSI=3 : TSZ=4 : TCELX=5 : TCELY=6 : TTRYB=7 : TE=8 : TP=9
			//	TBOB=10 : TKLAT=11 : TAMO=12 : TLEWA=16 : TPRAWA=17 : TNOGI=15 : TGLOWA=13
			//	TPLECAK=18 : TKORP=14 : TMAG=26 : TDOSW=27 : TRASA=28 : TWAGA=29 : TMAGMA=30
aint TEM=0, TX=1, TY=2, TSI=3, TSZ=4, TCELX=5, TCELY=6, TTRYB=7, TE=8, TP=9
	 , TBOB=10, TKLAT=11, TAMO=12, TLEWA=16, TPRAWA=17, TNOGI=15, TGLOWA=13
	 , TPLECAK=18, TKORP=14, TMAG=26, TDOSW=27, TRASA=28, TWAGA=29, TMAGMA=30;



//-------------------------------------------------------------------------

void EKRAN_WYBOR(void);

//-------------------------------------------------------------------------


void _main_code_rysuj_your_name(void) {
  Gfx::Color(0.f,0.f,0.f);
  _ClearRaster();
  Gfx::Color(1.f,1.f,1.f);
  Text(OKX+25,OKY+20,GS("000"));	//"Enter your name"
}
astr is_oponent_name = "";
void _main_code_rysuj_oponent_name(void) {
  Gfx::Color(0.f,0.f,0.f);
  _ClearRaster();
  Gfx::Color(1.f,1.f,1.f);
  Text(OKX+2,OKY+20,is_oponent_name);	//"Enter your name"
}
void main_code(void) {

	InitLocale();
	if( ExistsLang(gs_language) )
		SetLang(gs_language);
	else
		SetLang(gs_default_language);

	if( IB_INTRO ) pc_intro();

	SPEED_CHECK();

	AN[0]=0; AN[1]=1; AN[2]=0; AN[3]=2;		//	AN(0)=0 : AN(1)=1 : AN(2)=0 : AN(3)=2
	KTO_ATAKUJE=-1;			//	KTO_ATAKUJE=-1
	WCZYTAJ_BRON();			//	WCZYTAJ_BRON
	WCZYTAJ_RASY();			//	WCZYTAJ_RASY
	WCZYTAJ_BUDYNKI();	//	WCZYTAJ_BUDYNKI
	WCZYTAJ_ROZMOWE();	//	WCZYTAJ_ROZMOWE
	WCZYTAJ_PRZYGODY();	//	WCZYTAJ_PRZYGODY
	WCZYTAJ_GULE();			//	WCZYTAJ_GULE
	FONTSZ=5;						//	FONTSZ=5
	PREFS[1]=1; PREFS[2]=1; PREFS[4]=1;	//	PREFS(1)=1 : PREFS(2)=1 : PREFS(4)=1
	PREFS[5]=0;

	aint KONIEC=0, KONIEC2=0, STREFA=0, NSAVE=0;
	aint MZ=0, I=0;
	astr A_S="",B_S="",L_S="",PAT_S="",NAME_S="";
	astr Z_S="";
	aint KLAW=0, X=0, Y=0, NEW_X=0, NEW_Y=0;

											//	'TESTING=True
											//	'Goto BITWA
											//	'Goto PRZYGODA
	//goto LAB_BITWA;
	//goto PRZYGODA;

	if( IB_INTRO ) _INTRO();						//	'_INTRO
	EKRAN_WYBOR();			//	EKRAN_WYBOR
		X=XMouse(); Y=YMouse();						//	   X=X Mouse : Y=Y Mouse


	do {	//	Repeat
		_DrawIff(-1,0,0); BobUpdate();
		SetFont(FON3);
		Gfx::Color(1.f,1.f,1.f,0.8f);
		Text(560,500,astr("ver ")+AutoVersion::FULLVERSION_STRING,1.2f);
		SetFont(FON1);
	//	Core::Context->Update();
//    Core::Context->Render();

		WaitVbl();






															//	MAIN:








		Z_S=Inkey_S();										//	   A$=Inkey$
		KLAW=ScanCode();									//	   KLAW=Scancode

		if( KLAW>=76 && KLAW<=77 ) {				//	   If KLAW>75 and KLAW<80
		    if (KLAW==76)
		    {
		        MZ -= 1;
		        if (MZ < 21)
                {
                    MZ = 23;
                }
		    }
		    else if (KLAW == 77)
            {
                MZ += 1;
                if (MZ > 23)
                {
                    MZ = 21;
                }
            }
			//KLAWSKROL(KLAW);								//	      KLAWSKROL[KLAW]
		}
		ClearKey();

		NEW_X=XMouse(); NEW_Y=YMouse();						//	   X=X Mouse : Y=Y Mouse

		if (NEW_X != X || NEW_Y != Y)
        {
            MZ = MouseZone();
            X = NEW_X;
            Y = NEW_Y;
        }

		if( 21 == MZ ) {	//	   If Mouse Zone=21
			//	      Rainbow 1,3,140,23
			//	      Rainbow 2,3,163,23
			//	      Rainbow 3,3,187,23
			//	      Bob 1,,190,1 : View
			_Bob(1,NOPARI,190,1);
			//	      Bob Update : Wait Vbl
			if( MouseClick() || KLAW == 68) {	//	      If Mouse Click=1
				Gfx::Color(0.f,0.f,0.f);
				_ClearRaster();
				// SwapBuffers(); _ClearRaster();
				//	         Rainbow Del : View
				//	         Fade 1 : Wait 15
				//	         Screen Open 0,192,200,32,Lowres : Flash Off : Curs Off : Cls 0
				ScreenOpen(0,192,200,32,LOWRES);
				//	         Double Buffer : Bob Update On : Priority Off
				BobUpdateOnOff(true);
				//	         Screen Display 0,200,,,
				ScreenDisplay(0,200,NOPARI,NOPARI,NOPARI);
				//	         Get Bob Palette : Colour 3,$462
				//	         Set Rainbow 0,1,528,"(3,1,1)","(3,1,1)","(3,1,1)"
				//	         Bob 1,0,60,2 : Bob 2,0,60,3 : Bob Update
				_Bob(1,0,60,2); _Bob(2,0,60,3); BobUpdate();
				//	         Rainbow 0,20,110,26
				//	         A$="S: Move -128,0,387; Move 0,0,50; Move 128,0,387; Move 0,0,50; Jump S"
				A_S = "FLOAT S; S=1.0/50.0; MOVE -1,(-128,0,387*S)(0,0,50*S)(128,0,387*S)(0,0,50*S); PAUSE IS MOVING;";
				//	         B$="S: Move -387,0,387; Move 0,0,50; Move 387,0,387; Move 0,0,50; Jump S"
				B_S = "FLOAT S; S=1.0/50.0; MOVE -1,(-387,0,387*S)(0,0,50*S)(387,0,387*S)(0,0,50*S); PAUSE IS MOVING;";
				//	         Channel 1 To Bob 1 : Channel 2 To Bob 2
				//	         Amal 1,A$ : Amal 2,B$
				//	         Amal On 2 : Amal On 1
				Amal(1,A_S); Amal(2,B_S);
				ChannelToBob(1,1); ChannelToBob(2,2);
				AmalOnOff(2,true); AmalOnOff(1,true);

				OKX=0; OKY=0;		//	         OKX=0 : OKY=0
				SetFont(FON2);	//	         Set Font FON2

				//	         Ink 28,0 : Text OKX+10,OKY+20,"Enter your name"
				rysuj_ekran_ptr = _main_code_rysuj_your_name;
				//				Gfx::DrawBuffer(Gfx::DB_BOTH);
				//				Gfx::Color(1.f,1.f,1.f);
				//				Text(OKX+25,OKY+20,GS("000"));	//"Enter your name"
				//				Gfx::DrawBuffer(Gfx::DB_BACK);

				//	         View
				//	         WPISZ[OKX+30,OKY+40,28,0,12]
				//				WPISZ(OKX+30,OKY+40,28,0,12,-1);
				SET_BACKGROUND(0.f,0.f,0.f,1.f);
				SET_FOREGROUND(1.f,1.f,1.f,1.f);
				WPI_S="";
				WPISZ_PC(OKX+30,OKY+30,50,20,12,WPI_S,3);


					if( WPI_S == "" )	{					//	            If WPI$<>""
					    WPI_S = ROB_IMIE();
					}
                    players[I+1] = new World::Player(WPI_S);		//	               IMIONA$(I+1)=WPI$

				rysuj_ekran_ptr = _main_code_rysuj_oponent_name;
				for( I=1; I<=3; ++I ) {	//	         For I=1 To 3
					//	            Ink 0 : Bar OKX+2,OKY+2 To 200,70
					//					Gfx::DrawBuffer(Gfx::DB_BOTH);
					//					Gfx::Color(0.f,0.f,0.f); _Bar(OKX+2,OKY+2,200,70);
					//	            If I=1 : L$="First" : End If
					//	            If I=2 : L$="Second" : End If
					//	            If I=3 : L$="Third" : End If
					switch(I) {
						case 1: L_S=GS("001"); break;
						case 2: L_S=GS("002"); break;
						case 3: L_S=GS("003"); break;
					}
					//	            Ink 28,0 : Text OKX+2,OKY+20,L$+" opponent name"
					//					Gfx::Color(1.f,1.f,1.f); Text(OKX+2,OKY+20,L_S+GS("004"));
					//					Gfx::DrawBuffer(Gfx::DB_BACK);
          is_oponent_name = L_S+GS("004");

					//	            WPISZ[OKX+30,OKY+40,28,0,12]
					//WPISZ(OKX+30,OKY+40,28,0,12,-1);
					WPI_S="";
					WPISZ_PC(OKX+30,OKY+30,50,20,12,WPI_S,3);

					if( WPI_S == "" )	{					//	            If WPI$<>""
					    WPI_S = ROB_IMIE();
					}
                    players[I+1] = new World::Player(WPI_S);		//	               IMIONA$(I+1)=WPI$												//	            End If
				}	//	         Next I

				rysuj_ekran_ptr = 0;

				//	         Rainbow Del : View
				//	         Fade 2 : _TRACK_FADE[1]
				TrackFade(1);
				BobUpdateOnOff(false);
				for( int f=0; f<=30; ++f ) {
					BobUpdate();
					Fade(f/30.0);
					WaitVbl();
				}

				//	         Bob Update Off : Amal Off
				BobUpdateOnOff(false);
				AmalOnOff(-1,false);
				DZIEN=1;																	//	         DZIEN=1
				POWER=5; SX=0; SY=0;											//	         POWER=5 : SX=0 : SY=0
				for(I=1;I<=4;++I) players[I]->gold = 5000;			//	         For I=1 To 4 : GRACZE(I,1)=5000 : Next I
				players[1]->colour=20; players[2]->colour=16; players[3]->colour=18; players[4]->colour=22;	//	         GRACZE(1,3)=20 : GRACZE(2,3)=16 : GRACZE(3,3)=18 : GRACZE(4,3)=22
				PREFS[1]=1; PREFS[2]=1; PREFS[4]=1;				//	         PREFS(1)=1 : PREFS(2)=1 : PREFS(4)=1
				ScreenClose(0);														//	         Screen Close 0
				Gfx::Color(0.f,0.f,0.f);
				_ClearRaster();
				SETUP0();							//	         SETUP0
				ZROB_MIASTA();				//	         ZROB_MIASTA
				ZROB_ARMIE();					//	         ZROB_ARMIE
															//	         View
				MAIN();								//	         Gosub MAIN
				EKRAN_WYBOR();				//	         EKRAN_WYBOR
			}												//	      End If
		}													//	   End If
		if( 22 == MZ ) {																											//	   If Mouse Zone=22
																																					//	      Rainbow 2,3,140,23
																																					//	      Rainbow 3,3,187,23
																																					//	      Rainbow 1,3,163,23
																																					//	      Bob 1,,237,1 : View
																																					//	      Bob Update : Wait Vbl
			_Bob(1,NOPARI,237,1);
			void *sb=0;
			if( MouseClick()==1 || KLAW == 68) {																							//	      If Mouse Click=1
				OKX=320; OKY=180;																									//	         OKX=320 : OKY=180
																																					//	         Get Block 100,OKX,OKY,176,180
				Gfx::Color(0.0f, 0.0f, 0.0f); _Bar(320,180,480,350);													//	         Ink 0 : Bar 320,180 To 480,350
				Gfx::Color(0.9f, 0.9f, 0.9f); _Box(320,180,480,350);							//	         Ink 7 : Box 320,180 To 480,350
				Gfx::Color(0.5f, 0.5f, 0.5f); _Box(321,181,479,349);							//	         Ink 5 : Box 321,181 To 479,349
				SetFont(FON2);																										//	         Set Font FON2
																																					//	         'USTAW_FONT["bodacious",42]
																																					//	         Gr Writing 0
				//GADGET(OKX+10,OKY+8,120,15,A_S,K1,0,K2,31,-1);									//	         GADGET[OKX+10,OKY+8,120,15,A$,K1,0,K2,31,-1]
																																					//	         If Exist(KAT$+"archiwum")
				PAT_S=KAT_S+"archiwum/";																					//	            PAT$=KAT$+"archiwum/"
																																					//	         Else
																																					//	            REQUEST["archiwum:","Archiwum"]
																																					//	            PAT$="archiwum:"
																																					//	         End If
				for( I=0; I<=4; ++I ) {																						//	         For I=0 To 4
					if( Exists(PAT_S+"zapis"+Str_S(I+1)) ) {													//	            If Exist(PAT$+"zapis"+Str$(I+1))
																																					//	               Open In 1,PAT$+"zapis"+Str$(I+1)
																																					//	               NAME$=Input$(1,20)
																																					//	               NAME$=NAME$-Chr$(0)
																																					//	               Close 1
						FILE *fin=fopen((PAT_S+"zapis"+Str_S(I+1)).c_str(),"rb");
						if( 0!=fin ) {
							char buf[21];
							fread(buf,1,20,fin);
							buf[20]=0;
							NAME_S=buf;
							fclose(fin);
						}
					} else {																												//	            Else
						NAME_S=GS("005");																							//	               NAME$="Empty Slot"
					}																																//	            End If
					Gfx::Color(0.9f, 0.9f, 0.9f); Text(OKX+20,OKY+28+(I*25),NAME_S);		//	            Ink 7 : Text OKX+20,OKY+28+(I*25),NAME$
					SetZone(1+I,0,0,640,OKY+28+(I*25));															//	            Set Zone 1+I,0,0 To 640,OKY+28+(I*25)
				}																																	//	         Next
				Text(OKX+20,OKY+28+(5*25),GS("006"));															//	         Text OKX+20,OKY+28+(5*25),"Exit"
				SetZone(6,0,200,640,500);																					//	         Set Zone 6,0,200 To 640,500
				KONIEC2=0;																												//	         KONIEC2=False
				sb = StoreBuffer(OKX-1,OKY-1,176+2,180+2);
				do {																															//	         Repeat
					STREFA=MouseZone();																							//	            STREFA=Mouse Zone
					_Bob(1,NOPARI,OKY+((STREFA-1)*25),1);														//	            Bob 1,,OKY+((STREFA-1)*25),1 : Bob Update : Wait Vbl
					_DrawIff(-1,0,0); BobUpdate(); RestoreBuffer(sb); WaitVbl();
					if( MouseClick()==1 ) {																					//	            If Mouse Click=1
						if( STREFA==6 ) {																							//	               If STREFA=6
							KONIEC2=-1;																									//	                  KONIEC2=True
							for( I=1; I<=19; ++I ) {																		//	                  For I=1 To 19
								ResetZone(I);																							//	                     Reset Zone I
							}																														//	                  Next I
																																					//	                  Put Block 100 : Screen Swap : Put Block 100
						}																															//	               End If
						if( STREFA>0 && STREFA<6 && Exists(PAT_S+"zapis"+Str_S(STREFA)) ) {//	               If STREFA>0 and STREFA<6 and Exist(PAT$+"zapis"+Str$(STREFA))
							KONIEC2=-1;																									//	                  KONIEC2=True
							NSAVE=STREFA;																								//	                  NSAVE=STREFA
							unsigned char bank[60000], *MEM;														//	                  Reserve As Work 10,60000
							MEM=bank+20;																								//	                  MEM=Start(10)+20
							FILE *fin=fopen((KAT_S+"archiwum/zapis"+Str_S(NSAVE)).c_str(),"rb");
							if( 0!=fin ) {
								fread(bank,1,60000,fin);
								fclose(fin);
							}
																																					//	                  If Exist(KAT$+"archiwum/zapis"+Str$(NSAVE))
																																					//	                     Bload KAT$+"archiwum/zapis"+Str$(NSAVE),Start(10)
																																					//	                  Else
																																					//	                     REQUEST["archiwum:zapis"+Str$(NSAVE),"Archiwum"]
																																					//	                     Bload "archiwum:zapis"+Str$(NSAVE),Start(10)
																																					//	                  End If
							ODCZYT(MEM);																								//	                  ODCZYT[MEM]
																																					//	                  Del Block : Rainbow Del : View
							BobUpdateOnOff(false);
							AmalOnOff(-1,false);

							Gfx::Color(0.f,0.f,0.f); _ClearRaster(); WaitVbl();
							_TRACK_FADE(1);																							//	                  Fade 2 : _TRACK_FADE[1]
							ScreenClose(0);																							//	                  Screen Close 0
							SX=0; SY=0;																									//	                  SX=0 : SY=0
							SETUP0();																										//	                  SETUP0
							VISUAL_OBJECTS();																						//	                  VISUAL_OBJECTS
							MAIN();																											//	                  Gosub MAIN
							EKRAN_WYBOR();																							//	                  EKRAN_WYBOR
						}																															//	               End If
					}																															//	            End If
				} while( KONIEC2==0 );																						//	         Until KONIEC2
			}
			FreeBuffer(sb);																																	//	      End If
		}																																			//	   End If
		if( 23 == MZ ) {							//	   If Mouse Zone=23
																	//	      Rainbow 2,3,140,23
																	//	      Rainbow 3,3,163,23
																	//	      Rainbow 1,3,187,23
																	//	      Bob 1,,285,1 : View
																	//	      Bob Update : Wait Vbl
			_Bob(1,NOPARI,285,1);
			if( MouseClick()==1 || KLAW == 68) {			//	      If Mouse Click=1
				KONIEC=-1;								//	         KONIEC=True
			}														//	      End If
		}									//	   End If
	} while( ! KONIEC );						//	Until KONIEC
																	//	Rainbow Del : View
																	//	Fade 2 : _TRACK_FADE[1]
																	//	Screen Close 0
																	//	Erase All
																	//	Led On
																	//	Assign "fonts:" To "Sys:fonts"
																	//	'If Exist(KAT$+"rtdd") : Exec KAT$+"rtdd" : End If
	//exit(0);											//	Edit
	return;

																	//	'tu sie zaczyna bitwa
	//LAB_BITWA:											//	BITWA:
																	//	Show On
		TESTING=-1;										//	TESTING=True
		NOWA_ARMIA(1,10,-1);					//	NOWA_ARMIA[1,10,-1]
		NOWA_ARMIA(40,10,-1);					//	NOWA_ARMIA[40,10,-1]
		KTO_ATAKUJE=1;								//	KTO_ATAKUJE=1
		ARMIA[40][0][TKORP]=151;			//	ARMIA(40,0,TKORP)=151
		BITWA(1,40,1,2,0,0,0,2,1,-1);	//	BITWA[1,40,1,2,0,0,0,2,4,-1]
																	//	Erase All
																	//	Sam Stop
		//exit(0);										//	Edit
		return;
																	//
																	//	'tu sie zaczyna przygoda
	//PRZYGODA:												//	PRZYGODA:
		TESTING=-1;										//	TESTING=True
																	//	Show On
		NOWA_ARMIA(1,10,-1);					//	NOWA_ARMIA[1,10,-1]
		ReserveZone(30);							//	Reserve Zone 30
																	//	'PRZYGODY(2,P_TYP)=2
		NOWA_PRZYGODA(1,2,9,0);			//	NOWA_PRZYGODA[1,2,13,0]
																	//	'PRZYGODY(2,P_TEREN)=2
		MA_PRZYGODA(1,2);							//	MA_PRZYGODA[1,2]
																	//	Erase All
																	//	Sam Stop
		//exit(0);										//	Edit
		return;
}

void EKRAN_WYBOR(void) {
	//	Procedure EKRAN_WYBOR

	astr A_S="";

	Gfx::Color(0,0,0); _ClearRaster(); SwapBuffers(); _ClearRaster();
	Screen(0);

		//	   Hide On
		//	   _LOAD[KAT$+"kam_eng.pic","LEGION:kam_eng.pic","Legion",3]
		//	   _LOAD[KAT$+"mieczyk","legion:mieczyk","Legion",0]
		//	   _LOAD[KAT$+"intro","legion:intro","Legion",1]
	_LOAD(KAT_S+GS("FILE000"),KAT_S+"kam_eng.pic.iff","Legion",3);
	_LOAD(KAT_S+"mieczyk",KAT_S+"mieczyk.abk_sp","Legion",0);
    _LOAD(KAT_S+"intro",KAT_S+"intro.abk_sp","Legion",1);

	ScreenOpen(0,640,512,16,HIRES|LACED);

	USTAW_FONT("defender2",FONT_DEFENDER,14,0); FON3=FONR;

		//	   USTAW_FONT["garnet",16]
		//	   FON2=FONR
	USTAW_FONT("garnet",FONT_GARNET,24,1);	FON2=FONR;

		//	   USTAW_FONT["defender2",8]
		//	   FON1=FONR
	USTAW_FONT("defender2",FONT_DEFENDER,8,1); FON1=FONR;


		//	   Reserve Zone 25
		//	   Set Zone 21,0,0 To 640,238
		//	   Set Zone 22,0,238 To 640,285
		//	   Set Zone 23,0,285 To 640,500
	ReserveZone(25);
  SetZone(21,0,0,640,238);
  SetZone(22,0,238,640,285);
  SetZone(23,0,285,640,500);

		//	   Set Rainbow 2,6,256,"(2,-1,1)","(2,-1,1)","(3,-1,1)"
		//	   Set Rainbow 3,6,256,"","(2,-1,1)","(3,-1,1)"
		//	   Set Rainbow 1,6,256,"(3,-1,1)","(2,-1,1)",""
		//	   Double Buffer
		//	   Autoback 1

	_DrawIff(-1,0,0); SwapBuffers(); _DrawIff(-1,0,0);

		//	   Bob Update Off
		//	   Bob 1,50,190,1 : Bob Update : Wait Vbl
	BobUpdateOnOff(false);
	_Bob(1,50,190,1); BobUpdate(); WaitVbl();

	//	   A$="E:Move 4,0,4; Move 4,0,3; Move 4,0,2; Move 16,0,6; Move 4,0,2; Move 4,0,3; Move 4,0,4;"
	//	   A$=A$+"Move -4,0,4; Move -4,0,3; Move -4,0,2; Move -16,0,6; Move -4,0,2; Move -4,0,3; Move -4,0,4;Jump E"
	A_S = "FLOAT S; S=1.0/50.0;	\n\
				 MOVE -1,(4,0,4*S)(4,0,3*S)(4,0,2*S)(16,0,6*S)(4,0,2*S)(4,0,3*S)(4,0,4*S)					\n\
				 				 (-4,0,4*S)(-4,0,3*S)(-4,0,2*S)(-16,0,6*S)(-4,0,2*S)(-4,0,3*S)(-4,0,4*S)	\n\
				 PAUSE IS MOVING ";
	//	   Channel 1 To Bob 1
	//	   Amal 1,A$
	//	   Amal On 1
	Amal(1,A_S);
	ChannelToBob(1,1);
	AmalOnOff(1,true);

	//	   Limit Mouse 150,140 To 150,205
	LimitMouse(150,140,150,205);
	//	   View : Wait Vbl
	WaitVbl();

	while( MouseKey()!=0 ) {
		WaitVbl();
		MouseClick();	//jako efekt uboczny czysci bufor klikniec
	}
	//	End Proc
}
