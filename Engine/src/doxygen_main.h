//
//  doxygen_main.h
//  Engine
//
//  Created by krzysp on 31/12/2021.
//

#ifndef doxygen_main_h
#define doxygen_main_h

/** \defgroup API_GLOBALS Exposed Functionality
    A list of exposed interfaces available to be used in C++ game scripts. Those manage
    a wide variety of objects and states from sprite loading to animations.
*/

/**
\mainpage Pictel 2d Game Engine

# Short Description

Simply put - it's a 2D game pixel-engine written in C++ that, in theory, should be compatible with MacOS/iOS,
Windows & Linux. Most of the engine is platform agnostic. Only a small, specific parts of this software deal
with the target platform like the actual renderer.

This is a work in progress. Work done in no particular order and no set end-goal in mind.
There's some metal in C++ implementation here. Some sprite management. Some exposed C++ classes for scripting.
In the worse case scenario maybe it helps someone that dreams of building their own game engine from scratch ;)

# Long Description

It's a C++ based renderer with backend written (so far) for iOS/TVOS and macOS.
There's some platform specific functionality like the `virtual gamepad` that works
on iOS only, some gamepad support for macOS as well and, once I get to it, the same
will happen for Windows & Linux.

Exposed functionality, in form of C++ abstract classes (interfaces), is available
to the actual game scripts. The main github branch includes the sample code (so far
only Xcode/macOS due to convenience  and lack of time).

Some stuff is there purely for convenience, other (like the Apple provided graphics file
reader) should soon be replaced with their own, implementation.

The project also uses Pictel-sound, a sound library, that relies on OGG/Vorbis (complied
by yours truly for macOS/Windows), that in turn, sometimes, uses miniaudio.

# Completness

Is none at the moment. But maybe... in the future, might increase to a point above zero ;)

# Scripting interface quick-access.

See [Init params](doxygen_ini.md) to get a list possible ini params.

See [Command Line parameters](doxygen_executable.md) to get a list of command-line parameters.

See \ref API_GLOBALS "Exposed Functionality" for available classes & functions that can be used in
the game scripts.

See [Font Management](doxygen_fonts.md) to learn how to render texts.

See [Sound Management](doxygen_sounds.md) to learn how to play OGG/Vorbis files.

See [Animation](doxygen_animation.md) to learn basic animation.

*/


#endif /* doxygen_main_h */
