#ifndef COMMON_H_HEADER_GUARD
#define COMMON_H_HEADER_GUARD

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include "defs.h"
#include "general.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#ifdef __cplusplus
extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#endif

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#endif // COMMON_H_HEADER_GUARD
