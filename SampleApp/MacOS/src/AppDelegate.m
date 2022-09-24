//
//  AppDelegate.m
//  RendererAppSDL
//
//  Created by krzysp on 20/12/2021.
//

#import "AppDelegate.h"
#import "RendererEntry.h"
#import "scripting_exposed_interface.h"

void rust_function(void);

@interface AppDelegate ()

#if TARGET_MACOS
@property (strong) IBOutlet NSWindow *window;
#elif TARGET_IOS
@property (strong) IBOutlet UIWindow *window;
#endif

@end

/// Must-have initializer functions
void pictel_game_script_init(void);
void pictel_game_script_frame_update(void);

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
        rootViewController.gameEngienInitFnc = &pictel_game_script_init;
        rootViewController.gameEngineFrameUpdteFnc = &pictel_game_script_frame_update;
        self.window.contentViewController = (NSViewController*)rootViewController;
        [self.window orderFront:self];
        [self.window center];
        [self.window becomeKeyWindow];

        pictel_game_script_init();

    }
    return self;
}
#endif

#if TARGET_IOS

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary<UIApplicationLaunchOptionsKey,id> *)launchOptions
{
    PlatformViewController *rootViewController = [[RendererEntryViewController alloc] initWithNibName:nil bundle:nil];
    self.window = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
    self.window.rootViewController = rootViewController;
    [self.window makeKeyAndVisible];
//    UIViewController *rootViewController = [[AppViewController alloc] init];
//    self.window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];
//    self.window.rootViewController = rootViewController;
//    [self.window makeKeyAndVisible];

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
