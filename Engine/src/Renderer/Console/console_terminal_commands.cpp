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

#include "console_terminal_commands.hpp"
#include "imgui.h"
#include "engine.hpp"

/* Portable helpers */
static int   Stricmp(const char* s1, const char* s2)         { int d; while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; } return d; }

static bool IsCommand(std::string cmdLine, std::string cmd);
static std::string GetRestOfCommand(std::string cmdLine, std::string cmd);

/* Defines */
#define GET_TERMINAL(x) ENGINE().getConsoleRenderer().GetTerminal()

using namespace engine;

/**
 ConcoleTemrinalCmdParserSimple
 */

bool ConcoleTemrinalCmdParserSimple::Process(const char *commandLine)
{
    if (Stricmp(commandLine, "clear") == 0)
    {
        GET_TERMINAL().ClearLog();
        return true;
    }
    return false;
}

const char* ConcoleTemrinalCmdParserSimple::GetCommand()
{
    return "clear";
}

/**
 ConsoleTerminalCmdLuaExec
 */

ConsoleTerminalCmdLuaExec::ConsoleTerminalCmdLuaExec()
{

}

ConsoleTerminalCmdLuaExec::~ConsoleTerminalCmdLuaExec()
{

}

const char* ConsoleTerminalCmdLuaExec::GetCommand()
{
    return "lua_eval";
}

static std::string GetRestOfCommand(std::string cmdLine, std::string cmd)
{
    std::size_t cmdPos = std::string::npos;
    if ((cmdPos = cmdLine.find(cmd)) != std::string::npos)
    {
        std::string rest = cmdLine.substr(cmdPos+cmd.size(), cmdLine.size() - cmdPos);
        return rest;
    }
    else
    {
        return std::string();
    }
}

bool ConsoleTerminalCmdLuaExec::Process(const char *commandLine)
{
    printf("Not working right now as there's no lua... Need some processing.\n");
    exit(1);
    return false;
}

static bool IsCommand(std::string cmdLine, std::string cmd)
{
    return cmdLine.find(cmd) != std::string::npos;
}
