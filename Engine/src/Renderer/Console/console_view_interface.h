//
//  console_view_interface.h
//  Engine
//
//  Created by krzysp on 29/12/2021.
//

#ifndef console_view_interface_h
#define console_view_interface_h

#include "font_interface.h"

namespace engine
{
    class ConsoleViewI
    {
    public:
        ConsoleViewI(FontI *font, char keyTrigger): m_font(font), m_keyTrigger(keyTrigger) { };
        virtual ~ConsoleViewI() { };

    public:
        /// Decides if the console should be opened.
        virtual bool ShouldPresentConsole() = 0;

        /// Is the console preesnted?
        virtual bool IsPresented() = 0;

        /// Set the console to be presented
        virtual bool PresentConsole() = 0;

        /// Shows the console taking control of the input.
        virtual void RenderConsole() = 0;

    private:
        FontI * m_font;
        char m_keyTrigger;
    };
};

#endif /* console_view_interface_h */
