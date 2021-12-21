//
//  engine_provider.hpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#ifndef engine_provider_hpp
#define engine_provider_hpp

#include "common.h"
#include "common_engine_impl.h"
#include "engine_provider_interface.h"
#include "texture_interface.h"
#include "font_interface.h"

namespace engine
{

class EngineProvider : public EngineProviderI
{
    public:
        EngineProvider(engine::SDL_APP *engineHandle)
            :EngineProviderI(), m_engineHandle(engineHandle)
        {
        }

    public:

        void GetMousePosition(int *x, int *y);

        TextureI *LoadTexture(std::string name);
        void UnloadTexture(TextureI *texture);
        void DrawTexture(TextureI *texture, int x, int y);

        FontI *LoadFont(std::string name);
        void DrawText(FontI *font, std::string text, int x, int y, int r, int g, int b, TEXT_ALIGNMENT align);

    //        void DrawDebugText(uint16_t _x, uint16_t _y, uint8_t _attr, const char* _format, ...) override;

    private:
        engine::SDL_APP *m_engineHandle;
    };

};

#endif /* engine_provider_hpp */
