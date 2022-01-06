//
//  polygon_loader.hpp
//  Engine
//
//  Created by krzysp on 29/12/2021.
//

#ifndef polygon_loader_hpp
#define polygon_loader_hpp

#include "file_access_provider.h"
#include "polygon.hpp"

namespace engine
{

    class PolygonLoader
    {
    public:
        static std::vector<Polygon> Load(FileMemoryBufferStreamI *stream);
    };
};

#endif /* polygon_loader_hpp */
