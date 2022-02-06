//
//  console_renderer_interface_hpp
//  Engine
//
//  Created by krzysp on 07/01/2022.
//

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
        ~ConsoleAppRendererI() { };

        virtual void Setup() = 0;
        virtual bool IsSetup() = 0;
        virtual void DoFrame(std::function<void(void)>) = 0;
        virtual void SetConsoleHidden(bool) = 0;
    };
};

#endif /* console_renderer_interface_hpp */
