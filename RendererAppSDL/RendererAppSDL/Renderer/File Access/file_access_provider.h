//
//  file_access_provider.h
//  Renderer
//
//  Created by krzysp on 19/12/2021.
//

#ifndef file_access_provider_h
#define file_access_provider_h

#include "common.h"

namespace engine
{
    class FileAccessI
    {
    public:
        /// Get a path for the main bundle including the scene files.
        virtual std::string getBundlePath() = 0;

        /// Get a file path for a specific name. Main bundle will be used.
        virtual std::string getBundledFilepath(const char *value) = 0;
    };
};

#endif /* file_access_provider_h */
