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

#pragma once

#ifndef __PLARTFORM_METAL_H__
#define __PLARTFORM_METAL_H__

#if defined(TARGET_IOS) || defined(TARGET_TVOS)
    #import <UIKit/UIKit.h>
    #include <MetalKit/MetalKit.h>
    #include <Foundation/Foundation.hpp>
    #include <Metal/Metal.hpp>
    #include <QuartzCore/QuartzCore.hpp>
    #include <GameController/GameController.h>
    #define PlatformViewController GCEventViewController
#else
    #import <Cocoa/Cocoa.h>
    #include <MetalKit/MetalKit.h>
    #include <Foundation/Foundation.hpp>
    #include <Metal/Metal.hpp>
    #include <QuartzCore/QuartzCore.hpp>
    #include <GameController/GameController.h>
    #define PlatformViewController GCEventViewController
#endif

#include <stdio.h>
#include "script_entry_interface.hpp"
#include "common.h"
#include "defs.h"
#include "file_access.hpp"
#include "event_provider.hpp"
#include "engine.hpp"
#include "interfaces.h"
#include "texture_target_metal.hpp"
#include "console_renderer.h"
#include "console_app_renderer_mac.hpp"
#include "file_access_provider.h"
#include "engine_provider_interface.h"
#include "engine_interface.h"
#include "engine.hpp"
#include "events_manager.hpp"
#include "character_manager.hpp"
#include "scene_manager.hpp"
#include "sprite_atlas_manager.hpp"
#include "sprite_renderer_manager.hpp"
#include "console_renderer.h"
#include "texture_manager.hpp"
#include "font_manager.hpp"
#include "engine_provider_metal.hpp"
#include "AAPLShaderTypes.h"

#define INITIAL_SCREEN_WIDTH  320
#define INITIAL_SCREEN_HEIGHT 200

@interface RendererEntryViewController : PlatformViewController
{
    /** Metal related */
    id<MTLDevice> device;

    /** Onscreen rendering */
    id<MTLLibrary> library;
    id<MTLFunction> vertexFunction;
    id<MTLFunction> fragmentFunction;
    MTLRenderPipelineDescriptor *renderePipelineDescriptor;
    id<MTLRenderPipelineState> pipelineState;

    /** Offscreen rendering */
    id<MTLTexture> oscTargetTexture;
    id<MTLTexture> oscTargetDepthTexture;
    id<MTLFunction> oscVertexFunction;
    id<MTLFunction> oscFragmentFunction;
    id<MTLDepthStencilState> oscDepthStencilTest;
    MTLRenderPassDescriptor *oscRenderPassDescriptor;
    MTLRenderPipelineDescriptor *oscRenderePipelineDescriptor;
    id<MTLRenderPipelineState> oscPipelineState;

    id<MTLCommandQueue> commandQueue;
    vector_float2 viewportSize;
    MTKView *mtkView;

    /** Engine Related */
    engine::FileAccessI *m_fileAccess;
    engine::TextureManager *m_textureManager;
    engine::EngineProviderMetal *m_engineProvider;
    engine::FontManager *m_fontManager;
    engine::EventProviderI *m_eventProvider;
    engine::EventsManager *m_eventsManager;
    engine::CharacterManager *m_characterManager;
    engine::SceneManager *m_sceneManager;
    engine::SpriteAtlasManager *m_spriteAtlasManager;
    engine::SpriteRendererManager *m_sprireRendererManager;
    engine::ConsoleRenderer *m_consoleRenderer;
    engine::ConsoleAppRendererMac *m_consoleRendererProvider;
    engine::Engine *m_engine;

    /** Setup related*/
    BOOL didSetupEvents;
    float density;
    simd_float2 desiredFramebufferTextureSize;
    simd_float2 framebufferTextureSize;
    float affineScale;
    
    /** Events */
#if defined(TARGET_IOS) || defined(TARGET_TVOS)
#else
    NSTrackingArea *mouseTrackingArea;
#endif
}

#if defined(TARGET_IOS) || defined(TARGET_TVOS)
#else
@property (weak) IBOutlet NSWindowController *windowController;
@property (nonatomic, weak) NSWindow *parentWindow;
#endif

@property (nonatomic, assign) ScriptingFunctionVoid gameEngienInitFnc;
@property (nonatomic, assign) ScriptingFunctionVoid gameEngineFrameUpdteFnc;

#if USE_CONTROLLERS
@property (nonatomic, strong) GCController *controller;
#if TARGET_IOS
@property (nonatomic, strong) GCVirtualController *virtualController;
#endif

@property (nonatomic, copy) GCControllerDirectionPadValueChangedHandler leftThumbstickHandler;
@property (nonatomic, copy) GCControllerDirectionPadValueChangedHandler rightThumbstickHandler;
@property (nonatomic, copy) GCControllerDirectionPadValueChangedHandler dpadThumbstickHandler;

@property (nonatomic, copy) GCControllerButtonValueChangedHandler handlerButtonA;
@property (nonatomic, copy) GCControllerButtonValueChangedHandler handlerButtonB;
@property (nonatomic, copy) GCControllerButtonValueChangedHandler handlerButtonX;
@property (nonatomic, copy) GCControllerButtonValueChangedHandler handlerButtonY;

@property (nonatomic, copy) GCControllerButtonValueChangedHandler handlerButtonLeftShoulder;
@property (nonatomic, copy) GCControllerButtonValueChangedHandler handlerButtonLeftTrigger;

@property (nonatomic, copy) GCControllerButtonValueChangedHandler handlerButtonRightShoulder;
@property (nonatomic, copy) GCControllerButtonValueChangedHandler handlerButtonRightTrigger;

@property (nonatomic, copy) GCControllerButtonValueChangedHandler handlerButtonLeftThumbstickButton;
@property (nonatomic, copy) GCControllerButtonValueChangedHandler handlerButtonRightThumbstickButton;

@property (nonatomic, copy) GCControllerButtonValueChangedHandler handlerButtonMenu;
@property (nonatomic, copy) GCControllerButtonValueChangedHandler handlerButtonOptions;
#endif

- (void)recreateOffscreenRenderingPipeline;
@end

#endif

@interface RendererEntryViewController (Rendering) <MTKViewDelegate>
@end

@interface RendererEntryViewController (Events)
- (void)setupEvents;
- (void)setupMouseClickEvents;
- (void)setupMouseMovedEvents;
- (void)setupKeyEvents;
#if TARGET_OSX
- (void)handle:(NSEvent*)event;
#endif
@end

@interface RendererEntryViewController (Helpers)
- (NSString*)libraryPath;
@end
