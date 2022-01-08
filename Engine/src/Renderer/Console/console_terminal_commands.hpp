//
//  console_terminal_commands.hpp
//  Engine
//
//  Created by krzysp on 08/01/2022.
//

#ifndef console_terminal_commands_hpp
#define console_terminal_commands_hpp

#include "common.h"
#include "console_renderer_interface.h"

namespace engine
{
    class ConcoleTemrinalCmdParserSimple: public ConsoleTerminalCmdI
    {
    public:
        bool Process(const char*);
    };

    class ConsoleTerminalCmdLuaExec: public ConsoleTerminalCmdI
    {
    public:
        ConsoleTerminalCmdLuaExec();
        virtual ~ConsoleTerminalCmdLuaExec();

        bool Process(const char*);
    };
};


#endif /* console_terminal_commands_hpp */
