// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef RendererEntryViewController_Protocol_h
#define RendererEntryViewController_Protocol_h

#if defined(TARGET_IOS) || defined(TARGET_TVOS)
    #import <UIKit/UIKit.h>
    #include <Foundation/Foundation.h>
    #include <GameController/GameController.h>
    #define PlatformViewController GCEventViewController
#else
    #import <Cocoa/Cocoa.h>
    #include <Foundation/Foundation.h>
    #include <GameController/GameController.h>
    #define PlatformViewController GCEventViewController
#endif

#include "script_entry_interface.hpp"

@protocol RendererViewControllerProtocol <NSObject>

@property (nonatomic, weak) NSWindow *parentWindow;
@property (nonatomic, assign) ScriptingFunctionVoid gameEngienInitFnc;
@property (nonatomic, assign) ScriptingFunctionVoid gameEngineFrameUpdteFnc;

@end

#endif /* RendererEntryViewController_Protocol_h */
