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

#ifndef light_manager_hpp
#define light_manager_hpp

#include "common.h"
#include "light_interface.hpp"
#include "light.hpp"
#include "defs.h"

#if TARGET_IOS || TARGET_OSX
#include "AAPLShaderTypes.h"
#endif

namespace engine
{
    /** LightManager
        \addtogroup API_GLOBALS
     */
    /** The LightManager keeps a list of light objects as well as data cache for various
        different shaders.
     */
    class LightManager
    {
        std::vector<std::unique_ptr<Light>> m_lights;
        bool m_lightsActive;
#if TARGET_IOS || TARGET_OSX
        AAPAmbientLLight *m_lightCache; /** kelp aligned to the m_lights light list */
        unsigned long m_lightCacheBufferSize;
        int m_lightCacheCount;
#endif
    public:
        LightManager();
        ~LightManager();

        /** Create a light. The result is being managed by the manager.
            @param type  - type of falloff; either linear or exponential
            @param color - light color, rgb
            @param ambientIntensity - background intensity when not inside param diffuseSize
            @param position - x, y in game coordinates
            @param diffuseSize - size of the light area in game coordinates
            @param diffuseIntensity - the amount of light shine onto the scene wihtin the diffuseSize

            \code{lua}
            -- Create a light with a "linear" falloff, white, with a 0.1 ambient value
            -- positioned at 400, 350 with a diffuse size of 250 and diffuse intensity
            -- of 1.
            light = LightManager:CreateLight("linear", 1, 1, 1, 0.1, 400, 350, 250, 1)
            \endcode
         */
        /** @private */
        Light *CreateLight(LightFalloffType type, Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity);

        /** Create a light. The result is being managed by the manager.

            @param type  - type of falloff; either "linear" or "exponential"
            @param color - light color, rgb
            @param ambientIntensity - background intensity when not inside param diffuseSize
            @param position - x, y in game coordinates
            @param diffuseSize - size of the light area in game coordinates
            @param diffuseIntensity - the amount of light shine onto the scene wihtin the diffuseSize

            \code{lua}
            -- Create a light with a "linear" falloff, white, with a 0.1 ambient value
            -- positioned at 400, 350 with a diffuse size of 250 and diffuse intensity
            -- of 1.
            light = LightManager:CreateLight("linear", 1, 1, 1, 0.1, 400, 350, 250, 1)
            \endcode
         */
        Light *CreateLight(std::string type, Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity);

        /** Delete a light. */
        void DeleteLight(Light*);

        /** Delete all lights. */
        void DeleteAllLights();

        /** Get the light array
            @private */
        auto& GetLights() { return m_lights; };

        /** Getter for the `lights active` state. */
        auto& GetLightsActive() { return m_lightsActive; };

        /** Setter for the `lights active` state. */
        void SetLightsActive(bool);

    private:
#if TARGET_IOS || TARGET_OSX
        AAPAmbientLLight *GetFirstFreeEntry();
        void UpdateCache();
#endif
        
    public:
#if TARGET_IOS || TARGET_OSX
        AAPAmbientLLight *GetLightBuffer() { return m_lightCache; };
        auto GetLightBufferSize() { return m_lightCacheBufferSize; };
        auto GetLightBufferCount() { return m_lightCacheCount; };
#endif
    };
};

#endif /* light_manager_hpp */
