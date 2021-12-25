//
//  character.hpp
//  Engine
//
//  Created by krzysp on 25/12/2021.
//

#ifndef character_renderer_hpp
#define character_renderer_hpp

#include <iostream>
#include "character_renderer_interface.h"

namespace engine {

    class CharacterRenderer: public CharacterRendererI
    {
    public:
        CharacterRenderer(SpriteAtlasI *characterAtlas, int scale);

    public:
        CharacterWalkRenderer &GetRenderer(CharacterWalkDirection direction);
        void AppendBodyWalkAnimationFrame(CharacterWalkDirection direction, SpriteAtlasItemI *sprite, int offsetX, int offsetY, int headOffsetX, int headOffsetY);
        void AppendHeadAnimationFrame(CharacterWalkDirection direction, SpriteAtlasItemI *sprite, int offsetX, int offsetY);

        void DrawBody(CharacterWalkDirection, bool isAnimating, int x, int y);
        void DrawHead(CharacterWalkDirection, bool isAnimating, int x, int y);

    private:
        int m_headOffsetX;
        int m_headOffsetY;
    };
};

#endif /* character_renderer_hpp */
