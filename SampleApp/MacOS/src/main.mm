//
//  main.m
//  RendererAppSDL
//
//  Created by krzysp on 20/12/2021.
//

#import <Cocoa/Cocoa.h>

#pragma mark - Application Main Function

#if TARGET_MACOS

int main(int argc, const char * argv[])
{
    return NSApplicationMain(argc, argv);
}

#else

int main(int argc, char * argv[])
{
    @autoreleasepool
    {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
}

#endif
