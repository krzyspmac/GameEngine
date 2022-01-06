//
//  font.cpp
//  RendererAppSDL
//
//  Created by krzysp on 20/12/2021.
//

#include "font.hpp"
#include "engine.hpp"
#include "common_engine_impl.h"

using namespace engine;

//static char *characters = "Ö&|_# POfileorTBFS:handWCpygt2015-6,JwsbuGNUL3.Emj@c/\"IV\\RMD8+v?x;=%!AYq()'kH[]KzQX4Z79*àéí¡Çóè·úïçüºòÉÒÍÀ°æåøÆÅØ<>öÄäßÜá¿ñÁÊûâîôÈêùœÙìëęąłćżńśźŻŚŁĆÖ";
static char characters[4096] = "01234567890abcdefghijklmnoprstuwxyzABCDEFGHIJKLMNOPRSTUWXYZ";

static int nextGlyph(const char *str, int *i, char *glyphBuffer);
static SDL_Color white = {255, 255, 255, 255};
static SDL_Texture *toTexture(engine::SDL_APP app, SDL_Surface *surface, int destroySurface);

Font::Font(engine::SDL_APP *engineHandle, std::string filename, FileMemoryBufferStreamI *stream)
: FontI(filename)
{
    std::cout << "Loading font " << filename << std::endl;

    SDL_RWops *ops = SDL_RWFromConstMem(stream->GetMemory(), (int)stream->GetSize());
    if (!ops)
    {
        return;
    }
    
    m_font = TTF_OpenFontRW(ops, 1, FONT_SIZE*5); //TTF_OpenFont(filename.c_str(), FONT_SIZE);
    if (m_font == NULL)
    {
        std::cout << "Could not open font " << filename << std::endl;
        return;
    }

    SDL_Surface *surface, *text;
    SDL_Rect dest;
    int i, n;
    char glyphBuffer[MAX_GLYPH_SIZE];

    memset(&m_glyphs, 0, sizeof(SDL_Rect) * MAX_GLYPHS);

    surface = SDL_CreateRGBSurface(0, FONT_TEXTURE_SIZE, FONT_TEXTURE_SIZE, 32, 0, 0, 0, 0xff);
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGBA(surface->format, 0, 0, 0, 0));
    dest.x = dest.y = 0;

    i = 0;

    while ((n = nextGlyph(characters, &i, glyphBuffer)) != 0)
    {
        if (n >= MAX_GLYPHS)
        {
            printf("Glyph '%s' index exceeds array size (%d >= %d)\n", glyphBuffer, n, MAX_GLYPHS);
            exit(1);
        }

        text = TTF_RenderUTF8_Blended(m_font, glyphBuffer, white);

        TTF_SizeText(m_font, glyphBuffer, &dest.w, &dest.h);

        if (dest.x + dest.w >= FONT_TEXTURE_SIZE)
            {
            dest.x = 0;

            dest.y += dest.h + 1;

            if (dest.y + dest.h >= FONT_TEXTURE_SIZE)
            {
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "Out of glyph space in %dx%d font atlas texture map.", FONT_TEXTURE_SIZE, FONT_TEXTURE_SIZE);
                exit(1);
            }
            }

        SDL_BlitSurface(text, NULL, surface, &dest);

        m_glyphs[n] = dest;

        SDL_FreeSurface(text);

        dest.x += dest.w;
    }

    m_fontTexture = toTexture(*engineHandle, surface, 1);
}

Font::~Font()
{
    if (m_fontTexture != NULL)
    {
        SDL_DestroyTexture(m_fontTexture);
    }
    if (m_font != NULL)
    {
        TTF_CloseFont(m_font);
    }
}

void Font::DrawText(engine::SDL_APP *engineHandle, std::string stdText, int x, int y, int r, int g, int b, TEXT_ALIGNMENT align)
{
    int i, w, h, n;
    SDL_Rect *glyph, dest;

    char *text = (char*)stdText.c_str();

    if (align != TEXT_ALIGN_LEFT)
    {
        calcTextDimensions(text, &w, &h);

        if (align == TEXT_ALIGN_CENTER)
        {
            x -= (w / 2);
        }
        else if (align == TEXT_ALIGN_RIGHT)
        {
            x -= w;
        }
    }

    SDL_SetTextureColorMod(m_fontTexture, r, g, b);

    i = 0;

    while ((n = nextGlyph(text, &i, NULL)) != 0)
    {
        glyph = &m_glyphs[n];

        dest.x = x;
        dest.y = y;
        dest.w = glyph->w;
        dest.h = glyph->h;

        SDL_RenderCopy(engineHandle->renderer, m_fontTexture, glyph, &dest);

        x += glyph->w;
    }
}

void Font::calcTextDimensions(char *text, int *w, int *h)
{
    int i, n;
    SDL_Rect *g;

    *w = *h = 0;

    i = 0;

    while ((n = nextGlyph(text, &i, NULL)) != 0)
    {
        g = &m_glyphs[n];

        *w += g->w;
        *h = std::max(g->h, *h);
    }
}

static int nextGlyph(const char *str, int *i, char *glyphBuffer)
{
    int len;
    unsigned int bit;
    const char *p;

    bit = (unsigned char) str[*i];

    if (bit < ' ')
    {
        return 0;
    }

    len = 1;

    if (bit >= 0xF0)
    {
        bit  = (int)(str[*i]     & 0x07) << 18;
        bit |= (int)(str[*i + 1] & 0x3F) << 12;
        bit |= (int)(str[*i + 2] & 0x3F) << 6;
        bit |= (int)(str[*i + 3] & 0x3F);

        len = 4;
    }
    else if (bit >= 0xE0)
    {
        bit  = (int)(str[*i]     & 0x0F) << 12;
        bit |= (int)(str[*i + 1] & 0x3F) << 6;
        bit |= (int)(str[*i + 2] & 0x3F);

        len = 3;
    }
    else if (bit >= 0xC0)
    {
        bit  = (int)(str[*i]     & 0x1F) << 6;
        bit |= (int)(str[*i + 1] & 0x3F);

        len = 2;
    }

    /* only fill the buffer if it's been supplied */
    if (glyphBuffer != NULL)
    {
        p = str + *i;

        memset(glyphBuffer, 0, MAX_GLYPH_SIZE);
        memcpy(glyphBuffer, p, len);
    }

    *i = *i + len;

    return bit;
}

SDL_Texture *toTexture(engine::SDL_APP app, SDL_Surface *surface, int destroySurface)
{
    SDL_Texture *texture;

    texture = SDL_CreateTextureFromSurface(app.renderer, surface);

    if (destroySurface)
    {
        SDL_FreeSurface(surface);
    }

    return texture;
}
