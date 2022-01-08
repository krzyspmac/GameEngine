//
//  console_logger.hpp
//  Engine
//
//  Created by krzysp on 08/01/2022.
//

#ifndef console_logger_hpp
#define console_logger_hpp

#include "common.h"
#include "console_renderer_interface.h"

namespace engine
{
    class ConsoleLog: public ConsoleLogI
    {
        bool                p_open;
    public:
        ConsoleLog();
        static ConsoleLog *Shared();

        void Log(const char* fmt, ...);
        void ToggleVisibility();
        void Render();

    private:
        void Clear();
        void Draw(const char* title, bool* p_open = NULL);
    };
};

#endif /* console_logger_hpp */
