//
//  character_interface.h
//  Engine
//
//  Created by krzysp on 25/12/2021.
//

#ifndef character_interface_h
#define character_interface_h

#include "sprite_atlas_interface.h"

namespace engine
{
    typedef enum
    {

    } CharacterWalkDirection;

    /// Describes the character body renderer that includes
    /// the relation between the body and the head. The relation
    /// is per frame.
    /// By default the head will be drawn on top of the body.
    /// Additional tweaks are possible.
    class CharacterBodyPartRendererI
    {
    public:
        CharacterBodyPartRendererI(SpriteAtlasItemI *sprite) : m_bodySprite(sprite) { };

        SpriteAtlasItemI *GetSprite() { return m_bodySprite; };
    protected:
        SpriteAtlasItemI *m_bodySprite;
    };

    class CharacterBodyRenderer: public CharacterBodyPartRendererI
    {
    public:
        CharacterBodyRenderer(SpriteAtlasItemI *sprite)
            : CharacterBodyPartRendererI(sprite), m_headOffsetX(0), m_headOffsetY(0)
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
        CharacterHeadRenderer(SpriteAtlasItemI *sprite)
            : CharacterBodyPartRendererI(sprite)
        { };

    };

    /// Describes the walking renderer for the body and the head.
    class CharacterWalkRenderer
    {
    public:
        CharacterWalkRenderer() { };

        /// Will take ownershiop of the object.
        void AppendBodyRenderer(CharacterBodyRenderer* value);
        void SetBodyAnimationDelay(int &delay) { m_bodyAnimationDelay = delay; };
        unsigned long GetBodyAnimationCount() { return m_bodyRenderers.size(); }
        CharacterBodyRenderer *GetBodyRendererAtIndex(int index) { return m_bodyRenderers.at(index).get(); };
        int &GetBodyAnimationDelay() { return m_bodyAnimationDelay; };
        int &GetBodyMaxWidth() { return m_bodyMaxWidth; };
        int &GetBodyMaxHeight() { return m_bodyMaxHeight; };

        void AppendHeadRenderer(CharacterHeadRenderer* value);
        void SetHeadAnimationDelay(int &delay) { m_headAnimationDelay = delay; };
        unsigned long GetHeadAnimationCount() { return m_headRenderers.size(); }
        CharacterHeadRenderer *GetHeadRendererAtIndex(int index) { return m_headRenderers.at(index).get(); };
        int &GetHeadAnimationDelay() { return m_headAnimationDelay; };
        int &GetHeadMaxWidth() { return m_headMaxWidth; };
        int &GetHeadMaxHeight() { return m_headMaxHeight; };

    private:
        std::vector<std::unique_ptr<CharacterBodyRenderer>> m_bodyRenderers;
        int m_bodyAnimationDelay;
        int m_bodyMaxWidth;
        int m_bodyMaxHeight;

        std::vector<std::unique_ptr<CharacterHeadRenderer>> m_headRenderers;
        int m_headAnimationDelay;
        int m_headMaxWidth;
        int m_headMaxHeight;
    };

    /// Describes the character body. The character is made of the body and the head.
    /// The body is drawn first, then the head. The body, by default, is being drawn
    /// on top of the body. Additional tweak are possible (when the body is off to one
    /// side for instance.
    /// Upon concrete instance creation CharacterBodyRendererI are being created and those
    /// are being rendered. Those can receive position tweak if needed.
    class CharacterI
    {
    public:
        CharacterI(SpriteAtlasI *characterAtlas, int scale): m_characterAtlas(characterAtlas), m_scale(scale) {};

        virtual ~CharacterI() {
            delete m_walkR;
            delete m_headR;
        };

    public:
        /// Assume the head is completely stationary. The body can have different offset.
        virtual void SetHeadR(std::vector<SpriteAtlasItemI*> &sprites, int animationDelayMs) = 0;

        /// Set different animations.
        virtual void SetWalkR(std::vector<SpriteAtlasItemI*> &sprites, int animationDelayMs) = 0;

        /// Set custom offset for head renderer for a particular head sprite.
        virtual void SetHeadOffsetForSpriteNamed(std::string spriteName, int offsetX, int offsetY) = 0;

        /// Draw the character.
        virtual void Draw(int x, int y) = 0;

        /// Draw the body
        virtual void DrawBody(int x, int y) = 0;

        /// Draw the head
        virtual void DrawHead(int x, int y) = 0;

    protected:
        SpriteAtlasI *m_characterAtlas;
        int m_scale;

        CharacterWalkRenderer *m_walkR;
        CharacterWalkRenderer *m_headR;
    };
};

#endif /* character_interface_h */
