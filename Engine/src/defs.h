//
//  defs.h
//  RendererAppSDL
//
//  Created by krzysp on 21/12/2021.
//

#ifndef defs_h
#define defs_h

#define SHOW_FPS        1   /* shows the FPS on the screen */
#define SHOW_CONSOLE    1

#if defined(TARGET_IOS) || defined(TARGET_TVOS)
    #define TARGET_IOS  1
#else
    #define TARGET_OSX  1
#endif

#endif /* defs_h */
