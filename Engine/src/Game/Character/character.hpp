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

    class Character: public CharacterI
    {
    public:
        Character(SpriteAtlasI *characterAtlas, int scale);

    public:
        void SetWalkR(std::vector<SpriteAtlasItemI*> &sprites, int animationDelayMs);
        void SetHeadR(std::vector<SpriteAtlasItemI*> &sprites, int animationDelayMs);
        void SetHeadOffsetForSpriteNamed(std::string spriteName, int offsetX, int offsetY);

        void Draw(int x, int y);
        void DrawBody(int x, int y);
        void DrawHead(int x, int y);

    private:
        int m_headOffsetX;
        int m_headOffsetY;
    };
};

#endif /* character_hpp */
