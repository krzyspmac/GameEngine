// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef light_hpp
#define light_hpp

#include "light_interface.hpp"

namespace engine
{
    class Light: public LightI
    {
    protected:
        LightFalloffType m_type;
        Color3  m_color;
        float   m_ambientIntensity;
        Origin  m_position;
        float   m_diffuseSize;
        float   m_diffuseIntensity;
        bool    m_isEnabled;

        std::string m_name;
    public:
        Light(LightFalloffType type, Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity)
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
        LightFalloffType GetType();

        /** Setter for the light fallout type */
        void SetType(LightFalloffType);

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
    };
};

#endif /* light_hpp */
