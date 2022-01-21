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


@interface RendererEntryViewController : PlatformViewController <MTKViewDelegate>
#if defined(TARGET_IOS) || defined(TARGET_TVOS)
#else
@property (weak) IBOutlet NSWindowController *windowController;
#endif
@end

#endif
