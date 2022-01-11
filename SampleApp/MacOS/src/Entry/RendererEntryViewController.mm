//
//  PlatformViewController.m
//  SampleApp
//
//  Created by krzysp on 09/01/2022.
//

#import "RendererEntryViewController.h"
#include "RendererEntryMetal.hpp"
#include "AAPLShaderTypes.h"

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include <Metal/Metal.hpp>

using namespace engine;

@implementation RendererEntryViewController
{
    /** Current MTL device. */
    MTL::Device * _deviceEx;

    engine::RendererEntryMetal *_entryMetal;

    MTKView *mtkView;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    _deviceEx = MTL::CreateSystemDefaultDevice();

    mtkView = (MTKView*)self.view;
    mtkView.device = (__bridge id)_deviceEx;
    mtkView.delegate = self;

    _entryMetal = new engine::RendererEntryMetal();
    _entryMetal->Create((MTL::PixelFormat)mtkView.colorPixelFormat, _deviceEx);

    [self mtkView:mtkView drawableSizeWillChange:mtkView.drawableSize];
}

#pragma mark - MTKViewDelegate

- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{
    _entryMetal->DrawableSizeWillChange(size.width, size.height);
}

- (void)drawInMTKView:(nonnull MTKView *)view
{
    MTL::RenderPassDescriptor *ref = (__bridge MTL::RenderPassDescriptor*)view.currentRenderPassDescriptor;
    MTL::Drawable *drawable = (__bridge MTL::Drawable*)view.currentDrawable;
    _entryMetal->Draw(ref, drawable);
};

@end
