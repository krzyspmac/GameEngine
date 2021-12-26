//
//  engine.hpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#ifndef engine_hpp
#define engine_hpp

#import "defs.h"
#import "common.h"
#import "engine_interface.h"
#import "engine_provider_interface.h"
#import "file_access_provider.h"
#import "scripting_engine_provider_interface.h"
#import "character_renderer_interface.h"
#import "character_interface.h"
#import "texture_target.hpp"
#import "character_mover_interface.h"

namespace engine
{
    class Engine: public EngineI
    {
    public:
        ///
        Engine(EngineProviderI &engine, FileAccessI &fileAccess, ScriptingEngineI &scriptingEngine, EventProviderI &eventProvider, Size viewportSize);
        ~Engine();

    public:
        void setup();
        int doInput();
        void update();

    public:
        void SetCapRate(int fps);

    public:
        TextureI *LoadTexture(std::string name);
        TextureTargetI *CreateTargetTexture(int width, int height);
        TextureI *GetTexture(std::string name);
        void UnloadTexture(TextureI *texture);
        void DisposeAllTextures();

        FontI *LoadFont(std::string name);
        FontI *GetFont(std::string name);
        void DisposeAllFonts();

        SpriteAtlasI *SpriteAtlasLoad(std::string jsonFilename, std::string textureFilename);
        SpriteAtlasI *SpriteAtlasGet(std::string jsonFilename);
        void SpriteAtlasUnload(SpriteAtlasI *atlas);
        void SpriteAtlasDisposeAll();

        SpriteDrawI *SpriteDrawLoadStatic(SpriteAtlasItemI *sprite, int scale);
        SpriteDrawI *SpriteDrawLoadAnimated(std::vector<SpriteAtlasItemI*> sprites, int frameAnimationDurationMs, int scale);
        void SpriteDrawUnload(SpriteDrawI *spriteDraw);
        void SpriteDrawDisposeAll();

    private:
        void RenderScene();
        void RenderSceneTexts();
        void ApplyScaleTransformations();
        void MeasurePerformanceStart();
        void MeasurePerformanceEnd();

    private:
        void MouseClicked();

    private:
        std::vector<std::unique_ptr<TextureI>> m_textures;
        std::vector<std::unique_ptr<FontI>> m_fonts;
        std::vector<std::unique_ptr<SpriteAtlasI>> m_atlas;
        std::vector<std::unique_ptr<SpriteDrawI>> m_spriteDraws;

        Uint64 m_performanceStart;
        Uint64 m_performanceEnd;
        Uint64 m_performanceDelta;
        float m_seconds;
        float m_milliseconds;
        float m_previousFps; // only when CALC_FPS set

        int m_fpsCap;
        float m_fpsCapInverse;

        TextureTargetI *m_bufferTexture;
        float m_viewportScale; // scaled to fit the window
        Origin m_viewportOffset;

    #if SHOW_FPS
        char m_fpsBuffer[256];
        FontI *m_fpsFont;
    #endif
        CharacterI *m_character;
        CharacterMoverI *m_characterMover;
    };
}

#endif /* engine_hpp */
