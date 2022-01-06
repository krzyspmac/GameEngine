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
#include "file_access_provider.h"

namespace engine
{

    #define FONT_SIZE            15
    #define FONT_TEXTURE_SIZE    1024
    #define MAX_GLYPHS           400
    #define MAX_GLYPH_SIZE       8
    #define MAX_WORD_LENGTH      32
    #define MAX_LINE_LENGTH      1024

    class FontTTF: FontI
    {
    public:
        FontTTF(SDL_APP *engineHandle, std::string filename, FileStreamI *stream);
        ~FontTTF();

        SDL_Texture *getFontTexture() { return m_fontTexture; };

        void DrawAt(std::string text, float x, float, int r, int g, int b, int a, TEXT_ALIGNMENT align);
        void DrawText(engine::SDL_APP *engineHandle, std::string text, int x, int y, int r, int g, int b, TEXT_ALIGNMENT align);
        void calcTextDimensions(char *text, int *w, int *h);

    private:
        TTF_Font *m_font;
        SDL_Texture *m_fontTexture;
        SDL_Rect m_glyphs[MAX_GLYPHS];
    };

};

#endif /* font_hpp */
