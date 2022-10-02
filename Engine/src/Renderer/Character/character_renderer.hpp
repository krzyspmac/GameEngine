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

#ifndef character_renderer_hpp
#define character_renderer_hpp

#include <iostream>
#include "character_renderer_interface.h"
#include "engine_provider_interface.h"

namespace engine {

    class CharacterRenderer: public CharacterRendererI
    {
    public:
        CharacterRenderer(SpriteAtlasI *characterAtlas, int scale);
        ~CharacterRenderer();
        
    public:
        CharacterWalkRenderer &GetRenderer(CharacterWalkState direction);
        void AppendBodyWalkAnimationFrame(CharacterWalkState direction, SpriteAtlasItemI *sprite, int offsetX, int offsetY, int headOffsetX, int headOffsetY);
        void AppendHeadAnimationFrame(CharacterWalkState direction, SpriteAtlasItemI *sprite, int offsetX, int offsetY);
        void PrepareCharacter();

        void SetScale(float scale) { m_scale = scale; };
        void SetZPosition(float);
        
        void DrawBody(CharacterWalkRenderer&, bool isAnimating, Vector2 position);
        void DrawHead(CharacterWalkRenderer&, bool isAnimating, Vector2 position);
        void Draw(CharacterWalkState, bool isWalking, bool isTalking, Vector2& position);

        void DrawBoundingBox(EngineProviderI &provider);
        void DrawOriginCrosshair(EngineProviderI &provider);

    private:
        int m_headOffsetX;
        int m_headOffsetY;

        int m_headHeadHeight;
        int m_bodyWidth; // max out of all the textures
        int m_bodyHeight; // max out of all the textures
    };
};

#endif /* character_renderer_hpp */
