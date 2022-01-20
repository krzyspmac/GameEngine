//
//  PlatformViewController.m
//  SampleApp
//
//  Created by krzysp on 09/01/2022.
//

#import "RendererEntryViewController.h"

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.h>

#include <stdio.h>
#include "common.h"
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

#define SCREEN_WIDTH  (1280)
#define SCREEN_HEIGHT (720)

#define USES_CONSOLE 0

using namespace engine;

@interface NSWindow (TitleBarHeight)
- (CGFloat) titlebarHeight;
@end

@interface RendererEntryViewController () <NSWindowDelegate>
@end

#pragma mark - Renderer Entry
@implementation RendererEntryViewController
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
    id<MTLFunction> oscVertexFunction;
    id<MTLFunction> oscFragmentFunction;
    MTLRenderPassDescriptor *oscRenderPassDescriptor;
    MTLRenderPipelineDescriptor *oscRenderePipelineDescriptor;
    id<MTLRenderPipelineState> oscPipelineState;

    id<MTLCommandQueue> commandQueue;
    vector_float2 viewportSize;
    vector_float2 desiredViewport;
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

    /** Events */
    NSTrackingArea *mouseTrackingArea;
}

#pragma mark - Lifecycle & Setup

- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    return self;
}

- (void)loadView
{
    self.view = [[MTKView alloc] initWithFrame:CGRectMake(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)];
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    [self setupView];
    [self setupScreenRendingPipeline];
    [self setupOffscreenRenderingPipeline];
    [self setupEngine];
    [self setupConsole];
    [self prepareEngine];

    [self mtkView:mtkView drawableSizeWillChange:mtkView.drawableSize];
}

- (void)viewDidAppear
{
    [self setupEvents];
    mtkView.window.delegate = self;
}

- (void)setupView
{
    mtkView = (MTKView*)self.view;
    mtkView.colorPixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;//.bgra8Unorm_srgb
}

- (void)setupEngine
{
    FileAccess *fa = new FileAccess();
    TextureManager *tm = new TextureManager();
    EngineProviderMetal *ep = new EngineProviderMetal();
    FontManager *fm  = new FontManager();
    ScriptingEngine *se = new ScriptingEngine();
    EventProvider *eventProvider = new EventProvider();
    EventsManager *eventsManager = new EventsManager(*eventProvider, *ep);
    CharacterManager *characteManager = new CharacterManager();
    SceneManager *sceneManager = new SceneManager();
    SpriteAtlasManager * spriteAtlasManager = new SpriteAtlasManager();
    SpriteRendererManager *sprireRendererManager = new SpriteRendererManager();
    ConsoleRenderer *consoleRenderer = new ConsoleRenderer();

    m_fileAccess = fa;
    m_textureManager = tm;
    m_engineProvider = ep;
    m_fontManager = fm;
    m_scriptingEngine = se;
    m_eventProvider = eventProvider;
    m_eventsManager = eventsManager;
    m_characterManager = characteManager;
    m_sceneManager = sceneManager;
    m_spriteAtlasManager = spriteAtlasManager;
    m_sprireRendererManager = sprireRendererManager;
    m_consoleRenderer = consoleRenderer;

    engine::Size viewportSize;
    viewportSize.width = SCREEN_WIDTH;
    viewportSize.height = SCREEN_HEIGHT;
    m_engine = new Engine(
                            *m_engineProvider
                          , *m_textureManager
                          , *m_fileAccess
                          , *m_fontManager
                          , *m_scriptingEngine
                          , *m_eventProvider
                          , *m_eventsManager
                          , *m_characterManager
                          , *m_sceneManager
                          , *m_spriteAtlasManager
                          , *m_sprireRendererManager
                          , *m_consoleRenderer
                          , viewportSize
                          );

    m_engineProvider->SetRendererDevice((__bridge MTL::Device*)device);
    m_engineProvider->SetDesiredViewport(SCREEN_WIDTH, SCREEN_HEIGHT);
    m_engineProvider->SetRenderingPipelineState((__bridge MTL::RenderPipelineState*)pipelineState);
}

- (void)setupConsole
{
    m_consoleRendererProvider = (ConsoleAppRendererMac*)m_consoleRenderer->GetPlarformRenderer();
    m_consoleRendererProvider->SetDevice((__bridge MTL::Device*)device);
    m_consoleRendererProvider->SetView(self.view);
}

- (void)prepareEngine
{
    m_engine->Setup();
}

- (void)setupScreenRendingPipeline
{
    device = MTLCreateSystemDefaultDevice();

    mtkView.device = device;
    mtkView.delegate = self;

    library = [device newDefaultLibrary];
    vertexFunction = [library newFunctionWithName:@"presenterVertexShader"];
    fragmentFunction = [library newFunctionWithName:@"presenterFragmentShader"];

    renderePipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    [renderePipelineDescriptor setLabel:@"Simple Pipeline"];
    [renderePipelineDescriptor setVertexFunction:vertexFunction];
    [renderePipelineDescriptor setFragmentFunction:fragmentFunction];

    MTLRenderPipelineColorAttachmentDescriptor *renderbufferAttachment = renderePipelineDescriptor.colorAttachments[0];
    [renderbufferAttachment setPixelFormat:mtkView.colorPixelFormat];
    [renderbufferAttachment setBlendingEnabled:YES];
    [renderbufferAttachment setRgbBlendOperation:MTLBlendOperationAdd];
    [renderbufferAttachment setAlphaBlendOperation:MTLBlendOperationAdd];
    [renderbufferAttachment setSourceRGBBlendFactor:MTLBlendFactorSourceAlpha];
    [renderbufferAttachment setSourceAlphaBlendFactor:MTLBlendFactorSourceAlpha];
    [renderbufferAttachment setDestinationRGBBlendFactor:MTLBlendFactorOneMinusSourceAlpha];
    [renderbufferAttachment setDestinationAlphaBlendFactor:MTLBlendFactorOneMinusSourceAlpha];

    NSError *error;
    pipelineState = [device newRenderPipelineStateWithDescriptor:renderePipelineDescriptor
                                                           error:&error];
    if (!pipelineState)
    {
        NSLog(@"Failed to create pipeline state: %@.", error);
        // TODO: error handling
    }

    commandQueue = [device newCommandQueue];
}

- (void)setupOffscreenRenderingPipeline
{
    oscVertexFunction = [library newFunctionWithName:@"vertexShader"];
    oscFragmentFunction = [library newFunctionWithName:@"fragmentShader"];

    MTLTextureDescriptor *texDescriptor = [MTLTextureDescriptor new];
    texDescriptor.textureType = MTLTextureType2D;
    texDescriptor.width = SCREEN_WIDTH;
    texDescriptor.height = SCREEN_HEIGHT;
    texDescriptor.pixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;//MTLPixelFormatRGBA8Unorm;
    texDescriptor.usage = MTLTextureUsageRenderTarget |
                          MTLTextureUsageShaderRead;

    oscTargetTexture = [device newTextureWithDescriptor:texDescriptor];

    oscRenderPassDescriptor = [MTLRenderPassDescriptor new];
    oscRenderPassDescriptor.colorAttachments[0].texture = oscTargetTexture;
    oscRenderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;//MTLLoadActionLoad;//MTLLoadActionClear;
    oscRenderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(1, 0, 1, 1);
    oscRenderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;

    MTLRenderPipelineDescriptor *oscRenderePipelineDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    oscRenderePipelineDescriptor.label = @"Offline Render Pipeline";
    oscRenderePipelineDescriptor.sampleCount = 1;
    oscRenderePipelineDescriptor.vertexFunction = oscVertexFunction;
    oscRenderePipelineDescriptor.fragmentFunction = oscFragmentFunction;

    MTLRenderPipelineColorAttachmentDescriptor *colorAttch = oscRenderePipelineDescriptor.colorAttachments[0];
    colorAttch.pixelFormat = oscTargetTexture.pixelFormat;
    colorAttch.blendingEnabled             = YES;
    colorAttch.rgbBlendOperation           = MTLBlendOperationAdd;
    colorAttch.alphaBlendOperation         = MTLBlendOperationAdd;
    colorAttch.sourceRGBBlendFactor        = MTLBlendFactorSourceAlpha;
    colorAttch.sourceAlphaBlendFactor      = MTLBlendFactorSourceAlpha;
    colorAttch.destinationRGBBlendFactor   = MTLBlendFactorOneMinusSourceAlpha;
    colorAttch.destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;

    NSError *error;
    oscPipelineState = [device newRenderPipelineStateWithDescriptor:oscRenderePipelineDescriptor error:&error];
    NSAssert(oscPipelineState, @"Failed to create pipeline state to render to screen: %@", error);
}

#pragma mark - MTKViewDelegate

- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{
    viewportSize.x = size.width;
    viewportSize.y = size.height;

    desiredViewport.x = SCREEN_WIDTH;
    desiredViewport.y = SCREEN_HEIGHT;
    printf("size = %f, %f\n", size.width, size.height);

    [self setupMouseMovedEvents];
}

- (void)drawInMTKView:(nonnull MTKView *)view
{
    /** Update the engine if needed*/
    m_engine->SetViewportScale(self.view.window.backingScaleFactor);

    /** Process events */
    m_engine->ProcessEvents();

    /** Process script. Script can alter the current rendering queue */
    m_engine->ProcessScript();

    /** Create a command buffer*/
    id<MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];
    commandBuffer.label = @"Command Buffer";

    /** Render the scene offscreen to a target texture */
    {
        id<MTLRenderCommandEncoder> encoder = [commandBuffer renderCommandEncoderWithDescriptor:oscRenderPassDescriptor];
        [encoder setRenderPipelineState:oscPipelineState];

        /** Pass in the C++ bridge to the MTLRendererCommandEncoder */
        m_engineProvider->SetRendererCommandEncoder((__bridge MTL::RenderCommandEncoder*)encoder);
        m_engineProvider->SetViewportSize(desiredViewport);

        /** Render the scene */
        m_engine->FrameBegin();
        m_engine->FrameDraw();

        [encoder endEncoding];
    }

    /** Render the offscreen texture to screen */
    MTLRenderPassDescriptor *drawableRenderPassDescriptor = view.currentRenderPassDescriptor;
    if(drawableRenderPassDescriptor != nil)
    {
        /** Create the encoder for the pass */
        id<MTLRenderCommandEncoder> encoder = [commandBuffer renderCommandEncoderWithDescriptor:drawableRenderPassDescriptor];
        encoder.label = @"Drawable Render Pass";
        [encoder setRenderPipelineState:pipelineState];

        static const AAPLVertex quadVertices[] =
        {
            // Positions     , Texture coordinates
            { {  1,  -1 },  { 1.0, 1.0 } },
            { { -1,  -1 },  { 0.0, 1.0 } },
            { { -1,   1 },  { 0.0, 0.0 } },

            { {  1,  -1 },  { 1.0, 1.0 } },
            { { -1,   1 },  { 0.0, 0.0 } },
            { {  1,   1 },  { 1.0, 0.0 } },
        };

        // Draw the offscreen texture
        [encoder setVertexBytes:&quadVertices length:sizeof(quadVertices) atIndex:AAPLVertexInputIndexVertices];
        [encoder setVertexBytes:&viewportSize length:sizeof(viewportSize) atIndex:AAPLVertexInputIndexWindowSize];
        [encoder setVertexBytes:&desiredViewport length:sizeof(desiredViewport) atIndex:AAPLVertexInputIndexViewportSize];
        [encoder setFragmentTexture:oscTargetTexture atIndex:AAPLTextureIndexBaseColor];
        [encoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:6];

        // Optionally draw the console
#if USES_CONSOLE
        [encoder pushDebugGroup:@"Dear ImGui rendering"];

        m_consoleRendererProvider->PrepareForFrame(
           self.view
         , (__bridge MTL::RenderPassDescriptor*)drawableRenderPassDescriptor
         , (__bridge MTL::CommandBuffer*)commandBuffer
         , (__bridge MTL::RenderCommandEncoder*)encoder
        );
        m_consoleRenderer->DoFrame();
        m_consoleRendererProvider->Render();

        [encoder popDebugGroup];
#endif
        /** End encoding */
        [encoder endEncoding];
    }

    /** Present the drawable */
    [commandBuffer presentDrawable:view.currentDrawable];

    /** Flush the queue */
    [commandBuffer commit];
};

#pragma mark - Events Handlers setup

- (void)setupEvents
{
    if (didSetupEvents) { return; };

    [self setupMouseClickEvents];
    [self setupMouseMovedEvents];
    [self setupKeyEvents];

    didSetupEvents = YES;
}

- (void)setupMouseClickEvents
{
    [NSEvent addLocalMonitorForEventsMatchingMask:NSEventMaskLeftMouseUp handler:^NSEvent * _Nullable(NSEvent * _Nonnull event) {
        self->m_engine->getEventProvider().PushMouseLeftUp();
        return event;
    }];
}

- (void)setupMouseMovedEvents
{
    NSView *view = self.view;
    if (mouseTrackingArea)
    {
        [view removeTrackingArea: mouseTrackingArea];
    }

    NSTrackingArea *area = [[NSTrackingArea alloc] initWithRect:view.bounds
                                                        options:NSTrackingActiveInKeyWindow|NSTrackingMouseMoved
                                                          owner:self
                                                       userInfo:nil];
    [view addTrackingArea:area];
}

- (void)setupKeyEvents
{
    // If we want to receive key events, we either need to be in the responder chain of the key view,
    // or else we can install a local monitor. The consequence of this heavy-handed approach is that
    // we receive events for all controls, not just Dear ImGui widgets. If we had native controls in our
    // window, we'd want to be much more careful than just ingesting the complete event stream.
    // To match the behavior of other backends, we pass every event down to the OS.
    NSEventMask eventMask = NSEventMaskKeyDown | NSEventMaskKeyUp | NSEventMaskFlagsChanged;
    [NSEvent addLocalMonitorForEventsMatchingMask:eventMask handler:^NSEvent * _Nullable(NSEvent *event)
    {
#if USES_CONSOLE
        self->m_consoleRendererProvider->HandleEvent(event);
#endif
        return event;
    }];
}

- (NSSize)windowWillResize:(NSWindow *)sender toSize:(NSSize)frameSize
{
//    float desiredViewportWidth = (float)SCREEN_WIDTH;
//    float desiredViewportHeight = (float)SCREEN_HEIGHT;
//    float aspectRatio = desiredViewportWidth/desiredViewportHeight;
//
//    CGRect mtkFrame = mtkView.frame;
//
//    float scaleX, scaleY, scale;
//    scaleX = frameSize.width / (float)SCREEN_WIDTH;
//    scaleY = frameSize.height / (float)SCREEN_HEIGHT;
//    scale = std::min(scaleX, scaleY);
//
//    if (desiredViewportWidth > desiredViewportHeight)
//    {
//        mtkFrame.size.width = frameSize.width;
//        mtkFrame.size.height = frameSize.width / aspectRatio;
//    }
//    else
//    {
//        exit(0); // not implemented
//    }
//
//    mtkFrame.size = CGSizeMake(100, 100);
//    mtkFrame.origin = CGPointMake(floor((frameSize.width - mtkFrame.size.width)/2), floor((frameSize.height - mtkFrame.size.height)/2));
////    mtkFrame.size = frameSize;
//    mtkView.frame = mtkFrame;
////    [mtkView setNeedsDisplay:YES];
    return frameSize;
}

#pragma mark - Other input processing

#if TARGET_OS_OSX

- (void)handle:(NSEvent*)event
{
#if USES_CONSOLE
    m_consoleRendererProvider->HandleEvent(event);
#endif
}

- (void)mouseMoved:(NSEvent *)event
{
    NSView    *view = self.view;
    CGRect    viewFrame = view.frame;
    CGPoint   locationInView = [view convertPoint:[event locationInWindow] fromView:nil];

    locationInView.y = viewFrame.size.height - locationInView.y;

    float xPer = locationInView.x / viewFrame.size.width;
    float yPer = locationInView.y / viewFrame.size.height;

    auto& viewport = m_engine->GetViewport();
    Origin locationInViewport;
    locationInViewport.x = (int)(xPer * (float)viewport.width);
    locationInViewport.y = (int)(yPer * (float)viewport.height);

    m_engine->getEventProvider().PushMouseLocation(locationInViewport);

    [self handle:event];
}

- (void)mouseDown:(NSEvent *)event           { [self handle:event]; }
- (void)rightMouseDown:(NSEvent *)event      { [self handle:event]; }
- (void)otherMouseDown:(NSEvent *)event      { [self handle:event]; }
- (void)mouseUp:(NSEvent *)event             { [self handle:event]; }
- (void)rightMouseUp:(NSEvent *)event        { [self handle:event]; }
- (void)otherMouseUp:(NSEvent *)event        { [self handle:event]; }
- (void)mouseDragged:(NSEvent *)event        { [self handle:event]; }
- (void)rightMouseMoved:(NSEvent *)event     { [self handle:event]; }
- (void)rightMouseDragged:(NSEvent *)event   { [self handle:event]; }
- (void)otherMouseMoved:(NSEvent *)event     { [self handle:event]; }
- (void)otherMouseDragged:(NSEvent *)event   { [self handle:event]; }
- (void)scrollWheel:(NSEvent *)event         { [self handle:event]; }

#endif


@end

#if defined(TARGET_IOS) || defined(TARGET_TVOS)
#else

@interface GameWindowController: NSWindowController
@end

@implementation GameWindowController

- (void)windowWillLoad
{
    [super windowWillLoad];
}

- (void)windowDidLoad
{
    [super windowDidLoad];
}

@end

#endif

#pragma mark - NSWindowAdditions

@implementation NSWindow (TitleBarHeight)
- (CGFloat) titlebarHeight
{
    return self.frame.size.height - [self contentRectForFrameRect: self.frame].size.height;
}
@end
