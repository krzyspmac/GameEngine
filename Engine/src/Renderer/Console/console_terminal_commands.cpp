//
//  console_terminal_commands.cpp
//  Engine
//
//  Created by krzysp on 08/01/2022.
//

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
    std::string cmdLine = commandLine;

    if (IsCommand(cmdLine, "lua_eval"))
    {
        auto rest = GetRestOfCommand(cmdLine, "lua_eval");
        ENGINE().getScripting().loadChunk((char*)rest.c_str());
        return true;
    }

    return false;
}

static bool IsCommand(std::string cmdLine, std::string cmd)
{
    return cmdLine.find(cmd) != std::string::npos;
}
