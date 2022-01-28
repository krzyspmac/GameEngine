//
//  engine_interface.h
//  Renderer
//
//  Created by krzysp on 19/12/2021.
//

#ifndef engine_provider_interface_h
#define engine_provider_interface_h

#include "texture_interface.h"
#include "drawable_interface.h"
#include "font_interface.h"
#include "file_access_provider.h"
#include "sprite_atlas_interface.h"
#include "sprite_draw_backbuffer.hpp"
#include "vector2.hpp"
#include "common.h"

namespace engine
{
    typedef struct Engine_Rect
    {
        int x, y;
        int w, h;
    } Engine_Rect;

    /** EngineProviderI declares an abstraction for low-level drawing functions. Those are bare-bones only.
        The main entry point in the app initializes different concrete instances.
     */
    class EngineProviderI
    {
    public:
        ///
        EngineProviderI() { }

    /// Engine setup
    public:
        /// Sets the desired viewport. It will affect the aspect ratio.
        /// The engine them will attemp to compensate by scaling and
        /// translating the remainder of the view.
        virtual void SetDesiredViewport(int width, int height) = 0;

        virtual engine::Size GetDesiredViewport() = 0;

        /// Sets the viewport scale.
        virtual void SetViewportScale(float) = 0;

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

        /// Wait ms
        virtual void Delay(Uint32 ms) = 0;

        /// Get the current window size.
        virtual void GetWindowSize(int *w, int *h) = 0;

        /// Get the renderer output size
        virtual void GetRendererOutputSize(int *w, int *h) = 0;

    /// Renderer related
    public:

        /// Set the drawing colour.
        virtual void SetRenderBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) = 0;

        /// Clear the frambuffer with a previously set colour.
        virtual void ClearRender() = 0;

        /// Update the screen with any rendering performed since the previous call.
        virtual void RenderPresent() = 0;

    /// Drawables
    public:

        /// Given a sprite atlas item construct a drawable for the chosen scale.
        virtual std::unique_ptr<DrawableSpriteI> DrawableCreate(SpriteAtlasItemI*, float) = 0;

        /// Given a size construct a drawable for the chosen scale.
        /// The drawable is to be used as a target rending object. The curren rendering pass
        /// should be rendered onto the texture. The drawable object should then be able to be
        /// rendered using ::DrawableTargetRender.
        virtual std::unique_ptr<DrawableTargetI> DrawableTargetCreate(float, float) = 0;

        /// Render the drawable for the current frame at x, y.
        virtual void DrawableRender(DrawableI*, float, float) = 0;

        /// Render the target drawable for the current frame at x, y.
        virtual void DrawableTargetRender(DrawableTargetI*, float, float) = 0;

    /// Textures
    public:

        /// A concrete instance should load the texture from the filename using
        /// the default internal file access classes. The ownership
        /// of the texture is passed to the caller.
        virtual TextureI *LoadTexture(std::string name, FileStreamI *) = 0;

        /// A concrete instance should create the target texture. A target texture
        /// is able to be rendered upon so a partial render can be developed.
        /// The ownership of the texture is passed to the caller.
        virtual TextureTargetI *CreateTargetTexture(int width, int height) = 0;

        /// A concrete instance should unload the texture.
        virtual void UnloadTexture(TextureI *texture) = 0;

    /// Renderer specific
    public:

        /// Sets the render target to a target drawable. All rendering goes
        /// there until a the target is popped.
        /// Currently not used
        virtual void RendererTargetDrawablePush(DrawableTargetI *) = 0;

        /// Pops the renderer target texture from the stack and returned
        /// to the previous one or the main renderer if the stack is empty.
        /// Currently not used
        virtual void RendererTargetDrawablePop() = 0;

        /// Sets the drawable as the current render target.
        /// Currently not used
        virtual void RendererTargetDrawableSet(DrawableTargetI *) = 0;

        /// Clears the render target so the final render can be applied.
        /// Currently not used
        virtual void RenderTargetClear() = 0;

        /// Clears the buffer before drawing a new frame.
        virtual void RenderClear() = 0;

        /// Sets the draw color.
        virtual void RenderSetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) = 0;

        /// Sets the render scale.
        /// Has no effect on non-sdl providers
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
