//
//  font_manager.hpp
//  Engine
//
//  Created by krzysp on 08/01/2022.
//

#ifndef font_manager_hpp
#define font_manager_hpp

#include "font_interface.h"
#include "scripting_engine_provider_interface.h"

namespace engine
{
    /**
     FontManager
     \addtogroup API_GLOBALS
     */
    /** Keps a list of all fonts
     */
    class FontManager
    {
        std::vector<std::unique_ptr<FontI>> m_fonts;
    public:
        /** Load a specified fitmap font by providing the name of the .fnt file and the texture.
            If the font was previously loaded, uses the GetFont function instead. Otherwise loads new.

            \code{lua}
            local font = FontManager:LoadFont("someFont.fnt", "someFont.png")
            font:DrawAt("Sample Text", 0, 0, 255, 0, 0, 255, "left")
            \endcode
         */
        FontI *LoadFont(std::string fntFilename, std::string fontTexture);

        /** Get a cached version of the font.
            @private
         */
        FontI *GetFont(std::string name);

        /** Unload all fonts. Be sure that you're no longer using them.
         */
        void DisposeAllFonts();

    private: /** scripting */
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(FontManager);
    };
};

#endif /* font_manager_hpp */
