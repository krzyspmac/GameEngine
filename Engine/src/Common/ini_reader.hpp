// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

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
