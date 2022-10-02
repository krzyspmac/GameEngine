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

#ifndef console_renderer_h
#define console_renderer_h

#include "common.h"
#include "console_renderer_interface.h"
#include "interfaces.h"

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
        ConsoleLightManagementI *m_lightManagement;

    public:
        ConsoleRenderer();
        virtual ~ConsoleRenderer();
        
        void Setup();
        void DoFrame();
        void SetConsoleHidden(bool);
        bool GetConsoleHidden();

        ConsoleLogI& GetLogger();
        ConsoleTerminalI& GetTerminal();
        ConsoleLightManagementI& GetLightManagement();

        auto GetPlarformRenderer() { return m_platformRenderer.get(); };

    private:
        void SetupEvents();
        void DoMenuBar();
        void DoGui();
    };
};

#endif /* console_renderer_h */
