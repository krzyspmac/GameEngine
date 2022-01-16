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
#include "texture_target.hpp"
#include "vector2.hpp"

namespace engine
{

    typedef struct
    {
        SDL_Renderer *renderer;
        SDL_Window *window;
    } SDL_APP;

    class EngineProviderSDL : public EngineProviderI
    {
        Vector2 m_desiredViewport;
    public:
        EngineProviderSDL(engine::SDL_APP *engineHandle);

    public:
        void SetDesiredViewport(int width, int height);

    public:
        Uint64 GetTicks();
        Uint64 GetPerformanceTicks();
        Uint64 GetPerformanceCounter();
        void GetMousePosition(int *x, int *y);
        void Delay(Uint32 ms);
        void GetWindowSize(int *w, int *h);
        void GetRendererOutputSize(int *w, int *h);

    public:
        engine::SDL_APP *GetRendererHandle() { return m_engineHandle; };

    public:
        void SetRenderBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        void ClearRender();
        void RenderPresent();

    public:
        std::unique_ptr<DrawableI> DrawableCreate(SpriteAtlasItemI*, float scale);
        std::unique_ptr<DrawableTargetI> DrawableTargetCreate(float, float);
        void DrawableRender(DrawableI*, float, float);
        void DrawableTargetRender(DrawableTargetI*, float, float);

    public:
        TextureI *LoadTexture(std::string name, FileStreamI *);
        TextureTargetI *CreateTargetTexture(int width, int height);

        void UnloadTexture(TextureI *texture);
        void DrawTexture(TextureI *texture, int x, int y);
        void DrawTexture(TextureI *texture, int x, int y, int srcX, int srcY, int srcW, int srcH, float scale);
        void DrawTexture(TextureI *texture, Anchor_Point anchorPoint, int x, int y, float scale, bool flipHorizontal);
        void DrawTexture(TextureI *texture, Anchor_Point anchorPoint, Vector2& position, float scale, bool flipHorizontal);

        void TextureAlphaSetMod(TextureI *texture, uint8_t alpha);

    public:
        void RenderTargetSet(TextureI *targetTexture);
        void RenderTargetClear();
        void RenderClear();

        void RendererTargetDrawablePush(DrawableTargetI *);
        void RendererTargetDrawablePop();
        void RendererTargetDrawableSet(DrawableTargetI *);


        void RenderSetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        void RenderSetScale(float scaleX, float scaleY);
        void RenderDrawRect(Engine_Rect*);
        void RenderFillRect(Engine_Rect*);
        void RenderDrawLine(int x1, int y1, int x2, int y2);
        void RenderDrawPoint(int x1, int y1);

    private:
        engine::SDL_APP *m_engineHandle;
        std::vector<DrawableTargetI*> m_rendererDrawableStack;
    };

};

#endif /* engine_provider_hpp */
