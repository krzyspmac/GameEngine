//
//  console_view.hpp
//  Engine
//
//  Created by krzysp on 29/12/2021.
//

#ifndef console_view_hpp
#define console_view_hpp

#include "console_view_interface.h"
#include "engine_provider_interface.h"
#include "texture_interface.h"

namespace engine
{
    class ConsoleView: public ConsoleViewI
    {
    public:
        ConsoleView(FontI *font, char keyTrigger);
        virtual ~ConsoleView();

    public:
        bool ShouldPresentConsole();
        bool IsPresented();
        bool PresentConsole();
        void RenderConsole();

    private:
        void RenderScene();

    private:
        TextureTargetI *m_bufferTexture;
        Engine_Rect m_consoleViewportRect;
    };
};

#endif /* console_view_hpp */
