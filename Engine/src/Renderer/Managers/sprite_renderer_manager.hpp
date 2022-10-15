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

#ifndef sprite_renderer_manager_hpp
#define sprite_renderer_manager_hpp

#include "sprite_draw_interface.h"
#include "font_interface.h"
#include <iostream>

namespace engine
{
    /** SpriteRendererManager
        \addtogroup API_GLOBALS
     */
    /** Manages a list of sprite renderers. Those are used by the current
        scene to render the appropriate sprites at particular timeframes.
     */
    class SpriteRendererManager
    {
    public:
        /** Loads a sprite representation for a sprite atlas item descriptor.
            The result is cached. */
        SpriteRepresentationI *SpriteRepresentationStaticLoad(SpriteAtlasItemI *sprite);

        /** Loads a sprite representation for a sprite animation made up from
            individual sprite atlas items.
            The result is cached. */
        /** @private */
        SpriteRepresentationI *SpriteRepresentationAnimatedLoad(int frameAnimationDurationMs, std::vector<SpriteAtlasItemI*> sprites);

        /** Loads a sprite representation for a sprite animation made up of all the
            frames in one sprite atlas.
            The result is cached. */
        SpriteRepresentationI *SpriteRepresentationAnimatedLoad(int frameAnimationDurationMs, SpriteAtlasI*);

        /** Loads a text sprite representation.
            The result is cached. */
        SpriteRepresentationI *SpriteRepresentationTextLoad(FontI*);

        /** Unloads the sprite draw.
         */
        void SpriteDrawUnload(SpriteRepresentationI *spriteDraw);

        /** Unloads all.
         */
        void SpriteDrawDisposeAll();

    private:
        std::vector<std::unique_ptr<SpriteRepresentationI>> m_spriteDraws;
    };
};

#endif /* sprite_renderer_manager_hpp */
