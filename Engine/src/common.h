#ifndef COMMON_H_HEADER_GUARD
#define COMMON_H_HEADER_GUARD

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

#ifndef MIN
    #define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#endif

#ifndef MAX
    #define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#endif

#include "defs.h"
#include "general.hpp"
#include "common_sdl.h"

#ifdef __cplusplus
extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#endif

#endif // COMMON_H_HEADER_GUARD
