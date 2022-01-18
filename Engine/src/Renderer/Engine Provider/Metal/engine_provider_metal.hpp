//
//  engine_provider_metal.hpp
//  Engine
//
//  Created by krzysp on 11/01/2022.
//

#ifndef engine_provider_metal_hpp
#define engine_provider_metal_hpp

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include <Metal/Metal.hpp>
#include "AAPLShaderTypes.h"

#include "common.h"
#include "common_engine_impl.h"
#include "engine_provider_interface.h"
#include "texture_interface.h"
#include "font_interface.h"
#include "texture_target.hpp"
#include "vector2.hpp"

namespace engine
{

    struct EngineProviderMetalTargetDrawableDescriptor
    {

    };

    class EngineProviderMetal : public EngineProviderI
    {
        MTL::Device *m_device;
        MTL::CommandBuffer *m_commandBuffer;
        MTL::RenderCommandEncoder *m_renderEncoder;
        MTL::RenderPipelineState *m_renderPipelineState;
        MTL::RenderPassDescriptor *m_rederPassDescriptor;
        MTL::Library *m_library;
        MTL::PixelFormat m_pixelFormat;
        vector_float2 m_viewportSize;
        vector_float2 m_desiredViewport;
        
    public:
        EngineProviderMetal();

    public:
        void SetRendererDevice(MTL::Device*);
        void SetCommandBuffer(MTL::CommandBuffer*);
        void SetRenderPassDescriptor(MTL::RenderPassDescriptor*);
        void SetPixelFormat(MTL::PixelFormat);
        void SetRenderingPipelineState(MTL::RenderPipelineState*);
        void SetRendererCommandEncoder(MTL::RenderCommandEncoder*);
        void SetViewportSize(vector_float2);

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
        std::unique_ptr<DrawableSpriteI> DrawableCreate(SpriteAtlasItemI*, float scale);
        std::unique_ptr<DrawableTargetI> DrawableTargetCreate(float, float);
        void DrawableRender(DrawableI*, float, float);
        void DrawableTargetRender(DrawableTargetI*, float, float);

    public:
        void SetRenderBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        void ClearRender();
        void RenderPresent();

    public:
        TextureI *LoadTexture(std::string name, FileStreamI *);
        TextureTargetI *CreateTargetTexture(int width, int height);
        void UnloadTexture(TextureI *texture);
    public:
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
        DrawableTargetI *m_rendererDrawableTop;
        std::vector<DrawableTargetI*> m_rendererDrawableStack;

        MTL::RenderCommandEncoder *GetTopEncoder();
    };
};

#endif /* engine_provider_metal_hpp */
