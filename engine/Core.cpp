#include <SDL2/SDL.h>
#include <iostream>

#include <Rocket/Core/Core.h>
#include <Rocket/Controls.h>
#include <Rocket/Core/Input.h>
#include <Rocket/Debugger/Debugger.h>
#include "ShellFileInterface.h"

#include "SystemInterfaceSDL2.h"
#include "RenderInterfaceSDL2.h"

#include "Core.h"
#include "Utils.h"
#include "Bob.h"
#include "Collision.h"

#include "EventInstancer.h"
#include "EventManager.h"

namespace Core {

using namespace std;
using namespace Gfx;

bool ib_gfx_enable = true;
bool ib_snd_enable = true;
long il_screen_width = 640;
long il_screen_height = 480;
bool ib_double_buffer = true;
bool ib_zbuffer = false;
int ii_zbuffer_depth = 16;
bool ib_full_screen = false;
bool ib_resizable = false;

string is_screen_title = "Engine2d";
SDL_Window *screen = 0;
SDL_Renderer *renderer = 0;
Rocket::Core::Context *Context = 0;
RocketSDL2Renderer *Renderer = 0;
RocketSDL2SystemInterface *SystemInterface = 0;
ShellFileInterface *FileInterface = 0;
Mix_Music *sound = 0;

Uint32 _ii_video_flags = 0;
int _ii_video_bpp = 0;

int Init(void) {

	  //////////////////////////
	 // Ogólna inicjalizacja //
	//////////////////////////
	unsigned long ll_mask = 0;
	if( ib_gfx_enable ) ll_mask |= SDL_INIT_VIDEO;
	if( ib_snd_enable ) ll_mask |= SDL_INIT_AUDIO;
	if(SDL_Init(ll_mask) < 0) {
		ERROR("Video initialization failed: " + SDL_GetError());
		exit(-1);
	}

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	atexit(SDL_Quit);


	  ///////////////////
	 // Grafika, okno //
	///////////////////
	//const SDL_VideoInfo* info = 0;
	int width = il_screen_width;
	int height = il_screen_height;
	int bpp = 8;
	Uint32 flags = 0;

	//info = SDL_GetVideoInfo();
	//bpp = info->vfmt->BitsPerPixel;

	//SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	//SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	//SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

	if( ib_zbuffer )
		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, ii_zbuffer_depth );

	flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	if( ib_full_screen )
		flags |= SDL_WINDOW_FULLSCREEN;
	if( ib_resizable )
		flags |= SDL_WINDOW_RESIZABLE;

	//zapamietujemy parametry na potrzeby zdarzenia RESIZE
	_ii_video_bpp = bpp;
	_ii_video_flags = flags;

	if((screen = SDL_CreateWindow(is_screen_title.c_str(),
                          SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED,
                          width, height,
                          flags)) == 0) {
		ERROR("Video mode set failed: " + SDL_GetError());
    exit(-1);
	}

	SDL_GLContext glcontext = SDL_GL_CreateContext(screen);

    int oglIdx = -1;
    int nRD = SDL_GetNumRenderDrivers();
    for(int i=0; i<nRD; i++)
    {
        SDL_RendererInfo info;
        if(!SDL_GetRenderDriverInfo(i, &info))
        {
            if(!strcmp(info.name, "opengl"))
            {
                oglIdx = i;
            }
        }
    }

    renderer = SDL_CreateRenderer(screen, oglIdx, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    GLenum err = glewInit();

    if(err != GLEW_OK)
        fprintf(stderr, "GLEW ERROR: %s\n", glewGetErrorString(err));

	if( ib_double_buffer )
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	else
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);

	if( ib_zbuffer )
		glEnable(GL_DEPTH);
	else
		glDisable(GL_DEPTH);

	//ustawiamy domyslne rzutowanie swiata na ekran
	ProjectionOrtho();





    Renderer = new RocketSDL2Renderer(renderer, screen);
    SystemInterface = new RocketSDL2SystemInterface();
    FileInterface = new ShellFileInterface("legion/data/gui/");

    Rocket::Core::SetFileInterface(FileInterface);
    Rocket::Core::SetRenderInterface(Renderer);
    Rocket::Core::SetSystemInterface(SystemInterface);

    if(!Rocket::Core::Initialise())
        return 1;

	// Initialise the Rocket Controls library.
	Rocket::Controls::Initialise();

    Rocket::Core::FontDatabase::LoadFontFace("../../../fonts/Bodacious-Normal.ttf");
    Rocket::Core::FontDatabase::LoadFontFace("Delicious-Bold.otf");
    Rocket::Core::FontDatabase::LoadFontFace("Delicious-BoldItalic.otf");
    Rocket::Core::FontDatabase::LoadFontFace("Delicious-Italic.otf");
    Rocket::Core::FontDatabase::LoadFontFace("Delicious-Roman.otf");

	Context = Rocket::Core::CreateContext("default",
		Rocket::Core::Vector2i(width, height));

	Rocket::Debugger::Initialise(Context);

	// Initialise the event instancer and handlers.
	EventInstancer* event_instancer = new EventInstancer();
	Rocket::Core::Factory::RegisterEventListenerInstancer(event_instancer);
	event_instancer->RemoveReference();

    /*
	Rocket::Core::ElementDocument *Document = Context->LoadDocument("demo.rml");

	if(Document)
	{
		Document->Show();
		Document->RemoveReference();
		fprintf(stdout, "\nDocument loaded");
	}
	else
	{
		fprintf(stdout, "\nDocument is NULL");
	}*/

	  /////////////////////
	 // Dzwięki, muzyka //
	/////////////////////
//	int audio_rate,audio_channels
	int	audio_buffers=1024;
//	Uint16 audio_format;
//	Uint32 t;
//	int volume=SDL_MIX_MAXVOLUME;

	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,audio_buffers)<0) {
		ERROR("Audio mixer failed: " + SDL_GetError());
    exit(-1);
	}

	  ////////////////
	 // Klawiatura //
	////////////////
	//SDL_EnableKeyRepeat(0,0);

	return 1;
}

int Finish(void) {
    Context->RemoveReference();
    Rocket::Core::Shutdown();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    SDL_Quit();
	return 1;
}

void _CoreResizeEvent(int w,int h) {
//	Uint32 flags = _ii_video_flags;
//	if((screen = SDL_SetVideoMode(w, h, _ii_video_bpp, flags)) == 0) {
//		ERROR("Video mode set failed: " + SDL_GetError());
//    exit(-1);
//	}
	il_screen_width = w;
	il_screen_height = h;
}

//Obsluga czasow ramek
int FrameTiming(int mode) {
	Uint32 current, interval;
	static Uint32 first = 0, last = 0, five = 0, nframes = 0;
	static long last_col_test = 0;
	static bool first_call = true;

	current = SDL_GetTicks();
	switch( mode ) {
		case FTM_NEW_FRAME:
			nframes++;

			if( first_call ) {
				first_call = false;	//pierwszy raz mamy juz za soba
				first = current;
				last = current;
				five = current;
			}

			if (current - five > 5*1000) {
				INFO( toString( (unsigned long)nframes )
				    + " frames in 5 seconds = "
						+ toString( (float)nframes/5.0f,"%.1f" )
						+ " FPS  bobblits="
						+ toString( (unsigned long)Gfx::bobblit_cnt )
						+ " = "
						+ toString( (float)Gfx::bobblit_cnt/nframes,"%.1f")
						+ " BPF col_tests="
						+ toString( (unsigned long)(Fzx::collision_test_cnt - last_col_test) )
						+ " = "
						+ toString( (float)(Fzx::collision_test_cnt - last_col_test)/nframes,"%.1f" )
						+ " CTPF" );
				Gfx::bobblit_cnt = 0;
				last_col_test = Fzx::collision_test_cnt;
				nframes = 0;
				five = current;
			}

			interval = current - last;
			last = current;

			return interval;
		case FTM_FRAME_TIME:
			return current - last;
		case FTM_ALL_FRAMES_TIME:
			return current - first;
		case FTM_RAW_TICKS:
		default:
			return current;
	}
}

long FrameWait(Uint32 frame_time) {
	long interval;
	interval = frame_time - FrameTiming(Core::FTM_FRAME_TIME);
	if( interval > 0 ) {		//pozostalo troche czasu do zalozonego czasu ramki
		SDL_Delay(interval);
	}
	return interval;
}

void Wait(long pl_milisec) {
	SDL_Delay(pl_milisec);
}

void updateGuiBuffer()
{
    Renderer->clearDrawBuffer();
    Context->Render();
}

void drawGui()
{
    Renderer->drawBuffer();
}

void SwapBuffers(void) {
	BreakBobBlits();
	glFlush();							//oprozniamy kolejki OpenGL (czekamy az sie wszystko narysuje)
    //SDL_GL_SwapWindow(screen);
    //SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    //SDL_RenderClear(renderer);
	//SDL_GL_SwapWindow(screen);
    //    SDL_RenderPresent(renderer);
}

void ProjectionOrtho(GLfloat minx,GLfloat maxx,GLfloat miny,GLfloat maxy,GLfloat minz,GLfloat maxz) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(minx,maxx,miny,maxy,minz,maxz);
	glMatrixMode(GL_MODELVIEW);
}

void ProjectionOrtho(void) {
	ProjectionOrtho(0, Core::il_screen_width, Core::il_screen_height, 0);
}

void ShowMouseCursor(bool visible) {
	if( visible ) {
		SDL_ShowCursor(SDL_ENABLE);
	} else {
		SDL_ShowCursor(SDL_DISABLE);
	}
}

}	//namespace Core
