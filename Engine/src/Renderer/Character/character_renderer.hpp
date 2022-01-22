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
