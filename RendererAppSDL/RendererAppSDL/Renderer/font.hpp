//
//  font.hpp
//  RendererAppSDL
//
//  Created by krzysp on 20/12/2021.
//

#ifndef font_hpp
#define font_hpp

#include "common.h"
#include "font_interface.h"
#include "common_engine_impl.h"

namespace engine
{

    #define FONT_SIZE            48
    #define FONT_TEXTURE_SIZE    512
    #define MAX_GLYPHS           400
    #define MAX_GLYPH_SIZE       8
    #define MAX_WORD_LENGTH      32
    #define MAX_LINE_LENGTH      1024

    class Font: FontI
    {
    public:
        Font(SDL_APP *engineHandle, std::string filename);
        ~Font();

        SDL_Texture *getFontTexture() { return m_fontTexture; };

        void DrawText(engine::SDL_APP *engineHandle, std::string text, int x, int y, int r, int g, int b, TEXT_ALIGNMENT align);
        void calcTextDimensions(char *text, int *w, int *h);

    private:
        TTF_Font *m_font;
        SDL_Texture *m_fontTexture;
        SDL_Rect m_glyphs[MAX_GLYPHS];
    };

};

#endif /* font_hpp */
