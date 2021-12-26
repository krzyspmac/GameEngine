//
//  character.hpp
//  Engine
//
//  Created by krzysp on 25/12/2021.
//

#ifndef character_interface_hpp
#define character_interface_hpp

#include "character_renderer_interface.h"

namespace engine
{

    class CharacterI {
    public:
        CharacterI(): m_characterRenderer(NULL) { };

        virtual ~CharacterI() {
            if (m_characterRenderer)
            {
                delete m_characterRenderer;
            };
        }

    public:
        CharacterRendererI *GetCharacterRenderer() { return m_characterRenderer; };

        /// Draw the character. The origin aligned to the bottom center part of the character.
        virtual void Draw(int x, int y) = 0;

        /// Set the character scale
        virtual void SetScale(float scale) = 0;

        virtual void Change() = 0;

    protected:
        CharacterRendererI *m_characterRenderer;
    };
};

#endif /* character_interface_hpp */
