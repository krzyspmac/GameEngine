//
//  sprite_representation_text.hpp
//  Engine
//
//  Created by krzysp on 13/02/2022.
//

#ifndef sprite_representation_text_hpp
#define sprite_representation_text_hpp

#include "sprite_draw_interface.h"
#include "sprite_atlas_interface.h"
#include "sprite_representation_static.hpp"
#include "font_interface.h"
#include "scripting_engine_provider_interface.h"

namespace engine
{
    class SpriteRepresentationText: public SpriteRepresentationI
    {
        FontI* m_bitmapFont;
        std::string m_text;
        OriginF m_shadowOffset;
        Color4 m_shadowColor;
        float m_lineMultiplier;
        TEXT_ALIGNMENT m_textAlignment;
    public:
        SpriteRepresentationText(FontI*);

        /** Text */
        void SetText(std::string);

        /** Scale setter */
        void SetScale(float x);

        /** Position this sprite in game coordinates */
        void SetPosition(Vector2 pos);

        /** Sets the alpha. Values range from 0-1.
            Default value is 1.
         */
        void SetAlpha(float val);

        /** Lighting setter */
        void SetAcceptsLight(bool val);

        /** Shadow color. If alpha is <= 0 shadow is disabled. Default is clear color. */
        void SetShadowColor(Color4);

        /** Set shadow offset. Default is { 1, 1 } */
        void SetShadowOffset(OriginF);

        /** Set the line multiplier. Default is 1.f and is based on what was initially
            defined in the .fnt file */
        void SetLineHeightMultiplier(float);

        /** Set the alignment. "left"|"center"|"right"
            */
        void SetAlignment(std::string);

    public:
        void DrawAt(int x, int y);
        void Draw();
        void SetColorMod(Color4 val);

    /// ScriptingInterface
    public:
        /// @private
        SCRIPTING_INTERFACE_HEADERS(SpriteRepresentationText);
    };
};

#endif /* sprite_representation_text_hpp */
