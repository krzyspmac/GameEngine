//
//  file_access.hpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#ifndef file_access_hpp
#define file_access_hpp

#include <stdio.h>
#include "file_access_provider.h"

namespace engine
{
    class FileAccess : public FileAccessI
    {
        void getBundledFilepath(const char *value);
    };
};

#endif /* file_access_hpp */
