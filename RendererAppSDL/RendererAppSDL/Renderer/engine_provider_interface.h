//
//  engine_interface.h
//  Renderer
//
//  Created by krzysp on 19/12/2021.
//

#ifndef engine_provider_interface_h
#define engine_provider_interface_h

#include "common.h"
#include "texture_interface.h"
#include "font_interface.h"

namespace engine
{
    class EngineProviderI
    {
    public:
        ///
        EngineProviderI() { }

        /// A concrete instance should load the texture. The ownership
        /// of the texture is passed to the caller.
        virtual TextureI *LoadTexture(std::string name) = 0;

        /// A concrete instance should unload the texture.
        virtual void UnloadTexture(TextureI *texture) = 0;

        /// A concrete instance will draw the texture on screen
        /// at given coordinates.
        virtual void DrawTexture(TextureI *texture, int x, int y) = 0;

        /// Load a font. The ownership
        /// of the texture is passed to the caller.
        virtual FontI *LoadFont(std::string name) = 0;

        /// Draws a text using a specified font.
        virtual void DrawText(FontI *font, std::string text, int x, int y, int r, int g, int b, TEXT_ALIGNMENT align) = 0;

        ///
//        virtual void DrawDebugText(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, ...) = 0;
    };
};

#endif /* engine_provider_interface_h */
