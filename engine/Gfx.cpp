#include <iostream>

#include "Gfx.h"
#include "Utils.h"

#include <SDL2/SDL.h>

#ifdef _WIN32
    #include <SDL/SDL_image.h>
#elif __linux__
    #include <SDL/SDL_image.h>
#elif __APPLE__
    #include <SDL2_image/SDL_image.h>
#endif

using namespace Core;

namespace Gfx {
};
