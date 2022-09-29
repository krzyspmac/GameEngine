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

        [PHONE]
        orientation=portrait|landscape

        [RENDERER]
        game_folder=@rpath/Game
        clear_color=1.0,0.0,0.0,1.0

        [INPUT]
        gamepad_support=true
        gamepad_virtual_support=true
        gamepad_virtual_buttons=DirectionPad|LeftThumbstick|ButtonA
        \endcode{ini}
     */
    class IniReader
    {
        typedef enum
        {
            UNKNOWN             = 0,
            RESOLUTION          = 1,
            RENDERER            = 2,
            INPUT               = 3,
            PHONE               = 4
        } IniSectionType;

        EngineSetup m_engineSetup;
        IniSectionType m_currentSectionType;
    public:
        IniReader(std::string path);
        void ProcessDefaults();
        void ProcessFile(FILE*);
        EngineSetup GetSetup();

    private:
        bool UpdateSection(std::string &srcLine);
        void ParseKeyValue(std::string &srcLine);


    public:

        class Variables
        {
        public:
            static std::string rpath()
            {
                return "@rpath";
            }
        };
    };
};

#endif /* ini_reader_hpp */
