//
//  PlatformViewController.m
//  SampleApp
//
//  Created by krzysp on 09/01/2022.
//

#import "RendererEntryViewController.h"
#include "AAPLShaderTypes.h"

#include <Metal/Metal.hpp>
#include <MetalKit/MetalKit.h>

#include "file_access.hpp"
#include "scripting_engine.hpp"
#include "event_provider.hpp"
#include "engine.hpp"
#include "common_engine_impl.h"
#include "texture_target_metal.hpp"

#include "AAPLShaderTypes.h"

#define SCREEN_WIDTH  (1280)
#define SCREEN_HEIGHT (720)

using namespace engine;

@interface NSWindow (TitleBarHeight)
- (CGFloat) titlebarHeight;
@end

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
    engine::Engine *m_engine;

    /** Setup related*/
    BOOL didSetupEvents;

    /** Events */
    NSTrackingArea *mouseTrackingArea;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    [self setupView];
    [self setupScreenRendingPipeline];
    [self setupOffscreenRenderingPipeline];
    [self setupEngine];
    [self prepareEngine];

    [self mtkView:mtkView drawableSizeWillChange:mtkView.drawableSize];
}

- (void)viewDidAppear
{
    [self setupEvents];
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

    /** Create a command buffer*/
    id<MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];
    commandBuffer.label = @"Command Buffer";

    /** Render the scene offscreen to a target texture */
    {
        /** Create the encoder for the pass */
        id<MTLRenderCommandEncoder> encoder = [commandBuffer renderCommandEncoderWithDescriptor:oscRenderPassDescriptor];
        [encoder setRenderPipelineState:oscPipelineState];

        /** Pass in the C++ bridge to the MTLRendererCommandEncoder */
        m_engineProvider->SetRendererCommandEncoder((__bridge MTL::RenderCommandEncoder*)encoder);
        m_engineProvider->SetViewportSize(desiredViewport);

        /** Render the scene */
        m_engine->FrameBegin();
        m_engine->FrameDraw();

        /** End encoding */
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

        [encoder setVertexBytes:&quadVertices
                         length:sizeof(quadVertices)
                        atIndex:AAPLVertexInputIndexVertices];

        [encoder setVertexBytes:&viewportSize
                         length:sizeof(viewportSize)
                        atIndex:AAPLVertexInputIndexWindowSize];

        [encoder setVertexBytes:&desiredViewport
                         length:sizeof(desiredViewport)
                        atIndex:AAPLVertexInputIndexViewportSize];

        // Set the offscreen texture as the source texture.
        [encoder setFragmentTexture:oscTargetTexture atIndex:AAPLTextureIndexBaseColor];

        // Draw quad with rendered texture.
        [encoder drawPrimitives:MTLPrimitiveTypeTriangle
                    vertexStart:0
                    vertexCount:6];

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

#pragma mark - Events Handlers

- (void)mouseMoved:(NSEvent *)event
{
    CGPoint   locationInWindow = [event locationInWindow];
    NSView    *view = self.view;
    NSWindow  *window = view.window;
    CGRect    windowFrame = window.frame;

    windowFrame = [window convertRectToBacking:windowFrame];
    locationInWindow = [view convertPointToBacking:locationInWindow];
    locationInWindow.y = windowFrame.size.height - locationInWindow.y - window.titlebarHeight * 2;

    auto& viewport = m_engine->GetViewport();
    float xPer = locationInWindow.x / windowFrame.size.width;
    float yPer = locationInWindow.y / windowFrame.size.height;

    Origin locationInViewport;
    locationInViewport.x = (int)(xPer * (float)viewport.width);
    locationInViewport.y = (int)(yPer * (float)viewport.height);

    m_engine->getEventProvider().PushMouseLocation(locationInViewport);
}

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
