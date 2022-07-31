//
//  system_utils_mac.hpp
//  Engine
//
//  Created by krzysp on 31/07/2022.
//

#ifndef system_utils_mac_hpp
#define system_utils_mac_hpp

#include "system_utils.hpp"

namespace engine {

    class FileUtilsMac: public FileUtilsI
    {
    public:
        int GetCurrentFolder(std::string& out);
    };
};

#endif /* system_utils_mac_hpp */
