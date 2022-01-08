//
//  console_renderer.hpp
//  Engine
//
//  Created by krzysp on 07/01/2022.
//

#ifndef console_renderer_hpp
#define console_renderer_hpp

#include "common.h"

namespace engine
{
    /**
     Console part specific.
     */
    class ConsoleWindowI
    {
    public:
        virtual void ToggleVisibility() = 0;

    };

    /**
     Logger specifif.
     */
    class ConsoleLogI: public ConsoleWindowI
    {
    public:
        virtual void Log(const char* fmt, ...) = 0;
        virtual void Render() = 0;
        virtual void ToggleVisibility() = 0;
    };

    class ConsoleRendererI
    {
    public:
        virtual void Setup() = 0;

        virtual void DoFrame() = 0;

        virtual void SetConsoleHidden(bool) = 0;

        virtual ConsoleLogI& GetLogger() = 0;
    };

    /**
     Defines the imgui renderer for a specific part
     */
    class ConsoleAppRendererI
    {
    public:
        ConsoleAppRendererI();
    };
};

#endif /* console_renderer_hpp */
