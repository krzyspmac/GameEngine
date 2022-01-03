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

        int LoadDirectory(std::string directory);

        std::string GetResourcesDirectory();

    public:
        FileMemoryBufferStreamI *GetAccess(std::string filename);

    public:
        std::string getBundledFilepath(const char *value);

        std::string loadText(std::string filename);

        FileMemoryBufferStreamI *LoadBufferStream(const char *filename);

    public:
        std::string GetFullPath(std::string filename);

    private:
        FILE *m_gPackFile;
        std::string m_dataDirectory;
    };
};

#endif /* file_access_hpp */
