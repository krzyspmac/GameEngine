//
//  engine.hpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#ifndef engine_hpp
#define engine_hpp

#include "defs.h"
#include "common.h"
#include "engine_interface.h"
#include "engine_provider_interface.h"
#include "file_access_provider.h"
#include "scripting_engine_provider_interface.h"
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
               ScriptingEngineI &scriptingEngine,
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
        void Setup();
        void FrameBegin();
        int doInput();
        void FrameDraw();

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
        std::vector<std::unique_ptr<SpriteDrawI>> m_spriteDraws;

        Uint64 m_performanceStart;
        Uint64 m_performanceEnd;
        Uint64 m_performanceDelta;
        double m_seconds;
        double m_milliseconds;
        double m_previousFps; // only when CALC_FPS set

        int m_fpsCap;
        double m_fpsCapInverse;

        //TextureTargetI *m_bufferTexture;
        std::unique_ptr<DrawableTargetI> m_bufferDrawable;
        float m_viewportScale; // scaled to fit the window
        Origin m_viewportOffset;

    #if SHOW_FPS
        char m_fpsBuffer[256];
        FontBitmapRepresentation *m_displayFont;
    #endif
    };
}

#endif /* engine_hpp */
