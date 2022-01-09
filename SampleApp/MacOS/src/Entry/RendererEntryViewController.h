//
//  PlatformViewController.h
//  SampleApp
//
//  Created by krzysp on 09/01/2022.
//

#if defined(TARGET_IOS) || defined(TARGET_TVOS)
@import UIKit;
    #define PlatformViewController UIViewController
#else
@import AppKit;
    #define PlatformViewController NSViewController
#endif

@import MetalKit;

@interface RendererEntryViewController : PlatformViewController

@end
