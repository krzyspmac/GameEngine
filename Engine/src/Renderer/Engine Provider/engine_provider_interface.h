//
//  engine_interface.h
//  Renderer
//
//  Created by krzysp on 19/12/2021.
//

#ifndef engine_provider_interface_h
#define engine_provider_interface_h

#include "texture_interface.h"
#include "font_interface.h"
#include "common.h"

namespace engine
{
    /// EngineProviderI declares an abstraction for low-level
    /// drawing functions. Those are bare-bones only.
    /// EngineI provides further concrete instances where
    /// additional caching might happen. Texturing should be
    /// used via EngineI since the cache is there.
    class EngineProviderI
    {
    public:
        ///
        EngineProviderI() { }

    /// Engine states
    public:

        /// Concrete instance would get the ticks since the
        /// provider library initialized. The library itself
        /// should check for overflows.
        virtual Uint64 GetTicks() = 0;

        /// More robuts results than GetTicks.
        virtual Uint64 GetPerformanceTicks() = 0;

        /// More robuts results than GetTicks.
        virtual Uint64 GetPerformanceCounter() = 0;

        /// Concrete instance would get the mouse position
        /// and store them under the given pointers.
        virtual void GetMousePosition(int *x, int *y) = 0;

        /// Wait ms
        virtual void Delay(Uint32 ms) = 0;

    /// Renderer related
    public:

        /// Set the drawing colour.
        virtual void SetRenderBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) = 0;

        /// Clear the frambuffer with a previously set colour.
        virtual void ClearRender() = 0;

        /// Update the screen with any rendering performed since the previous call.
        virtual void RenderPresent() = 0;

    /// Textures
    public:

        /// A concrete instance should load the texture. The ownership
        /// of the texture is passed to the caller.
        virtual TextureI *LoadTexture(std::string name) = 0;

        /// A concrete instance should unload the texture.
        virtual void UnloadTexture(TextureI *texture) = 0;

        /// A concrete instance will draw the texture on screen
        /// at given coordinates.
        virtual void DrawTexture(TextureI *texture, int x, int y) = 0;

        /// A concrete instance will draw the texture on screen
        /// at given coordinates from the given source rect.
        virtual void DrawTexture(TextureI *texture, int x, int y, int srcX, int srcY, int srcW, int srcH) = 0;

    /// Fonts
    public:

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
