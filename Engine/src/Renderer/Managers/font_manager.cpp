// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

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
