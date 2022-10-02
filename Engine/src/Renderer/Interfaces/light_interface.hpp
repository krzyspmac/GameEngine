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

#ifndef light_interface_h
#define light_interface_h

#include <iostream>
#include "size.hpp"
#include "general.hpp"

namespace engine
{
    typedef enum
    {
        LIGHT_FALLOUT_TYPE_LINEAR       = 0
      , LIGHT_FALLOUT_TYPE_EXP          = 1
    } LightFalloffType;

    typedef struct {
        std::string name;
        LightFalloffType type;
    } LightInfo;

    class LightI
    {
    public:
        LightI(LightFalloffType type, Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity)
        { };

        static std::vector<LightInfo>& LIGHT_TYPES() {
            static std::vector<LightInfo> lightTypes =
            {
                { "linear", LIGHT_FALLOUT_TYPE_LINEAR }
              , { "exponential", LIGHT_FALLOUT_TYPE_EXP }
            };

            return lightTypes;
        }

        static LightFalloffType GetFalloutTypeForName(std::string type)
        {
            auto lightInfo = matching<LightInfo>(LightI::LIGHT_TYPES(), [&](LightInfo& info){
                return info.name == type;
            });
            if (lightInfo != nullptr)
            {
                return lightInfo->type;
            }
            else
            {
                return LIGHT_FALLOUT_TYPE_LINEAR;
            }
        }

        virtual LightFalloffType GetType() = 0;
        virtual void SetType(LightFalloffType) = 0;
        virtual Color3& GetColor() = 0;
        virtual void SetColor(Color3) = 0;
        virtual bool GetIsEnabled() = 0;
        virtual void SetIsEnabled(bool) = 0;
        virtual std::string& GetName() = 0;
        virtual float& GetAmbientIntensity() = 0;
        virtual void SetAmbientIntensity(float) = 0;
        virtual float& GetDiffuseIntensity() = 0;
        virtual void SetDiffuseIntensity(float) = 0;
        virtual float& GetDiffuseSize() = 0;
        virtual void SetDiffuseSize(float) = 0;
        virtual Origin& GetPosition() = 0;
        virtual void SetPosition(Origin) = 0;
    };
};

#endif /* light_interface_h */
