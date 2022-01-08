//
//  console_app_renderer_mac.hpp
//  Engine
//
//  Created by krzysp on 08/01/2022.
//

#ifndef console_app_renderer_mac_hpp
#define console_app_renderer_mac_hpp

#include "console_renderer_interface.h"
#include "common_engine_impl.h"

namespace engine
{
    class ConsoleAppRendererMac: public ConsoleAppRendererI
    {
        engine::SDL_APP m_app;
        bool m_hidden;
        bool m_isSetup;

    public: // ConsoleAppRendererI
        ConsoleAppRendererMac();
        virtual ~ConsoleAppRendererMac() { };

        void Setup();
        bool IsSetup();
        void DoFrame(std::function<void(void)>);
        void SetConsoleHidden(bool);

    private:
        void SetupWindow();
        void SetupImGui();
    };
};

#endif /* console_app_renderer_mac_hpp */
