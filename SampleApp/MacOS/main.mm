//
//  main.m
//  RendererAppSDL
//
//  Created by krzysp on 20/12/2021.
//

#import <Cocoa/Cocoa.h>
#include "RendererEntry.hpp"

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // Setup code that might create autoreleased objects goes here.
    }

    engine::RendererEntry entry;
    entry.main(argc, argv);

    return NSApplicationMain(argc, argv);
}
