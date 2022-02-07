//
//  light.hpp
//  Engine-Mac
//
//  Created by krzysp on 05/02/2022.
//

#ifndef light_hpp
#define light_hpp

#include "light_interface.hpp"
#include "scripting_engine_provider_interface.h"

namespace engine
{
    class Light: public LightI
    {
    protected:
        LightFalloutType m_type;
        Color3  m_color;
        float   m_ambientIntensity;
        Origin  m_position;
        float   m_diffuseSize;
        float   m_diffuseIntensity;
        bool    m_isEnabled;

        std::string m_name;
    public:
        Light(LightFalloutType type, Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity)
            : LightI(type, color, diffuseIntensity, position, diffuseSize, diffuseIntensity)
            , m_type(type)
            , m_color(color)
            , m_ambientIntensity(ambientIntensity)
            , m_position(position)
            , m_diffuseSize(diffuseSize)
            , m_diffuseIntensity(diffuseIntensity)
            , m_isEnabled(true)
            , m_name("")
        { };

        /** Geter for the light fallout type */
        LightFalloutType GetType();

        /** Setter for the light fallout type */
        void SetType(LightFalloutType);

        /** Geter for the ambient color */
        Color3& GetColor();

        /** Setter for the ambient color */
        void SetColor(Color3);

        /** Getter for the ambient intensity */
        float& GetAmbientIntensity();

        /** Setter for the ambient inetensity */
        void SetAmbientIntensity(float);

        /** Getter for the diffuse intensity */
        float& GetDiffuseIntensity();

        /** Setter for the diffuse intensity */
        void SetDiffuseIntensity(float);

        /** Getter for the diffuse size */
        float& GetDiffuseSize();

        /** Setter for the diffuse size */
        void SetDiffuseSize(float);

        /** Getter for the position */
        Origin& GetPosition();

        /** Setter for the position */
        void SetPosition(Origin);

        /** Getter for the enabled attribute */
        bool GetIsEnabled();

        /** Setter for the enabled attribute */
        void SetIsEnabled(bool);

        /** Getter for the name */
        std::string& GetName();

        /** Setter for the name */
        void SetName(std::string value);

    private: /** scripting */
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(Light);
    };
};

#endif /* light_hpp */
