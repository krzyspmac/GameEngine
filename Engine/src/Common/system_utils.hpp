//
//  system_utils.hpp
//  Engine
//
//  Created by krzysp on 31/07/2022.
//

#ifndef system_utils_h
#define system_utils_h

#include "common.h"

namespace engine {

    class FileUtilsI
    {
    public:
        /// Returns the current folder. -1 on success.
        /// @private
        virtual int GetCurrentFolder(std::string& out) = 0;
    };

    class FileUtils: public FileUtilsI
    {
    public:
        static FileUtils* shared()
        {
            static FileUtils *sharedInstance = nullptr;
            if (sharedInstance == nullptr)
            {   sharedInstance = new FileUtils();
            }
            return sharedInstance;
        }
        int GetCurrentFolder(std::string& out);
    };
};

#endif /* system_utils_h */
