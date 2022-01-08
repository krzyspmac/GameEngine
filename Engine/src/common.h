#ifndef COMMON_H_HEADER_GUARD
#define COMMON_H_HEADER_GUARD

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#include "defs.h"
#include "general.hpp"
#include "common_sdl.h"
#include "console_logger.hpp"

#ifdef __cplusplus
extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#endif

#define LOGGER ConsoleLog::Shared()

#endif // COMMON_H_HEADER_GUARD
