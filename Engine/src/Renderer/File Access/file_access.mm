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
#include "system_utils.hpp"
#include "ini_reader.hpp"
#include "easy.h"

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
    auto systemUtils = FileUtils::shared();

    std::string rpath("");
    if (systemUtils->GetCurrentFolder(rpath))
    {
        m_dataDirectory = replaceAll(directory, IniReader::Variables::rpath(), rpath);
    }
    else
    {
        LOGGER().Log("Could not get the rPath from the system. Will keep the local directiry as %s.", directory.c_str());
        m_dataDirectory = directory;
    }

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
        auto systemUtils = FileUtils::shared();
        std::string currentFolder("");
        if (systemUtils->GetCurrentFolder(currentFolder))
        {
            return currentFolder + separator() + filename;
        }
        else
        {
            return "";
        }
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
