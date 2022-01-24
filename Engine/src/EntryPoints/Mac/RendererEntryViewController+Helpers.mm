//
//  RendererEntryViewController+RendererEntryViewController_Helpers.m
//  Engine
//
//  Created by krzysp on 24/01/2022.
//

#import "RendererEntryViewController.h"

@implementation RendererEntryViewController (Helpers)

- (NSString*)libraryPath
{
    NSBundle *mainBundle = [NSBundle mainBundle];
    NSURL *engineBundlePath = nil;

    engineBundlePath = [mainBundle URLForResource:@"Engine-Mac-Bundle" withExtension:@"bundle"];

    if (!engineBundlePath)
    {
        engineBundlePath = [mainBundle URLForResource:@"Engine-iOS-Bundle" withExtension:@"bundle"];
    }

    if (!engineBundlePath)
    {
        engineBundlePath = [mainBundle URLForResource:@"Engine-TV-Bundle" withExtension:@"bundle"];
    }

    NSBundle *engineBundle = [NSBundle bundleWithURL:engineBundlePath];

    NSString *metalLibPath = [engineBundle pathForResource:@"Engine-Mac-MetalLib" ofType:@"metallib"];
    if (!metalLibPath)
    {
        metalLibPath = [engineBundle pathForResource:@"Engine-iOS-MetalLib" ofType:@"metallib"];
    }
    if (!metalLibPath)
    {
        metalLibPath = [engineBundle pathForResource:@"Engine-TV-MetalLib" ofType:@"metallib"];
    }

    return metalLibPath;
}

@end
