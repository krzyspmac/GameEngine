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
    class LightManager
    {
        std::vector<std::unique_ptr<LightI>> m_lights;

#if TARGET_IOS || TARGET_OSX
        AAPAmbientLLight * m_lightCache;
        unsigned long m_lightCacheBufferSize;
        int m_lightCacheCount;
#endif
    public:
        LightManager();

        /** Create a light. The result is being managed by the manager. */
        LightI *CreateLight(Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity);

        /** Delete a light. */
        void DeleteLight(LightI*);

        /** Delete all lights. */
        void DeleteAllLights();

    public: /** Rendering related */

#if TARGET_IOS || TARGET_OSX
        AAPAmbientLLight *GetLightBuffer() { return m_lightCache; };
        auto GetLightBufferSize() { return m_lightCacheBufferSize; };
        auto GetLightBufferCount() { return m_lightCacheCount; };
#endif

    private:
        void UpdateCache();

    private: /** scripting */
        /** @private */
        SCRIPTING_INTERFACE_HEADERS(LightManager);
    };
};

#endif /* light_manager_hpp */
