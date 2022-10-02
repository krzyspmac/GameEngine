//
//  font_manager.cpp
//  Engine
//
//  Created by krzysp on 08/01/2022.
//

#include "font_manager.hpp"
#include "font_bitmap.hpp"

using namespace engine;

FontI *FontManager::LoadFont(std::string fntFilename, std::string fontTexture)
{
    FontI *result = GetFont(fntFilename);
    if (!result)
    {
        FontI *result = new FontBitmapRepresentation(fntFilename, fontTexture, 1);
        if (result)
        {
            m_fonts.emplace_back(std::unique_ptr<FontI>(std::move(result)));
            return result;
        }
    }
    return result;
}

FontI *FontManager::GetFont(std::string name)
{
    for(auto it = std::begin(m_fonts); it != std::end(m_fonts); ++it)
    {
        FontI *item = it->get();
        if (item->getFontName().compare(name) == 0)
        {
            return item;
        }
    }

    return NULL;
}

void FontManager::DisposeAllFonts()
{
    std::cout << "DisposeAllFonts not implemented" << std::endl;
}
