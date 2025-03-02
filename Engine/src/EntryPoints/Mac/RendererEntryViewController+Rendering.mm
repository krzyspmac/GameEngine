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

#import "RendererEntryViewController.h"
#import "engine.hpp"
#include "defs.h"

@implementation RendererEntryViewController (Rendering)

- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{
    density = [self density];

    viewportSize.x = size.width;
    viewportSize.y = size.height;
    printf("size = %f, %f\n", size.width, size.height);

    [self setupMouseMovedEvents];

    if (density > 0)
    {
        ENGINE().getEngineState().SendScreenSizeChangeEvent(
            { static_cast<int>(size.width), static_cast<int>(size.height) }
          , density
        );
    }
}

- (void)drawInMTKView:(nonnull MTKView *)view
{
    /** The main engine */
    auto &engine = ENGINE();

    /** Engine state */
    auto& engineSetup = engine.GetEngineSetup();

    /** The main engine provider */
    auto& provider = engine.getProvider();

    /** Update the engine if needed*/
    m_engine->SetViewportScale(density);

    /** Recreate the offscreen texture if needed */
    desiredFramebufferTextureSize.x = engineSetup.resolution.width;
    desiredFramebufferTextureSize.y = engineSetup.resolution.height;

    if ( engineSetup.isDirty )
    {
        [self recreateOffscreenRenderingPipeline];
        provider.SetDesiredViewport(desiredFramebufferTextureSize.x, desiredFramebufferTextureSize.y);
        affineScale = engineSetup.affineScale;
        engineSetup.isDirty = false;
    }

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
        [encoder setDepthStencilState:oscDepthStencilTest];

        /** Pass in the C++ bridge to the MTLRendererCommandEncoder */
        m_engineProvider->SetRendererCommandEncoder((__bridge MTL::RenderCommandEncoder*)encoder);
        m_engineProvider->SetViewportSize(desiredFramebufferTextureSize);

        /** Render the scene */
        m_engine->FrameBegin();
        m_engine->FrameDrawObjects();
        m_engine->FrameDrawTopObjects();
        m_engine->FrameEnd();

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

        static simd_float2 position = { 0.f, 0.f };
        static float alpha = { 1.f };

        engine::EngineScreenI &engineScreen = m_engine->getEngineScreen();

        auto screenOffset = engineScreen.GetPosition();
        position.x = screenOffset.x;
        position.y = screenOffset.y;
        alpha = engineScreen.GetAlpha();

        // Draw the offscreen texture
        [encoder setVertexBytes:&quadVertices length:sizeof(quadVertices) atIndex:AAPLVertexInputIndexVertices];
        [encoder setVertexBytes:&viewportSize length:sizeof(viewportSize) atIndex:AAPLVertexInputIndexWindowSize];
        [encoder setVertexBytes:&desiredFramebufferTextureSize length:sizeof(desiredFramebufferTextureSize) atIndex:AAPLVertexInputIndexViewportSize];
        [encoder setVertexBytes:&affineScale length:sizeof(affineScale) atIndex:AAPLVertexInputIndexObjectScale];
        [encoder setVertexBytes:&position length:sizeof(position) atIndex:AAPLVertexInputIndexObjectOffset];
        [encoder setFragmentTexture:oscTargetTexture atIndex:FragmentShaderIndexBaseColor];
        [encoder setFragmentBytes: &alpha length:sizeof(float) atIndex:FragmentShaderIndexBaseAlpha];
        [encoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:6];

        // Optionally draw the console
#if TARGET_OSX
#if SHOW_CONSOLE
        if (!m_consoleRenderer->GetConsoleHidden())
        {
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
        }
#endif
#endif
        /** End encoding */
        [encoder endEncoding];
    }

    /** Present the drawable */
    [commandBuffer presentDrawable:view.currentDrawable];

    /** Flush the queue */
    [commandBuffer commit];
};

- (float)density
{
#if TARGET_IOS
    return [UIScreen mainScreen].scale;
#else
    return self.parentWindow.backingScaleFactor;
#endif

}

@end
