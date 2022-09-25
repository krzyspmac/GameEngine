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

#define Uint64  uint64_t
#define Uint32  uint32_t
#define Uint8   uint8_t

#define Sint64  int64_t
#define Sint32  int32_t
#define Sint8   int8_t

#endif // COMMON_H_HEADER_GUARD
