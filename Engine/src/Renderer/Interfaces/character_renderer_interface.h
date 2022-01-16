//
//  character_interface.h
//  Engine
//
//  Created by krzysp on 25/12/2021.
//

#ifndef character_interface_h
#define character_interface_h

#include "sprite_atlas_interface.h"
#include "texture_target.hpp"
#include "vector2.hpp"
#include "drawable_interface.h"

namespace engine
{
    typedef enum
    {
        STAND_RIGHT             = 1,
        RIGHT                   = 2,

        LEFT                    = 3,
        STAND_LEFT              = 4,

        FORWARD                 = 5,
        STAND_FORWARD           = 6,

        BACKWARD                = 7,
        STAND_BACKWARD          = 8
    } CharacterWalkState;

    /// Describes the character body renderer that includes
    /// the relation between the body and the head. The relation
    /// is per frame.
    /// By default the head will be drawn on top of the body.
    /// Additional tweaks are possible.
    class CharacterBodyPartRendererI
    {
    public:
        CharacterBodyPartRendererI(SpriteAtlasItemI *sprite, int offsetX, int offsetY)
            : m_bodySprite(sprite), m_bodyOffsetX(offsetX), m_bodyOffsetY(offsetY)
        { };

        SpriteAtlasItemI *GetSprite() { return m_bodySprite; };

        void SetBodyOffsetX(int value) { m_bodyOffsetX = value; };
        void SetBodyOffsetY(int value) { m_bodyOffsetY = value; };

        int &GetBodyOffsetX() { return m_bodyOffsetX; };
        int &GetBodyOffsetY() { return m_bodyOffsetY; };

    protected:
        SpriteAtlasItemI *m_bodySprite;
        int m_bodyOffsetX;
        int m_bodyOffsetY;
    };

    /// Describes a frame of the body renderer. Each body frame
    /// can have custom head offset.
    class CharacterBodyRenderer: public CharacterBodyPartRendererI
    {
    public:
        CharacterBodyRenderer(SpriteAtlasItemI *sprite, int offsetX, int offsetY)
            : CharacterBodyPartRendererI(sprite, offsetX, offsetY), m_headOffsetX(0), m_headOffsetY(0)
        { };

        void SetHeadOffsetX(int &value) { m_headOffsetX = value; };
        void SetHeadOffsetY(int &value) { m_headOffsetY = value; };

        int &GetHeadOffsetX() { return m_headOffsetX; };
        int &GetHeadOffsetY() { return m_headOffsetY; };
    private:
        int m_headOffsetX;
        int m_headOffsetY;
    };

    class CharacterHeadRenderer: public CharacterBodyPartRendererI
    {
    public:
        CharacterHeadRenderer(SpriteAtlasItemI *sprite, int offsetX, int offsetY)
            : CharacterBodyPartRendererI(sprite, offsetX, offsetY)
        { };

    };

    /// Describes the walking renderer for the body and the head.
    class CharacterWalkRenderer
    {
    public:
        CharacterWalkRenderer()
            : m_bodyMaxWidth(0), m_bodyMaxHeight(0), m_bodyAnimationDelay(0),
              m_headMaxWidth(0), m_headMaxHeight(0), m_headAnimationDelay(0), m_isReversed(false)
        { };

        /// Will take ownershiop of the object.
        void AppendBodyRenderer(CharacterBodyRenderer* value);
        void SetBodyAnimationDelay(int delay) { m_bodyAnimationDelay = delay; };
        unsigned long GetBodyAnimationCount() { return m_bodyRenderers.size(); }
        CharacterBodyRenderer *GetBodyRendererAtIndex(int index) { return m_bodyRenderers.at(index).get(); };
        int &GetBodyAnimationDelay() { return m_bodyAnimationDelay; };
        int &GetBodyMaxWidth() { return m_bodyMaxWidth; };
        int &GetBodyMaxHeight() { return m_bodyMaxHeight; };

        void AppendHeadRenderer(CharacterHeadRenderer* value);
        void SetHeadAnimationDelay(int delay) { m_headAnimationDelay = delay; };
        unsigned long GetHeadAnimationCount() { return m_headRenderers.size(); }
        CharacterHeadRenderer *GetHeadRendererAtIndex(int index) { return m_headRenderers.at(index).get(); };
        int &GetHeadAnimationDelay() { return m_headAnimationDelay; };
        int &GetHeadMaxWidth() { return m_headMaxWidth; };
        int &GetHeadMaxHeight() { return m_headMaxHeight; };

        void SetReversed(bool value) { m_isReversed = value; };
        bool GetIsReversed() { return m_isReversed; }

    private:
        std::vector<std::unique_ptr<CharacterBodyRenderer>> m_bodyRenderers;
        int m_bodyAnimationDelay;
        int m_bodyMaxWidth;
        int m_bodyMaxHeight;

        std::vector<std::unique_ptr<CharacterHeadRenderer>> m_headRenderers;
        int m_headAnimationDelay;
        int m_headMaxWidth;
        int m_headMaxHeight;

        bool m_isReversed;
    };

    /// Describes the character body. The character is made of the body and the head.
    /// The body is drawn first, then the head. The body, by default, is being drawn
    /// on top of the body. Additional tweak are possible (when the body is off to one
    /// side for instance.
    /// Upon concrete instance creation CharacterBodyRendererI are being created and those
    /// are being rendered. Those can receive position tweak if needed.
    class CharacterRendererI
    {
    public:
        CharacterRendererI(SpriteAtlasI *characterAtlas, float scale)
            : m_characterAtlas(characterAtlas), m_scale(scale), m_bufferDrawable(nullptr) {};

        virtual ~CharacterRendererI() {
        };

    public:
        /// Returns the "right" walking animation;
        virtual CharacterWalkRenderer &GetRenderer(CharacterWalkState direction) = 0;

        /// Appends a frame of animation.
        virtual void AppendBodyWalkAnimationFrame(CharacterWalkState direction, SpriteAtlasItemI *sprite, int offsetX, int offsetY, int headOffsetX, int headOffsetY) = 0;

        /// Appends a frame of animation.
        virtual void AppendHeadAnimationFrame(CharacterWalkState direction, SpriteAtlasItemI *sprite, int offsetX, int offsetY) = 0;

        /// Preprares the character buffer textures & others. The character is being
        /// drawn in parts and the the parts are being drawn to a buffer texture.
        /// Only after all the parts rendered on to the buffer texture is the
        /// buffer texture rendered.
        virtual void PrepareCharacter() = 0;

        /// Sets the scale.
        virtual void SetScale(float scale) = 0;

        /// Draw all the character.
        virtual void Draw(CharacterWalkState, bool isWalking, bool isTalking, Vector2& position) = 0;

    protected:
        SpriteAtlasI *m_characterAtlas;
        float m_scale;

        CharacterWalkRenderer m_standR;
        CharacterWalkRenderer m_walkR;

        CharacterWalkRenderer m_walkL;
        CharacterWalkRenderer m_standL;

        CharacterWalkRenderer m_walkF;
        CharacterWalkRenderer m_standF;

        CharacterWalkRenderer m_walkB;
        CharacterWalkRenderer m_standB;

        std::unique_ptr<DrawableTargetI> m_bufferDrawable;
    };

    inline CharacterWalkState CharacterWalkStateGetStanding(CharacterWalkState state)
    {
        switch (state)
        {
            case STAND_RIGHT:
                return STAND_RIGHT;
            case RIGHT:
                return STAND_RIGHT;
            case LEFT:
                return STAND_LEFT;
            case STAND_LEFT:
                return STAND_LEFT;
            case FORWARD:
                return STAND_FORWARD;
            case STAND_FORWARD:
                return STAND_FORWARD;
            case BACKWARD:
                return STAND_BACKWARD;
            case STAND_BACKWARD:
                return STAND_BACKWARD;
        }
    }

}; // namespace

#endif /* character_interface_h */
