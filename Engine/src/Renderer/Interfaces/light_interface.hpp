//
//  light_interface.hpp
//  Engine
//
//  Created by krzysp on 05/02/2022.
//

#ifndef light_interface_h
#define light_interface_h

#include "common_engine_impl.h"
#include <iostream>

namespace engine
{
    class LightI
    {
    public:
        LightI(Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity)
        { };

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
