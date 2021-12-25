//
//  character.hpp
//  Engine
//
//  Created by krzysp on 25/12/2021.
//

#ifndef character_hpp
#define character_hpp

#include <iostream>
#include "character_interface.h"

namespace engine {

    class CharacterRenderer: public CharacterRendererI
    {
    public:
        CharacterRenderer(SpriteAtlasI *characterAtlas, int scale);

    public:
        CharacterWalkRenderer &GetRenderer(CharacterWalkDirection direction);
        void AppendBodyWalkAnimationFrame(CharacterWalkDirection direction, SpriteAtlasItemI *sprite, int headOffsetX, int headOffsetY);
        void AppendHeadAnimationFrame(CharacterWalkDirection direction, SpriteAtlasItemI *sprite);

        void Draw(int x, int y);
        void DrawBody(int x, int y);
        void DrawHead(int x, int y);

    private:
        int m_headOffsetX;
        int m_headOffsetY;
    };
};

#endif /* character_hpp */
