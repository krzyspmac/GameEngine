//
//  font_manager_interface.h
//  Engine
//
//  Created by krzysp on 25/09/2022.
//

#ifndef font_manager_interface_h
#define font_manager_interface_h

#include "font_interface.h"

namespace engine
{
    /** FontManagerI
        \addtogroup API_GLOBALS

        Keps a list of all fonts including memory handling of those.
     */
    class FontManagerI
    {
    public:
        /** Load a specified fitmap font by providing the name of the .fnt file and the texture.
            If the font was previously loaded, uses the GetFont function instead. Otherwise loads new.
         */
        virtual FontI *LoadFont(std::string fntFilename, std::string fontTexture) = 0;

        /** Get a cached version of the font.
            @private
         */
        virtual FontI *GetFont(std::string name) = 0;

        /** Unload all fonts. Be sure that you're no longer using them.
         */
        virtual void DisposeAllFonts() = 0;
    };
}

#endif /* font_manager_interface_h */
