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

std::string FileAccess::getBundlePath()
{
    return "";
}

std::string FileAccess::getBundledFilepath(const char *value)
{
#ifdef __APPLE__
    NSBundle *mainBundle = [NSBundle mainBundle];

    NSString *filename = [[NSString alloc] initWithUTF8String:value];
    NSString *path = [mainBundle pathForResource:filename ofType:nil];

    std::string cString = std::string(path.UTF8String);

    return cString;
#endif
};

};
