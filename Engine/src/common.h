#ifndef COMMON_H_HEADER_GUARD
#define COMMON_H_HEADER_GUARD

#ifndef SCRIPTING_WRAPPER_BUILD
    #include <iostream>
    #include <vector>
    #include <functional>
    #include <algorithm>
#endif // SCRIPTING_WRAPPER_BUILD

#include "defs.h"

#ifndef MIN
    #define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#endif

#ifndef MAX
    #define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#endif

#ifndef SCRIPTING_WRAPPER_BUILD
    #include "general.hpp"

    #define Uint64  uint64_t
    #define Uint32  uint32_t
    #define Uint8   uint8_t

    #define Sint64  int64_t
    #define Sint32  int32_t
    #define Sint8   int8_t
#else
    #include <types.h>

    #define Uint64  uint64_t
    #define Uint32  uint32_t
    #define Uint8   uint8_t

    #define Sint64  int64_t
    #define Sint32  int32_t
    #define Sint8   int8_t
#endif // SCRIPTING_WRAPPER_BUILD

#ifndef SCRIPTING_WRAPPER_BUILD
    #ifdef __cplusplus
    extern "C" {
        #include "lua.h"
        #include "lualib.h"
        #include "lauxlib.h"
    }
    #endif
#endif // SCRIPTING_WRAPPER_BUILD

#endif // COMMON_H_HEADER_GUARD
