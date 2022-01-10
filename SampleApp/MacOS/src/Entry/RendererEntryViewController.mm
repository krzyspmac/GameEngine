//
//  PlatformViewController.m
//  SampleApp
//
//  Created by krzysp on 09/01/2022.
//

#import "RendererEntryViewController.h"
#include "RendererEntryMetal.hpp"
#include "AAPLShaderTypes.h"

//#define NS_PRIVATE_IMPLEMENTATION
//#define CA_PRIVATE_IMPLEMENTATION
//#define MTL_PRIVATE_IMPLEMENTATION
//#include <Foundation/Foundation.hpp>
//#include <Metal/Metal.hpp>
//#include <QuartzCore/QuartzCore.hpp>

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include <Metal/Metal.hpp>

//#include "MTKViewWrapper.hpp"

void Draw(MTL::CommandQueue *_commandQueue, MTL::RenderPipelineState *_pipelineState, MTL::RenderPassDescriptor *renderPassDescriptor, MTL::Drawable *currentDrawable, double x, double y, std::function<MTL::Drawable*(void)> lambda)
;

using namespace engine;

@implementation RendererEntryViewController
{
    /** Current MTL device. */
    MTL::Device * _deviceEx;

    engine::RendererEntryMetal *_entryMetal;



    MTKView *mtkView;

    id<MTLDevice> _device;

    // The render pipeline generated from the vertex and fragment shaders in the .metal shader file.
    id<MTLRenderPipelineState> _pipelineState;

    // The command queue used to pass commands to the device.
    id<MTLCommandQueue> _commandQueue;

    // The current size of the view, used as an input to the vertex shader.
    vector_uint2 _viewportSize;


}

- (void)viewDidLoad
{
    [super viewDidLoad];

    /*
    _device = MTL::CreateSystemDefaultDevice();
    NSAssert(_device, @"Metal is not supported on this device");

    MTKView *mtkView = (MTKView *)self.view;
    mtkView.device = (__bridge id)_device;//type;
    mtkView.delegate = self;

    _entryMetal = new engine::RendererEntryMetal();
    _entryMetal->Create((MTL::PixelFormat)mtkView.colorPixelFormat, _device);
    [self mtkView:mtkView drawableSizeWillChange:mtkView.drawableSize];
     */

    _deviceEx = MTL::CreateSystemDefaultDevice();
//    _device = MTLCreateSystemDefaultDevice();

    mtkView = (MTKView*)self.view;
    mtkView.device = (__bridge id)_deviceEx; //MTLCreateSystemDefaultDevice();
//    mtkView.device = _device;
    mtkView.delegate = self;


    _entryMetal = new engine::RendererEntryMetal();
    _entryMetal->Create((MTL::PixelFormat)mtkView.colorPixelFormat, _deviceEx);
//    _entryMetal->Create((MTL::PixelFormat)mtkView.colorPixelFormat, (__bridge MTL::Device*)_device);
//







    NSError *error;

    // Load all the shader files with a .metal file extension in the project.
    id<MTLLibrary> defaultLibrary = [mtkView.device newDefaultLibrary];

    id<MTLFunction> vertexFunction = [defaultLibrary newFunctionWithName:@"vertexShader"];
    id<MTLFunction> fragmentFunction = [defaultLibrary newFunctionWithName:@"fragmentShader"];

    // Configure a pipeline descriptor that is used to create a pipeline state.
    MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
    pipelineStateDescriptor.label = @"Simple Pipeline";
    pipelineStateDescriptor.vertexFunction = vertexFunction;
    pipelineStateDescriptor.fragmentFunction = fragmentFunction;
    pipelineStateDescriptor.colorAttachments[0].pixelFormat = mtkView.colorPixelFormat;

    _pipelineState = [mtkView.device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor
                                                             error:&error];

    // Pipeline State creation could fail if the pipeline descriptor isn't set up properly.
    //  If the Metal API validation is enabled, you can find out more information about what
    //  went wrong.  (Metal API validation is enabled by default when a debug build is run
    //  from Xcode.)
    NSAssert(_pipelineState, @"Failed to create pipeline state: %@", error);

    // Create the command queue
    _commandQueue = [mtkView.device newCommandQueue];




    [self mtkView:mtkView drawableSizeWillChange:mtkView.drawableSize];


}
//
#pragma mark - MTKViewDelegate

- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{
    _entryMetal->DrawableSizeWillChange(size.width, size.height);
    _viewportSize.x = size.width;
    _viewportSize.y = size.height;
}

- (void)drawInMTKView:(nonnull MTKView *)view
{
    MTL::RenderPassDescriptor *ref = (__bridge MTL::RenderPassDescriptor*)view.currentRenderPassDescriptor;
    MTL::Drawable *drawable = (__bridge MTL::Drawable*)view.currentDrawable;
    MTL::CommandQueue *commandQueue = (__bridge MTL::CommandQueue*)_commandQueue;
    MTL::RenderPipelineState *pipelineState = (__bridge MTL::RenderPipelineState*)_pipelineState;
    _entryMetal->Draw(commandQueue, pipelineState, ref, drawable, [&]{
        MTL::Drawable *drawable = (__bridge MTL::Drawable*)view.currentDrawable;
        return drawable;
    });


//    static const AAPLVertex triangleVertices[] =
//    {
//        // 2D positions,    RGBA colors
//        { {  250,  -250 }, { 1, 0, 0, 1 } },
//        { { -250,  -250 }, { 0, 1, 0, 1 } },
//        { {    0,   250 }, { 0, 0, 1, 1 } },
//    };
//
//    // Create a new command buffer for each render pass to the current drawable.
//    id<MTLCommandBuffer> commandBuffer = [_commandQueue commandBuffer];
//    commandBuffer.label = @"MyCommand";
//
//    // Obtain a renderPassDescriptor generated from the view's drawable textures.
//    MTLRenderPassDescriptor *renderPassDescriptor = view.currentRenderPassDescriptor;
//
//    if(renderPassDescriptor != nil)
//    {
//        // Create a render command encoder.
//        id<MTLRenderCommandEncoder> renderEncoder =
//        [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
//        renderEncoder.label = @"MyRenderEncoder";
//
//        // Set the region of the drawable to draw into.
//        double x = _viewportSize.x;
//        double y = _viewportSize.y;
//        [renderEncoder setViewport:(MTLViewport){0.0, 0.0, x, y, 0.0, 1.0 }];
//
//        [renderEncoder setRenderPipelineState:_pipelineState];
//
//        // Pass in the parameter data.
//        [renderEncoder setVertexBytes:triangleVertices
//                               length:sizeof(triangleVertices)
//                              atIndex:AAPLVertexInputIndexVertices];
//
//        [renderEncoder setVertexBytes:&_viewportSize
//                               length:sizeof(_viewportSize)
//                              atIndex:AAPLVertexInputIndexViewportSize];
//
//        // Draw the triangle.
//        [renderEncoder drawPrimitives:MTLPrimitiveTypeTriangle
//                          vertexStart:0
//                          vertexCount:3];
//
//        [renderEncoder endEncoding];
//
//        // Schedule a present once the framebuffer is complete using the current drawable.
//        [commandBuffer presentDrawable:view.currentDrawable];
//    }
//
//    // Finalize rendering here & push the command buffer to the GPU.
//    [commandBuffer commit];






//    static const AAPLVertex triangleVertices[] =
//    {
//        // 2D positions,    RGBA colors
//        { {  250,  -250 }, { 1, 0, 0, 1 } },
//        { { -250,  -250 }, { 0, 1, 0, 1 } },
//        { {    0,   250 }, { 0, 0, 1, 1 } },
//    };
//
//    // Create a new command buffer for each render pass to the current drawable.
//    id<MTLCommandBuffer> commandBuffer = [_commandQueue commandBuffer];
//    commandBuffer.label = @"MyCommand";
//
//    // Obtain a renderPassDescriptor generated from the view's drawable textures.
//    MTLRenderPassDescriptor *renderPassDescriptor = view.currentRenderPassDescriptor;
//
//    if(renderPassDescriptor != nil)
//    {
//        id<MTLRenderCommandEncoder> renderEncoder =
//        [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
//
//        MTL::RenderCommandEncoder *renderEncoderEx = (__bridge MTL::RenderCommandEncoder*)renderEncoder;
//
//        // Set the region of the drawable to draw into.
//        double x = _viewportSize.x;
//        double y = _viewportSize.y;
//        MTL::Viewport viewport = {0.0, 0.0, x, y, 0.0, 1.0};
//        renderEncoderEx->setViewports(&viewport, 1);
//
//        renderEncoderEx->setRenderPipelineState((__bridge MTL::RenderPipelineState*)_pipelineState);
//
//        // Pass in the parameter data.
//        renderEncoderEx->setVertexBytes(triangleVertices, sizeof(triangleVertices), AAPLVertexInputIndexVertices);
//        renderEncoderEx->setVertexBytes(&_viewportSize, sizeof(_viewportSize), AAPLVertexInputIndexViewportSize);
//        renderEncoderEx->drawPrimitives(MTL::PrimitiveTypeTriangle, (NS::UInteger)0, (NS::UInteger)3);
//
//        renderEncoderEx->endEncoding();
//
//        // Schedule a present once the framebuffer is complete using the current drawable.
//        [commandBuffer presentDrawable:view.currentDrawable];
//    }
//
//    // Finalize rendering here & push the command buffer to the GPU.
//    [commandBuffer commit];





//    static const AAPLVertex triangleVertices[] =
//    {
//        // 2D positions,    RGBA colors
//        { {  250,  -250 }, { 1, 0, 0, 1 } },
//        { { -250,  -250 }, { 0, 1, 0, 1 } },
//        { {    0,   250 }, { 0, 0, 1, 1 } },
//    };
//
//    // Create a new command buffer for each render pass to the curernt drawable.
//    auto commandBuffer = ((__bridge MTL::CommandQueue*)_commandQueue)->commandBuffer();
//
//    // Obtain a renderPassDescriptor generated from the view's drawable textures.
//    MTL::RenderPassDescriptor *renderPassDescriptor = (__bridge MTL::RenderPassDescriptor*)view.currentRenderPassDescriptor;
//
//    if (renderPassDescriptor != nullptr)
//    {
//        // Create a render command encoder.
//        auto renderEncoder = commandBuffer->renderCommandEncoder(renderPassDescriptor);
//
//        // Set the region of the drawable to draw into.
//        double x = _viewportSize.x;
//        double y = _viewportSize.y;
//        MTL::Viewport viewport = {0.0, 0.0, x, y, 0.0, 1.0};
//        renderEncoder->setViewports( &viewport, 1 );
//
//        // Set pipeline state
//        renderEncoder->setRenderPipelineState((__bridge MTL::RenderPipelineState*)_pipelineState);
//
//        // Pass in the parameter data.
//        renderEncoder->setVertexBytes(triangleVertices, sizeof(triangleVertices), AAPLVertexInputIndexVertices);
//        renderEncoder->setVertexBytes(&_viewportSize, sizeof(_viewportSize), AAPLVertexInputIndexViewportSize);
//
//        // Draw the triangle
//        renderEncoder->drawPrimitives(MTL::PrimitiveTypeTriangle, (NS::UInteger)0, (NS::UInteger)3);
//
//        renderEncoder->endEncoding();
//
//        // Schedule a present once the framebuffer is complete using the current drawable.
//        commandBuffer->presentDrawable((__bridge MTL::Drawable*)view.currentDrawable);
//    }
//
//    commandBuffer->commit();

    {
        MTL::RenderPassDescriptor *ref = (__bridge MTL::RenderPassDescriptor*)view.currentRenderPassDescriptor;
        MTL::Drawable *drawable = (__bridge MTL::Drawable*)view.currentDrawable;
        MTL::CommandQueue *commandQueue = (__bridge MTL::CommandQueue*)_commandQueue;
        MTL::RenderPipelineState *pipelineState = (__bridge MTL::RenderPipelineState*)_pipelineState;
        Draw(commandQueue, pipelineState, ref, drawable, _viewportSize.x, _viewportSize.y, [&]{
            MTL::Drawable *drawable = (__bridge MTL::Drawable*)view.currentDrawable;
            return drawable;
        });

    }

};


void Draw(MTL::CommandQueue *_commandQueue, MTL::RenderPipelineState *_pipelineState, MTL::RenderPassDescriptor *renderPassDescriptor, MTL::Drawable *currentDrawable, double x, double y, std::function<MTL::Drawable*(void)> lambda)
{
//    static const AAPLVertex triangleVertices[] =
//    {
//        // 2D positions,    RGBA colors
//        { {  250,  -250 }, { 1, 0, 0, 1 } },
//        { { -250,  -250 }, { 0, 1, 0, 1 } },
//        { {    0,   250 }, { 0, 0, 1, 1 } },
//    };
//
//    // Create a new command buffer for each render pass to the curernt drawable.
//    auto commandBuffer = (_commandQueue)->commandBuffer();
//
//    // Obtain a renderPassDescriptor generated from the view's drawable textures.
////    MTL::RenderPassDescriptor *renderPassDescriptor = (__bridge MTL::RenderPassDescriptor*)view.currentRenderPassDescriptor;
//
//    if (renderPassDescriptor != nullptr)
//    {
//        // Create a render command encoder.
//        auto renderEncoder = commandBuffer->renderCommandEncoder(renderPassDescriptor);
//
//        // Set the region of the drawable to draw into.
////        double x = _viewportSize.x;
////        double y = _viewportSize.y;
//        MTL::Viewport viewport = {0.0, 0.0, x, y, 0.0, 1.0};
//        renderEncoder->setViewports( &viewport, 1 );
//
//        vector_uint2 _viewportSize;
//        _viewportSize.x = x;
//        _viewportSize.y = y;
//
//        // Set pipeline state
//        renderEncoder->setRenderPipelineState(_pipelineState);
//
//        // Pass in the parameter data.
//        renderEncoder->setVertexBytes(triangleVertices, sizeof(triangleVertices), AAPLVertexInputIndexVertices);
//        renderEncoder->setVertexBytes(&_viewportSize, sizeof(_viewportSize), AAPLVertexInputIndexViewportSize);
//
//        // Draw the triangle
//        renderEncoder->drawPrimitives(MTL::PrimitiveTypeTriangle, (NS::UInteger)0, (NS::UInteger)3);
//
//        renderEncoder->endEncoding();
//
//        // Schedule a present once the framebuffer is complete using the current drawable.
//        commandBuffer->presentDrawable(currentDrawable);
//    }
//
//    commandBuffer->commit();

}

@end
