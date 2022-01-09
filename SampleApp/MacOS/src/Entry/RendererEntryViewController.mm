//
//  PlatformViewController.m
//  SampleApp
//
//  Created by krzysp on 09/01/2022.
//

#import "RendererEntryViewController.h"
#include "RendererEntryMetal.hpp"

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


@implementation RendererEntryViewController
{
    MTKView *_view;
    id<MTLDevice> _device;

//
//    AAPLRenderer *_renderer;
    engine::RendererEntryMetal *_entryMetal;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    _device = MTLCreateSystemDefaultDevice();
    _device = _view.device;


        // Load all the shader files with a .metal file extension in the project.
        id<MTLLibrary> defaultLibrary = [_device newDefaultLibrary];

        id<MTLFunction> vertexFunction = [defaultLibrary newFunctionWithName:@"vertexShader"];
        id<MTLFunction> fragmentFunction = [defaultLibrary newFunctionWithName:@"fragmentShader"];

        // Configure a pipeline descriptor that is used to create a pipeline state.
        MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
        pipelineStateDescriptor.label = @"Simple Pipeline";
        pipelineStateDescriptor.vertexFunction = vertexFunction;
        pipelineStateDescriptor.fragmentFunction = fragmentFunction;
        pipelineStateDescriptor.colorAttachments[0].pixelFormat = _view.colorPixelFormat;

//    [_device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor];



    _entryMetal = new engine::RendererEntryMetal();
    _entryMetal->Create((MTL::PixelFormat)_view.colorPixelFormat);

//    // Set the view to use the default device
//    _view = (MTKView *)self.view;
//
//    _view.device = MTLCreateSystemDefaultDevice();
//    NSAssert(_view.device, @"Metal is not supported on this device");
//
//    // Initialize the renderer with the view size
//    [self mtkView:_view drawableSizeWillChange:_view.drawableSize];
//
//    _view.delegate = self;
}
//
//#pragma mark - MTKViewDelegate
//
//- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
//{
//
//}
//
//- (void)drawInMTKView:(nonnull MTKView *)view
//{
//};

@end
