//
//  font_interface.h
//  RendererAppSDL
//
//  Created by krzysp on 20/12/2021.
//

#ifndef font_interface_h
#define font_interface_h

#include "common.h"
#include "common_engine_impl.h"

namespace engine
{
    typedef enum {
        TEXT_ALIGN_LEFT     = 0,
        TEXT_ALIGN_CENTER   = 1,
        TEXT_ALIGN_RIGHT    = 2
    } TEXT_ALIGNMENT;

    class FontI
    {
    public:
        FontI(std::string filename): m_fontName(filename) { }
        virtual ~FontI() { };
        
        /**
         Retrieve the font name. Usually the name of the defining the font.
         */
        std::string &getFontName() { return m_fontName; };

        /** Set the scale */
        virtual void SetScale(float) = 0;

        /**
         Draw the font. Uses the current engine provider.
         */
        virtual void DrawAt(std::string text, float x, float, int r, int g, int b, int a, TEXT_ALIGNMENT align, Color4 colorMod, float lineMultiplier) = 0;

    private:
        std::string m_fontName;
    };

}

#endif /* font_interface_h */
