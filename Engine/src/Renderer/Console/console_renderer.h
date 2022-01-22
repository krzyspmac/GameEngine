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
    /** The main console renderer. Release version does not include a console. */
    class ConsoleRenderer: public ConsoleRendererI
    {
        std::unique_ptr<ConsoleAppRendererI> m_platformRenderer;
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

        auto GetPlarformRenderer() { return m_platformRenderer.get(); };

    private:
        void SetupEvents();
        void DoMenuBar();
        void DoGui();
    };
};

#endif /* console_renderer_h */
