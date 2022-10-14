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

#import "AppDelegate.h"
#import "RendererEntry.h"

@interface AppDelegate ()
#if TARGET_MACOS
@property (strong) IBOutlet NSWindow *window;
#elif TARGET_IOS
@property (strong) IBOutlet UIWindow *window;
#endif
@end

// Main initializer functions

void PictelScriptInit(void);
void PictelScriptFrameUpdate(void);

@implementation AppDelegate

#if TARGET_MACOS
- (instancetype)init
{
    if (self = [super init])
    {
        id<RendererViewControllerProtocol> rootViewController = [RendererEntry instantiate];

        self.window = [[NSWindow alloc] initWithContentRect:NSZeroRect
                                                  styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskMiniaturizable
                                                    backing:NSBackingStoreBuffered
                                                      defer:NO];
        rootViewController.parentWindow = self.window;
        rootViewController.gameEngienInitFnc = &PictelScriptInit;
        rootViewController.gameEngineFrameUpdteFnc = &PictelScriptFrameUpdate;
        self.window.contentViewController = (NSViewController*)rootViewController;
        [self.window orderFront:self];
        [self.window center];
        [self.window becomeKeyWindow];
    }
    return self;
}
#endif

#if TARGET_IOS

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary<UIApplicationLaunchOptionsKey,id> *)launchOptions
{
    UIViewController<RendererViewControllerProtocol> *rootViewController = (id)[RendererEntry instantiate];
    rootViewController.gameEngienInitFnc = &PictelScriptInit;
    rootViewController.gameEngineFrameUpdteFnc = &PictelScriptFrameUpdate;

    self.window = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
    self.window.rootViewController = rootViewController;
    [self.window makeKeyAndVisible];
    return YES;
}

#endif

#if TARGET_MACOS

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
}


- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    return YES;
}
#endif

#if TARGET_MACOS
- (BOOL)applicationSupportsSecureRestorableState:(NSApplication *)app {
    return YES;
}
#endif

@end
