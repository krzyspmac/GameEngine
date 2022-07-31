//
//  system_utils_mac.cpp
//  Engine
//
//  Created by krzysp on 31/07/2022.
//

#include "system_utils_mac.hpp"
#import <Foundation/Foundation.h>

using namespace engine;

int FileUtilsMac::GetCurrentFolder(std::string& out)
{
    NSBundle* bundle = [NSBundle mainBundle];
    NSString* resourceDirectoryPath = [bundle bundlePath];
    NSString* path = [resourceDirectoryPath stringByAppendingString: @"/Contents/Resources"];

    out = [path cStringUsingEncoding:NSUTF8StringEncoding];
    return -1;
}
