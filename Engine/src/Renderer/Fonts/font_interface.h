//
//  font_interface.h
//  RendererAppSDL
//
//  Created by krzysp on 20/12/2021.
//

#ifndef font_interface_h
#define font_interface_h

#include "common.h"

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

        std::string &getFontName() { return m_fontName; };

    private:
        std::string m_fontName;
    };

}

#endif /* font_interface_h */
