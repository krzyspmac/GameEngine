//
//  file_access.cpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#include "file_access.hpp"

#if !TARGET_IOS
#include <Cocoa/Cocoa.h>
#else
#include <UIKit/UIKit.h>
#endif

#include <string>
#include <fstream>
#include <streambuf>
#include <filesystem>
#include <iostream>

#include "file_access_provider.h"

namespace fs = std::filesystem;

inline char separator()
{
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}

using namespace engine;

FileAccess::FileAccess()
    : FileAccessI(), m_gPackFile(NULL)
{

}

int FileAccess::LoadPackedFile(std::string filename)
{
    return 1;
}

int FileAccess::LoadDirectory(std::string directory)
{
    m_dataDirectory = directory;
    return 0;
}

std::string FileAccess::GetResourcesDirectory()
{
#ifdef __APPLE__
    NSBundle *mainBundle = [NSBundle mainBundle];
    NSString *resources = mainBundle.resourcePath;
    std::string cString = std::string(resources.UTF8String);
    return cString;
#endif
}

std::string FileAccess::GetFullPath(std::string filename)
{
    if (!m_dataDirectory.empty())
    {
        std::string fullPath(m_dataDirectory);

        if (fullPath[fullPath.length()] != separator()) {
            fullPath += separator();
            return(fullPath + filename);
        }
        else
        {
            return(fullPath + filename);
        }

        return (m_dataDirectory + filename);
    }
    else
    {
        return "";
    }
}

FileStreamI *FileAccess::GetAccess(std::string filename)
{
    return new FileMemoryBufferStreamFromFile(GetFullPath(filename));
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
