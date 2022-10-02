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

#ifndef console_renderer_interface_hpp
#define console_renderer_interface_hpp

#include "common.h"

namespace engine
{
    /**
     Console part specific.
     */
    class ConsoleWindowI
    {
    public:
        virtual ~ConsoleWindowI() { };

        virtual void ToggleVisibility() = 0;

    };

    /**
     Logger specific.
     */
    class ConsoleLogI: public ConsoleWindowI
    {
    public:
        virtual ~ConsoleLogI() { };

        virtual void Log(const char* fmt, ...) = 0;
        virtual void Render() = 0;
        virtual void ToggleVisibility() = 0;
    };

    /**
     Declare a console command. Each command gets its own processor.
     */
    class ConsoleTerminalCmdI
    {
    public:
        virtual ~ConsoleTerminalCmdI() { };

        virtual const char* GetCommand() = 0;
        virtual bool Process(const char*) = 0;
    };

    /**
     Terminal.
     */
    class ConsoleTerminalI: public ConsoleWindowI
    {
    public:
        virtual ~ConsoleTerminalI() { };

        virtual void Render() = 0;
        virtual void ToggleVisibility() = 0;
        virtual void ClearLog() = 0;
        virtual void AddLog(const char* fmt, ...) = 0;

    protected:
        std::vector<std::unique_ptr<ConsoleTerminalCmdI>> m_cmdParsers;
    };

    /**
     Lights Management
     */
    class ConsoleLightManagementI: public ConsoleWindowI
    {
    public:
        virtual ~ConsoleLightManagementI() { };

        virtual void Render() = 0;
        virtual void ToggleVisibility() = 0;
    };

    /**
     Defines the actual console renderer. Uses ConsoleAppRendererI for
     platform specific rendering.
     */
    class ConsoleRendererI
    {
    public:
        virtual ~ConsoleRendererI() { };

        virtual void Setup() = 0;

        virtual void DoFrame() = 0;

        virtual void SetConsoleHidden(bool) = 0;

        virtual ConsoleLogI& GetLogger() = 0;

        virtual ConsoleTerminalI& GetTerminal() = 0;
    };

    /**
     Defines the imgui renderer for a specific palrform.
     */
    class ConsoleAppRendererI
    {
    public:
        ConsoleAppRendererI() { };
        virtual ~ConsoleAppRendererI() { };

        virtual void Setup() = 0;
        virtual bool IsSetup() = 0;
        virtual void DoFrame(std::function<void(void)>) = 0;
        virtual void SetConsoleHidden(bool) = 0;
    };
};

#endif /* console_renderer_interface_hpp */
