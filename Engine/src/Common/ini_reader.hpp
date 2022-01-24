//
//  ini_reader.hpp
//  Engine
//
//  Created by krzysp on 24/01/2022.
//

#ifndef ini_reader_hpp
#define ini_reader_hpp

#include "common.h"
#include "engine_setup_interface.h"

namespace engine
{
    /** The go-to class for ini file reader
        \code{ini}
        [RESOLUTION]
        width=1280
        height=720
        \endcode{ini}
     */
    class IniReader
    {
        EngineSetup m_engineSetup;
        std::string m_currentSectionName;
    public:
        IniReader(std::string path);
        EngineSetup GetSetup();

    private:
        void ParseResolutionSection();
    };
};

#endif /* ini_reader_hpp */
