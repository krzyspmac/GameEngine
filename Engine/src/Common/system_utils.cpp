//
//  system_utils.cpp
//  Engine
//
//  Created by krzysp on 31/07/2022.
//

#include "system_utils.hpp"

#ifdef __APPLE__
#include "system_utils_mac.hpp"
#endif

using namespace engine;

int FileUtils::GetCurrentFolder(std::string& out)
{
#ifdef __APPLE__
    FileUtilsMac fileUtils;
    return fileUtils.GetCurrentFolder(out);
#endif
}
