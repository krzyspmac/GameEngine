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

@interface RendererEntryViewController : PlatformViewController <MTKViewDelegate>
@end

#endif
