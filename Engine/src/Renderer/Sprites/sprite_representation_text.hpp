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

#include "sprite_representation_text_interface.h"

namespace engine
{
    class SpriteRepresentationText: public SpriteRepresentationTextI
    {
        FontI* m_bitmapFont;
        std::string m_text;
        OriginF m_shadowOffset;
        Color4 m_shadowColor;
        float m_lineMultiplier;
        float m_alpha;
        TEXT_HORIZONTAL_ALIGNMENT m_textHorizontalAlignment;
        TEXT_VERTICAL_ALIGNMENT m_textVerticalAlignment;
    public:
        SpriteRepresentationText(FontI*);

        void SetText(std::string);
        
        /** Get text */
        std::string GetText() { return m_text; };

        /** Scale setter */
        void SetScale(float x);

        /** Position this sprite in game coordinates */
        void SetPosition(Vector2 pos);

        void SetAlpha(float val);

        float GetAlpha();
        
        void SetZPosition(float zPos);

        void SetAcceptsLight(bool val);

        void SetShadowColor(Color4);

        void SetShadowOffset(OriginF);

        void SetLineHeightMultiplier(float);

        void SetHorizontalAlignment(std::string);
        
        void SetVerticalAlignment(std::string);

        void SetRotation(Rotation);

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
