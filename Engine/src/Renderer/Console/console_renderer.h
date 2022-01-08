//
//  console_renderer.h
//  Engine
//
//  Created by krzysp on 07/01/2022.
//

#ifndef console_renderer_h
#define console_renderer_h

#include "common.h"
#include "console_renderer_interface.h"
#include "common_engine_impl.h"

namespace engine
{
    class ConsoleRenderer: public ConsoleRendererI
    {
        engine::SDL_APP m_app;
        bool m_hidden;
        bool m_isSetup;
        ConsoleLogI *m_logger;
        ConsoleTerminalI *m_terminal;

    public:
        ConsoleRenderer();

        void Setup();
        void DoFrame();
        void SetConsoleHidden(bool);

        ConsoleLogI& GetLogger();
        ConsoleTerminalI& GetTerminal();

    private:
        void SetupWindow();
        void SetupEvents();
        void DoMenuBar();
        void SetupImGui();
        void DoGui();
    };
};

#endif /* console_renderer_h */
