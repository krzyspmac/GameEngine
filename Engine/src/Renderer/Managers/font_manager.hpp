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
#include "font_manager_interface.h"

namespace engine
{
    /**
     FontManager
     \addtogroup API_GLOBALS
     */
    /** Keps a list of all fonts
     */
    class FontManager: public FontManagerI
    {
        std::vector<std::unique_ptr<FontI>> m_fonts;
    public:
        FontI *LoadFont(std::string fntFilename, std::string fontTexture);

        FontI *GetFont(std::string name);

        void DisposeAllFonts();

    private: /** scripting */
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(FontManager);
    };
};

#endif /* font_manager_hpp */
