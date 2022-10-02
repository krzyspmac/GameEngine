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

#ifndef engine_hpp
#define engine_hpp

#include "defs.h"
#include "common.h"
#include "engine_interface.h"
#include "engine_provider_interface.h"
#include "file_access_provider.h"
#include "character_renderer_interface.h"
#include "character_interface.h"
#include "texture_target.hpp"
#include "character_mover_interface.h"
#include "path_finder.hpp"
#include "font_bitmap.hpp"

namespace engine
{
    class Engine: public EngineI
    {
    public:
        ///
        Engine(EngineProviderI &engine,
               TextureManager &textureManager,
               FileAccessI &fileAccess,
               FontManager &fontManager,
               EventProviderI &eventProvider,
               EventsManager &eventsManager,
               CharacterManager &characterManager,
               SceneManager &sceneManager,
               SpriteAtlasManager &spriteAtlasManager,
               SpriteRendererManager &spriteRendererManager,
               ConsoleRendererI &consoleRenderer,
               Size viewportSize
        );
        ~Engine();

    public:
        void SetupInit();
        void Setup();
        int ProcessEvents();
        void FrameBegin();
        void ProcessScript();
        void FrameDrawObjects();
        void FrameDrawLightObjects();
        void FrameDrawTopObjects();
        void FrameEnd();
    public:
        void SetCapRate(int fps);

    private:
        void RenderScene();
        void RenderSceneTexts();
        void ApplyScaleTransformations();
        void MeasurePerformanceStart();
        void MeasurePerformanceEnd();

    private:
        void MouseClicked();

    private:
        std::vector<std::unique_ptr<FontI>> m_fonts;
        std::vector<std::unique_ptr<SpriteAtlasI>> m_atlas;
        std::vector<std::unique_ptr<SpriteRepresentationI>> m_spriteDraws;

        Uint64 m_performanceStart;
        Uint64 m_performanceEnd;
        Uint64 m_performanceDelta;
        double m_seconds;
        double m_milliseconds;
        double m_previousFps; // only when CALC_FPS set

        int m_fpsCap;
        double m_fpsCapInverse;

        float m_viewportScale; // scaled to fit the window
        Origin m_viewportOffset;

    #if SHOW_FPS
        char m_fpsBuffer[256];
        FontBitmapRepresentation *m_displayFont;
    #endif
    };
}

#endif /* engine_hpp */
