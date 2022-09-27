//
//  engine_screen.hpp
//  Engine-Mac
//
//  Created by krzysp on 12/08/2022.
//

#ifndef engine_screen_hpp
#define engine_screen_hpp

#include "engine_screen_interface.h"
#include "scripting_engine_provider_interface.h"

namespace engine
{
    class EngineScreen: public EngineScreenI
    {
    private:
        Vector2 m_position;
        Rotation m_rotation;
        float m_zPosition;
        float m_alpha;
    public:
        EngineScreen();

    public: // AnimatablePropertiesI
        float       GetScale() { return 1.0; }
        void        SetScale(float x) { };
        void        SetPosition(Vector2 pos) { m_position = pos; };
        Vector2&    GetPosition() { return m_position; };
        void        SetZPosition(float zPos) { };
        float&      GetZPosition() { return m_zPosition; };
        void        SetAlpha(float val) { m_alpha = val; };
        float       GetAlpha() { return m_alpha; };
        void        SetRotation(Rotation rotation) { m_rotation = rotation; };
        Rotation    &GetRotation() { return m_rotation; }


    private: /** scripting */
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(EngineScreen);
    };
};

#endif /* engine_screen_hpp */
