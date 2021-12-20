//
//  file_access.cpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#include "file_access.hpp"

#ifdef __APPLE__
#import <Cocoa/Cocoa.h>
#endif

namespace engine
{

void FileAccess::getBundledFilepath(const char *value)
{
#ifdef __APPLE__
    NSBundle *mainBundle = [NSBundle mainBundle];

    NSString *filename = [[NSString alloc] initWithCharactersNoCopy:(unichar*)value length:strlen(value) freeWhenDone:NO];
    NSString *path = [mainBundle pathForResource:filename ofType:nil];

    [path UTF8String];
#endif
};

};
