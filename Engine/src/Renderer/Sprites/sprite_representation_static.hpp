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

    class SpriteRepresentationStatic: public SpriteRepresentationI, public ScriptingInterface
    {
    public:
        /** @private */
        SpriteRepresentationStatic(SpriteAtlasItemI *spriteAtlasItem);
        virtual ~SpriteRepresentationStatic() { };
        
    public:
        /** Sets the scale.
         */
        void SetScale(float x);

        /** Sets the position for the sprite.
         */
        void SetPosition(Vector2 &pos);

        /** Gets the current position for the sprite.
         */
        Vector2& GetPosition() { return m_position; };

        /** Get width & size of the sprite.
         */
        Size& GetSize() { return m_sprite->GetSize(); };

        /** Set the z-axis position.
            Possible values range from 0.0 to 1.0, 0.0 being closest to the "camera" and
            1.0 being further away. Of two object: one being at 1.0 and one being at 0.0
            the one at 0.0 will overlap the one at 1.0.
            */
        void SetZPosition(float zPos);

        /** Get the current sprite atlas item for this sprite */
        SpriteAtlasItemI *GetSpriteAtlasItem() { return m_sprite; };

        /** Set the rotation and pass it to the drawable */
        void SetRotation(Rotation rotation);

        /** Draws the sprite.
         */
        void DrawAt(int x, int y);

        /** Draws the sprite.
         */
        void Draw();

    public:

    private:
        SpriteAtlasItemI *m_sprite;

    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(SpriteRepresentationStatic);
    };
};

#endif /* sprite_draw_hpp */
