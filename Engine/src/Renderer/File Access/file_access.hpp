//
//  file_access.hpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#ifndef file_access_hpp
#define file_access_hpp

#include "common.h"
#include "file_access_provider.h"

namespace engine
{
    class FileAccess : public FileAccessI
    {
    public:
        FileAccess();

        int LoadPackedFile(std::string filename);

        /// Load the game directory by providing the "game_folder" variable.
        int LoadDirectory(std::string directory);

        std::string GetResourcesDirectory();

    public:
        FileStreamI *GetAccess(std::string filename);

    public:
        std::string getBundledFilepath(const char *value);

    public:
        std::string GetFullPath(std::string filename);

    private:
        FILE *m_gPackFile;
        std::string m_dataDirectory;
    };
};

#endif /* file_access_hpp */
