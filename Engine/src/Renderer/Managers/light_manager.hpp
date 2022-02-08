//
//  light_manager.hpp
//  Engine-Mac
//
//  Created by krzysp on 05/02/2022.
//

#ifndef light_manager_hpp
#define light_manager_hpp

#include "common.h"
#include "scripting_engine_provider_interface.h"
#include "light_interface.hpp"
#include "defs.h"

#if TARGET_IOS || TARGET_OSX
#include "AAPLShaderTypes.h"
#endif

namespace engine
{
    /** LightManager
        \addtogroup API_GLOBALS

        The LightManager keeps a list of light objects as well as data cache for various
        different shaders. The cache gets updated on create/delete. Updates go
        directly to the cache.
     */
    class LightManager
    {
        std::vector<std::unique_ptr<LightI>> m_lights;
        bool m_lightsActive;
#if TARGET_IOS || TARGET_OSX
        AAPAmbientLLight *m_lightCache; /** kelp aligned to the m_lights light list */
        unsigned long m_lightCacheBufferSize;
        int m_lightCacheCount;
#endif
    public:
        LightManager();
        ~LightManager();

        /** Create a light. The result is being managed by the manager. */
        LightI *CreateLight(LightFalloutType type, Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity);

        /** Create a light helper. Type as string (linear|quadratic) */
        LightI *CreateLight(std::string type, Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity);

        /** Delete a light. */
        void DeleteLight(LightI*);

        /** Delete all lights. */
        void DeleteAllLights();

        /** Get the light array
            @private */
        auto& GetLights() { return m_lights; };

        auto& GetLightActive() { return m_lightsActive; };

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

    private: /** scripting */
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(LightManager);
    };
};

#endif /* light_manager_hpp */
