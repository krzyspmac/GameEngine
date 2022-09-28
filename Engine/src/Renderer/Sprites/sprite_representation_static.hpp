//
//  sprite_draw.hpp
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#ifndef sprite_draw_hpp
#define sprite_draw_hpp

#include "scripting_engine_provider_interface.h"
#include "sprite_draw_interface.h"
#include "drawable_interface.h"

namespace engine
{

    class SpriteRepresentationStatic: public SpriteRepresentationI
    {
    public:
        SpriteRepresentationStatic(SpriteAtlasItemI *spriteAtlasItem);
        virtual ~SpriteRepresentationStatic() { };
        
    public: // AnimatablePropertiesI
        void SetScale(float x);
        void SetPosition(Vector2 &pos);
        Vector2& GetPosition() { return m_position; };
        Size& GetSize() { return m_sprite->GetSize(); };
        void SetZPosition(float zPos);
        SpriteAtlasItemI *GetSpriteAtlasItem() { return m_sprite; };
        void SetRotation(Rotation rotation);

    public: // SpriteRepresentationI
        void DrawAt(int x, int y);
        void Draw();

    public:

    private:
        SpriteAtlasItemI *m_sprite;
    };
};


#endif /* sprite_draw_hpp */
