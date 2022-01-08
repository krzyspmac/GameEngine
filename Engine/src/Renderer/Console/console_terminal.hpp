//
//  console_terminal.hpp
//  Engine
//
//  Created by krzysp on 08/01/2022.
//

#ifndef console_terminal_hpp
#define console_terminal_hpp

#include "common.h"
#include "console_renderer_interface.h"
#include "imgui.h"

namespace engine
{
    class ConsoleTerminal: public ConsoleTerminalI
    {
        bool p_open;
    public:
        ConsoleTerminal();
        ~ConsoleTerminal();

        void ToggleVisibility();
        void Render();

    public:
        void ClearLog();
        void AddLog(const char* fmt, ...);
        void Draw(const char* title, bool* p_open);
        void ExecCommand(const char* command_line);
        int TextEditCallback(ImGuiInputTextCallbackData* data);
    };
};


#endif /* console_terminal_hpp */
