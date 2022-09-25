//
//  RendererEntryViewController+Protocol.h
//  Engine
//
//  Created by krzysp on 24/09/2022.
//

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
