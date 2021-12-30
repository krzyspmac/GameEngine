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
#include "file_access_provider.h"
#include "vector2.hpp"
#include "common.h"

namespace engine
{
    typedef struct Engine_Rect
    {
        int x, y;
        int w, h;
    } Engine_Rect;

    typedef enum Anchor_Point
    {
        ANCHOR_TOP_LEFT,        // default
        ANCHOR_BOTTOM_CENTER    // for character drwaing
    } Anchor_Point;

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

        /// Get the current window size.
        virtual void GetWindowSize(int *w, int *h) = 0;

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

        /// A concrete instance should load the texture from the filename using
        /// the default internal file access classes. The ownership
        /// of the texture is passed to the caller.
        virtual TextureI *LoadTexture(std::string name, FileMemoryBufferStreamI *) = 0;

        /// A concrete instance should create the target texture. A target texture
        /// is able to be rendered upon so a partial render can be developed.
        /// The ownership of the texture is passed to the caller.
        virtual TextureTargetI *CreateTargetTexture(int width, int height) = 0;

        /// A concrete instance should unload the texture.
        virtual void UnloadTexture(TextureI *texture) = 0;

        /// A concrete instance will draw the texture on screen
        /// at given coordinates.
        virtual void DrawTexture(TextureI *texture, int x, int y) = 0;

        /// A concrete instance will draw the texture on screen
        /// at given coordinates from the given source rect.
        virtual void DrawTexture(TextureI *texture, int x, int y, int srcX, int srcY, int srcW, int srcH, float scale) = 0;

        /// Draws a texture ona specific anchor point. Helpful for character drawing where the origin point
        /// is a the bottom.
        virtual void DrawTexture(TextureI *texture, Anchor_Point anchorPoint, int x, int y, float scale, bool flipHorizontal) = 0;

        /// Draws a texture ona specific anchor point. Helpful for character drawing where the origin point
        /// is a the bottom.
        virtual void DrawTexture(TextureI *texture, Anchor_Point anchorPoint, Vector2& position, float scale, bool flipHorizontal) = 0;

    /// Fonts
    public:

        /// Load a font. The ownership
        /// of the texture is passed to the caller.
        virtual FontI *LoadFont(std::string name, FileMemoryBufferStreamI *) = 0;

        /// Draws a text using a specified font.
        virtual void DrawText(FontI *font, std::string text, int x, int y, int r, int g, int b, TEXT_ALIGNMENT align) = 0;

    /// Renderer specific
    public:

        /// Sets the render target to a target texture. All rendering goes
        /// there until a `RenderTargetClear` is called. The texture
        /// must be created as a target texture.
        virtual void RendererTargetPush(TextureTargetI *targetTexture) = 0;

        /// Pops the renderer target texture from the stack and returned
        /// to the previous one or the main renderer if the stack is empty.
        virtual void RendererTargetPop() = 0;
        
        virtual void RenderTargetSet(TextureI *targetTexture) = 0;

        /// Clears the render target so the final render can be applied.
        virtual void RenderTargetClear() = 0;

        /// Clears the buffer before drawing a new frame.
        virtual void RenderClear() = 0;

        /// Sets the draw color.
        virtual void RenderSetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) = 0;

        /// Sets the render scale.
        virtual void RenderSetScale(float scaleX, float scaleY) = 0;

        /// Draw a rectangle.
        virtual void RenderDrawRect(Engine_Rect*) = 0;

        /// Draw a rectangle.
        virtual void RenderFillRect(Engine_Rect*) = 0;

        /// Draw a rectangle.
        virtual void RenderDrawLine(int x1, int y1, int x2, int y2) = 0;

        /// Draw a point.
        virtual void RenderDrawPoint(int x1, int y1) = 0;

    };
};

#endif /* engine_provider_interface_h */
