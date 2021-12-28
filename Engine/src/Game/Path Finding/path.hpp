//
//  path.hpp
//  Engine
//
//  Created by krzysp on 28/12/2021.
//

#ifndef path_hpp
#define path_hpp

#include "path_finder_interface.h"

namespace engine
{

    class Path: public PathI
    {
    public:
        Path(): PathI() { };
        Path(std::vector<Vector2> path): PathI(path) { };
        virtual ~Path() { };
        std::string Description();
    public:
        std::vector<Line> ToLines();

    };
};

#endif /* path_hpp */
