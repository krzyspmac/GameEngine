//
//  AppDelegate.h
//  RendererAppSDL
//
//  Created by krzysp on 20/12/2021.
//

#if TARGET_IOS
#include <UIKit/UIKit.h>
#else
#include <Cocoa/Cocoa.h>
#endif

@interface AppDelegate : NSObject

#if TARGET_IOS
#else
<NSApplicationDelegate>
#endif

@end

