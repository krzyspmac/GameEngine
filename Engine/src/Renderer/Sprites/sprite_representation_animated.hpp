//
//  sprite_draw_animated.hpp
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#ifndef sprite_draw_animated_hpp
#define sprite_draw_animated_hpp

#include "sprite_draw_interface.h"
#include "sprite_atlas_interface.h"
#include "sprite_representation_static.hpp"
#include "scripting_engine_provider_interface.h"

namespace engine
{
    class SpriteRepresentationAnimated: public SpriteRepresentationI
    {
    public:

        SpriteRepresentationAnimated(std::vector<SpriteAtlasItemI*> sprites, int frameAnimationDurationMs);
        virtual ~SpriteRepresentationAnimated();
        
        static SpriteRepresentationAnimated *CreateFromAtlas(std::vector<std::unique_ptr<SpriteAtlasItemI>>& sprites, int frameAnimationDurationMs);

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

        /** Set Alpha */
        void SetAlpha(float val);

        /** Sets animation frame duration in ms */
        void SetAnimationFrameDuration(float);

    public: /** Overrides */

        void SetAcceptsLight(bool val);
        void DrawAt(int x, int y);
        void Draw();
        void SetColorMod(Color4);
        
    private:
        void PrepareAnimation();
        
    private:
        int m_frameAnimationDurationMs;
        std::vector<SpriteRepresentationStatic*> m_sprites;
        int m_maxWidth;
        int m_maxHeight;
        
    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(SpriteRepresentationAnimated);
    };

};

#endif /* sprite_draw_animated_hpp */
