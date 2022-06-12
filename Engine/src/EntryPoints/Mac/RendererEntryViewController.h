//
//  PlatformViewController.h
//  SampleApp
//
//  Created by krzysp on 09/01/2022.
//

#pragma once

#ifndef __PLARTFORM_METAL_H__
#define __PLARTFORM_METAL_H__

#if defined(TARGET_IOS) || defined(TARGET_TVOS)
    #import <UIKit/UIKit.h>
    #include <MetalKit/MetalKit.h>
    #include <Foundation/Foundation.hpp>
    #include <Metal/Metal.hpp>
    #include <QuartzCore/QuartzCore.hpp>
    #define PlatformViewController UIViewController
#else
    #import <Cocoa/Cocoa.h>
    #include <MetalKit/MetalKit.h>
    #include <Foundation/Foundation.hpp>
    #include <Metal/Metal.hpp>
    #include <QuartzCore/QuartzCore.hpp>
    #define PlatformViewController NSViewController
#endif

#include <stdio.h>
#include "common.h"
#include "defs.h"
#include "file_access.hpp"
#include "scripting_engine.hpp"
#include "event_provider.hpp"
#include "engine.hpp"
#include "common_engine_impl.h"
#include "texture_target_metal.hpp"
#include "console_renderer.h"
#include "console_app_renderer_mac.hpp"
#include "file_access_provider.h"
#include "engine_provider_interface.h"
#include "scripting_engine_provider_interface.h"
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
    engine::ScriptingEngineI *m_scriptingEngine;
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
@property (weak) NSWindow *parentWindow;
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
