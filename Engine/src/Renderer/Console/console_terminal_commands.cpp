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
//static int   Strnicmp(const char* s1, const char* s2, int n) { int d = 0; while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; n--; } return d; }
//static char* Strdup(const char* s)                           { IM_ASSERT(s); size_t len = strlen(s) + 1; void* buf = malloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)s, len); }
//static void  Strtrim(char* s)                                { char* str_end = s + strlen(s); while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; }

static bool IsCommand(std::string cmdLine, std::string cmd);
static std::string GetRestOfCommand(std::string cmdLine, std::string cmd);

/* Defines */
#define GET_TERMINAL(x) GetMainEngine()->getConsoleRenderer().GetTerminal()

using namespace engine;

/**
 ConcoleTemrinalCmdParserSimple
 */

bool ConcoleTemrinalCmdParserSimple::Process(const char *commandLine)
{
    if (Stricmp(commandLine, "CLEAR") == 0)
    {
        GET_TERMINAL().ClearLog();
        return true;
    }
    return false;
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
        GetMainEngine()->getScripting().loadChunk((char*)rest.c_str());
        return true;
    }

    return false;
}

static bool IsCommand(std::string cmdLine, std::string cmd)
{
    return cmdLine.find(cmd) != std::string::npos;
}
