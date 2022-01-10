//
//  RendererEntryMetal.cpp
//  SampleApp
//
//  Created by krzysp on 09/01/2022.
//

#include "RendererEntryMetal.hpp"

using namespace engine;

#define STR(x) NS::MakeConstantString(#x)

RendererEntryMetal::RendererEntryMetal()
{

}

void RendererEntryMetal::Create(MTL::PixelFormat pixelFormat, MTL::Device *device)
{
//    m_device = device;
//
//    m_library = m_device->newDefaultLibrary();
//    m_vertexFuntion = m_library->newFunction(NS::MakeConstantString("vertexShader"));
//    m_fragmentFunction = m_library->newFunction(NS::MakeConstantString("fragmentShader"));
//
//    m_renderePipelineDescriptor = MTL::RenderPipelineDescriptor::alloc()->init();
//    m_renderePipelineDescriptor->setLabel(NS::MakeConstantString("Simple Pipeline"));
//    m_renderePipelineDescriptor->setVertexFunction(m_vertexFuntion);
//    m_renderePipelineDescriptor->setFragmentFunction(m_fragmentFunction);
//    m_renderePipelineDescriptor->colorAttachments()->object(0)->setPixelFormat(pixelFormat);
//
//    NS::Error *error = nullptr;
//    m_pipelineState = m_device->newRenderPipelineState(m_renderePipelineDescriptor, &error);
//    if (m_pipelineState == nullptr)
//    {
//        printf("Failed to create pipeline state %s\n", error->description()->cString(NS::ASCIIStringEncoding));
//    }

//    NSAssert(m_pipelineState, @"Failed to create pipeline state: %@", error);
/*



 // Configure a pipeline descriptor that is used to create a pipeline state.
 MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
 pipelineStateDescriptor.label = @"Simple Pipeline";
 pipelineStateDescriptor.vertexFunction = vertexFunction;
 pipelineStateDescriptor.fragmentFunction = fragmentFunction;
 pipelineStateDescriptor.colorAttachments[0].pixelFormat = mtkView.colorPixelFormat;

 _pipelineState = [_device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor
                                                          error:&error];

 // Pipeline State creation could fail if the pipeline descriptor isn't set up properly.
 //  If the Metal API validation is enabled, you can find out more information about what
 //  went wrong.  (Metal API validation is enabled by default when a debug build is run
 //  from Xcode.)
 NSAssert(_pipelineState, @"Failed to create pipeline state: %@", error);

 */

//    m_commandQueue = m_device->newCommandQueue();
}

void RendererEntryMetal::DrawableSizeWillChange(float width, float height)
{
    m_viewportSize.x = width;
    m_viewportSize.y = height;
}

void RendererEntryMetal::Draw(MTL::CommandQueue *_commandQueue, MTL::RenderPipelineState *_pipelineState, MTL::RenderPassDescriptor *renderPassDescriptor, MTL::Drawable *currentDrawable, std::function<MTL::Drawable*(void)> lambda)
{


    static const AAPLVertex triangleVertices[] =
    {
        // 2D positions,    RGBA colors
        { {  250,  -250 }, { 1, 0, 0, 1 } },
        { { -250,  -250 }, { 0, 1, 0, 1 } },
        { {    0,   250 }, { 0, 0, 1, 1 } },
    };

    // Create a new command buffer for each render pass to the curernt drawable.
    auto commandBuffer = (_commandQueue)->commandBuffer();

    // Obtain a renderPassDescriptor generated from the view's drawable textures.
    if (renderPassDescriptor != nullptr)
    {
        // Create a render command encoder.
        auto renderEncoder = commandBuffer->renderCommandEncoder(renderPassDescriptor);

        // Set the region of the drawable to draw into.
        double x = m_viewportSize.x;
        double y = m_viewportSize.y;
        MTL::Viewport viewport = {0.0, 0.0, x, y, 0.0, 1.0};
        renderEncoder->setViewports( &viewport, 1 );

        // Set pipeline state
        renderEncoder->setRenderPipelineState(_pipelineState);

        // Pass in the parameter data.
        renderEncoder->setVertexBytes(triangleVertices, sizeof(triangleVertices), AAPLVertexInputIndexVertices);
        renderEncoder->setVertexBytes(&m_viewportSize, sizeof(m_viewportSize), AAPLVertexInputIndexViewportSize);

        // Draw the triangle
        renderEncoder->drawPrimitives(MTL::PrimitiveTypeTriangle, (NS::UInteger)0, (NS::UInteger)3);

        renderEncoder->endEncoding();

        // Schedule a present once the framebuffer is complete using the current drawable.
        commandBuffer->presentDrawable(currentDrawable);
    }

    commandBuffer->commit();




/*
 static const AAPLVertex triangleVertices[] =
 {
     // 2D positions,    RGBA colors
     { {  250,  -250 }, { 1, 0, 0, 1 } },
     { { -250,  -250 }, { 0, 1, 0, 1 } },
     { {    0,   250 }, { 0, 0, 1, 1 } },
 };

 // Create a new command buffer for each render pass to the current drawable.
 id<MTLCommandBuffer> commandBuffer = [_commandQueue commandBuffer];
 commandBuffer.label = @"MyCommand";

 // Obtain a renderPassDescriptor generated from the view's drawable textures.
 MTLRenderPassDescriptor *renderPassDescriptor = view.currentRenderPassDescriptor;

 if(renderPassDescriptor != nil)
 {
     // Create a render command encoder.
     id<MTLRenderCommandEncoder> renderEncoder =
     [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
     renderEncoder.label = @"MyRenderEncoder";

     // Set the region of the drawable to draw into.
     [renderEncoder setViewport:(MTLViewport){0.0, 0.0, _viewportSize.x, _viewportSize.y, 0.0, 1.0 }];

     [renderEncoder setRenderPipelineState:_pipelineState];

     // Pass in the parameter data.
     [renderEncoder setVertexBytes:triangleVertices
                            length:sizeof(triangleVertices)
                           atIndex:AAPLVertexInputIndexVertices];

     [renderEncoder setVertexBytes:&_viewportSize
                            length:sizeof(_viewportSize)
                           atIndex:AAPLVertexInputIndexViewportSize];

     // Draw the triangle.
     [renderEncoder drawPrimitives:MTLPrimitiveTypeTriangle
                       vertexStart:0
                       vertexCount:3];

//        [renderEncoder setFragmentTexture:<#(nullable id<MTLTexture>)#> atIndex:<#(NSUInteger)#>]

     [renderEncoder endEncoding];

     // Schedule a present once the framebuffer is complete using the current drawable.
     [commandBuffer presentDrawable:view.currentDrawable];
 }

 // Finalize rendering here & push the command buffer to the GPU.
 [commandBuffer commit];

 */

//    static const AAPLVertex triangleVertices[] =
//    {
//        // 2D positions,    RGBA colors
//        { {  250,  -250 }, { 1, 0, 0, 1 } },
//        { { -250,  -250 }, { 0, 1, 0, 1 } },
//        { {    0,   250 }, { 0, 0, 1, 1 } },
//    };
//
//    // Create a new command buffer for each render pass to the curernt drawable.
//    auto commandBuffer = _commandQueue->commandBuffer();
//    //commandBuffer->setLabel()
//
//    // Obtain a renderPassDescriptor generated from the view's drawable textures.
//    if (renderPassDescriptor != nullptr)
//    {
//        // Create a render command encoder.
//        auto renderEncoder = commandBuffer->renderCommandEncoder(renderPassDescriptor);
////        renderEncoder.label = @"MyRenderEncoder";
////        renderEncoder->setLabel(NS::MakeConstantString("MyRendererEncoder"));
//
//        // Set the region of the drawable to draw into.
//        MTL::Viewport viewport = {0.0, 0.0, m_viewportSize.width, m_viewportSize.height, 0.0, 1.0};
//        renderEncoder->setViewports( &viewport, 1 );
//
//        // Set pipeline state
//        renderEncoder->setRenderPipelineState(_pipelineState);
//
//        // Pass in the parameter data.
//        renderEncoder->setVertexBytes(triangleVertices, sizeof(triangleVertices), AAPLVertexInputIndexVertices);
//        renderEncoder->setVertexBytes(&m_viewportSize, sizeof(m_viewportSize), AAPLVertexInputIndexViewportSize);
//
//        // Draw the triangle
//        renderEncoder->drawPrimitives(MTL::PrimitiveTypeTriangle, (NS::UInteger)0, (NS::UInteger)3);
//
//        renderEncoder->endEncoding();
//
//        // Schedule a present once the framebuffer is complete using the current drawable.
//        commandBuffer->presentDrawable(lambda());
//    }
//
//    commandBuffer->commit();
}
