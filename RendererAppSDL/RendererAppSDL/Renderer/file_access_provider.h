//
//  file_access_provider.h
//  Renderer
//
//  Created by krzysp on 19/12/2021.
//

#ifndef file_access_provider_h
#define file_access_provider_h

namespace engine
{
    class FileAccessI
    {

        ///
        virtual void getBundledFilepath(const char *value) = 0;
    };
};

#endif /* file_access_provider_h */
