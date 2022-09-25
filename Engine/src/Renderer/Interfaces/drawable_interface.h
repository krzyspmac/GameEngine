//
//  drawable_interface.h
//  Engine
//
//  Created by krzysp on 12/01/2022.
//

#ifndef drawable_interface_h
#define drawable_interface_h

#include "common.h"
#include "texture_interface.h"
#include "sprite_atlas_interface.h"

namespace engine
{
    /** Declares an abstract interface for the final object that will be drawn using the EngineProviderI.
        Different backend for different libraries might declare differently working concrete instances.
        The values held here should be as close to the low-level rendering APIs as possible. Sometimes
        providing raw bytes when necessary for Metal, DirectX or OpenGL.

        The `drawable` is usually composed of vertex data and texture data.
     */
    class DrawableI
    {
    protected:
        TextureI *m_texture;
        Rect m_textureRect;
        Color4 m_colorMod;
        float m_flipHorizontal;
        float m_scale;
        float m_alpha;
        float m_zPos;
        bool m_flippedHorizontally;
        bool m_acceptsLight;
        bool m_rotatable;
    public:
        DrawableI(float width, float height)
            : m_scale(1.0f)
            , m_alpha(1.0f)
            , m_zPos(0.0f)
            , m_flippedHorizontally(false)
            , m_textureRect( { {0, 0}, {(int)width, (int)height} } )
            , m_acceptsLight(true)
            , m_colorMod{1.f, 1.f, 1.f, 1.f}
            , m_rotatable(true)
        { };

        virtual ~DrawableI() { };

        /** Can the sprite be drawn */
        virtual bool CanDraw() { return true; };

        /** Set the drawable scale */
        virtual void SetScale(float val) { m_scale = val; }

        /** Get the drawable scale */
        virtual float *GetScale() { return &m_scale; };
        
        /** Set the z-axis position.
            Possible values range from 0.0 to 1.0, 0.0 being closest to the "camera" and
            1.0 being further away. Of two object: one being at 1.0 and one being at 0.0
            the one at 0.0 will overlap the one at 1.0.
            */
        virtual void SetZPosition(float value) { m_zPos = value; };

        /** Set the drawable alpha; 0-1 */
        virtual void SetAlpha(float val) { m_alpha = val; };

        /** Get the drawable alpha; 0-1 */
        virtual float *GetAlpha() { return &m_alpha; };

        /** Set the color mod */
        virtual void SetColorMod(Color4 mod) { m_colorMod = mod; };

        /** Get the color mod */
        virtual Color4& GetColorMod() { return m_colorMod; };

        /** Rotation, low-level */
        virtual void SetRotation(float, float, float) = 0;

        /** Rotation, low-level */
        virtual void GetRotation(float*, float*, float*) = 0;

        /** Rotatable */
        virtual void SetRotateable(bool) = 0;

    public: // Texture related

        /** Set the drawable texture */
        virtual void SetTexture(TextureI *texture) { m_texture = texture; };

        /** Get the drawable texture */
        virtual TextureI *GetTexture() { return m_texture; };

        /** Should the rendered sprite be flipped horizontally */
        virtual bool IsFlippedHorizontally() { return m_flippedHorizontally; }

        /** Set the rendered sprite be flipped horizontally */
        virtual void SetFlippedHorizontally(bool value) { m_flippedHorizontally = value; };

        /** Get the texture rect that this sprite is in */
        virtual Rect& GetTextureRect() { return m_textureRect; };

        /** */
        virtual bool& GetAcceptsLight() { return m_acceptsLight; };
    };

    /** Declares an abstract interface dealing with a drawable for a sprite
        that exists as {x, y, width, height} component from the loaded sprite atlas.
     */
    class DrawableSpriteI: public DrawableI
    {
    protected:
        SpriteAtlasItemI *m_atlasItem;
    public:
        DrawableSpriteI(SpriteAtlasItemI *atlasItem)
            : DrawableI((int)atlasItem->GetWidth(), (int)atlasItem->GetHeight())
        {
            SetSpriteAtlasItem(atlasItem);
        };

        virtual ~DrawableSpriteI() { };

        /** Can the drawable be presented. Override */
        virtual bool CanDraw() = 0;

    public: // Sprite atlas related

        /** Set the sprite atlas item. Cannot be nil */
        void SetSpriteAtlasItem(SpriteAtlasItemI *value) {
            m_atlasItem = value;
            m_textureRect = { {(int)m_atlasItem->GetX(), (int)m_atlasItem->GetY()}, {(int)m_atlasItem->GetWidth(), (int)m_atlasItem->GetHeight()} };
        }

        /** Retrieve the sprite atlas */
        SpriteAtlasItemI *GetSpriteAtlasItem() { return m_atlasItem; };
    };

    /** Declares an abstrzct interface for the target drawable that is capable of accepting
        the current render pass and store it in its texture.
     */
    class DrawableTargetI: public DrawableI
    {
    public:
        DrawableTargetI(float width, float height)
            : DrawableI(width, height)
        { };
        
        void SetTexture(TextureTargetI *texture) { m_texture = texture; };
        TextureTargetI *GetTexture() { return (TextureTargetI*)m_texture; };
    };
};

#endif /* drawable_interface_h */
