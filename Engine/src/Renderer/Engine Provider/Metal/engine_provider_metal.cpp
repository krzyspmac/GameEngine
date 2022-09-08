//
//  engine_provider_metal.cpp
//  Engine
//
//  Created by krzysp on 11/01/2022.
//

#include "engine_provider_metal.hpp"

#include "AAPLShaderTypes.h"

#include "drawable_metal.hpp"
#include "texture.hpp"
#include "texture_target_metal.hpp"
#include "texture_metal.hpp"
#include <chrono>
#include <iostream>
#include <chrono>
#include <ratio>
#include <thread>

#include "sprite_representation_static.hpp"
#include "scene_manager.hpp"
#include "engine.hpp"

using namespace engine;
using namespace std::chrono;

static auto timeEngineStart = std::chrono::high_resolution_clock::now();

class EngineProviderMetalTargetTextureDescriptor
{
public:
    MTL::RenderPassDescriptor *m_renderToTexturePassDescriptor;
    MTL::RenderPipelineDescriptor *m_renderToTexturePipeline;
};

std::vector<EngineProviderMetalTargetTextureDescriptor*> renderStack;

EngineProviderMetal::EngineProviderMetal()
: EngineProviderI()
{
}

void EngineProviderMetal::SetRendererDevice(MTL::Device *device)
{
    m_device = device;
    m_library = device->newDefaultLibrary();
}

MTL::Device* EngineProviderMetal::GetRendererDevice()
{
    return m_device;
}

void EngineProviderMetal::SetCommandBuffer(MTL::CommandBuffer *val)
{
    m_commandBuffer = val;

    for (DrawableTargetI *baseDrawable : m_rendererDrawableStack)
    {
        DrawableTargetMetal *drawable = static_cast<DrawableTargetMetal*>(baseDrawable);
        drawable->UpdateCommandEncoder(val);
    }
}

void EngineProviderMetal::SetRenderPassDescriptor(MTL::RenderPassDescriptor* val)
{
    m_rederPassDescriptor = val;
}

void EngineProviderMetal::SetPixelFormat(MTL::PixelFormat val)
{
    m_pixelFormat = val;
}

void EngineProviderMetal::SetDesiredViewport(int width, int height)
{
    m_desiredViewport[0] = width;
    m_desiredViewport[1] = height;
}

engine::Size EngineProviderMetal::GetDesiredViewport()
{
    return { static_cast<int>(m_desiredViewport.x), static_cast<int>(m_desiredViewport.y) };
}

void EngineProviderMetal::SetViewportScale(float val)
{
    m_viewportScale = val;
}

void EngineProviderMetal::SetRenderingPipelineState(MTL::RenderPipelineState *val)
{
    m_renderPipelineState = val;
}

void EngineProviderMetal::SetRendererCommandEncoder(MTL::RenderCommandEncoder *renderEncoder)
{
    m_renderEncoder = renderEncoder;
}

void EngineProviderMetal::SetViewportSize(vector_float2 size)
{
    m_viewportSize = size;
}

Uint64 EngineProviderMetal::GetTicks()
{
    auto now = std::chrono::high_resolution_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now - timeEngineStart);
    return milliseconds.count();
}

Uint64 EngineProviderMetal::GetPerformanceTicks()
{
    return GetTicks();
}

Uint64 EngineProviderMetal::GetPerformanceCounter()
{
    return GetTicks();
}

void EngineProviderMetal::Delay(Uint32 ms)
{

}

void EngineProviderMetal::GetWindowSize(int *w, int *h)
{
    *w = m_viewportSize.x;
    *h = m_viewportSize.y;
}

void EngineProviderMetal::GetRendererOutputSize(int *w, int *h)
{
}

void EngineProviderMetal::SetRenderBackgroundColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{

}

void EngineProviderMetal::ClearRender()
{

}

void EngineProviderMetal::RenderPresent()
{

}

TextureI *EngineProviderMetal::LoadTexture(std::string filename, FileStreamI *stream)
{
    return new TextureMetal(m_device, filename);
}

TextureTargetI *EngineProviderMetal::CreateTargetTexture(int width, int height)
{
    TextureTargetMetal *texture = new TextureTargetMetal(m_device, width, height);
    return texture;
}

void EngineProviderMetal::UnloadTexture(TextureI *texture)
{
}

std::unique_ptr<DrawableSpriteI> EngineProviderMetal::DrawableCreate(SpriteAtlasItemI *atlasItem, float scale)
{
    DrawableMetal *drawable = new DrawableMetal(m_device, atlasItem);
    return std::unique_ptr<DrawableSpriteI>(std::move(drawable));
}

std::unique_ptr<DrawableTargetI> EngineProviderMetal::DrawableTargetCreate(float width, float height)
{
    TextureTargetMetal *texture = (TextureTargetMetal*)CreateTargetTexture(width, height);
    DrawableTargetMetal *drawable = new DrawableTargetMetal(m_device, m_commandBuffer, texture);
    return std::unique_ptr<DrawableTargetI>(std::move(drawable));
}

void EngineProviderMetal::DrawableRender(DrawableI *baseDrawable, SpriteRepresentationI *spr, float x, float y)
{
    DrawableRender(baseDrawable, spr, x, y, baseDrawable->GetColorMod());
}

void EngineProviderMetal::DrawableRender(DrawableI *baseDrawable, SpriteRepresentationI *spr, float x, float y, Color4 colorMod)
{
    // Cast interface to concrete instance and check if we can draw
    auto drawable = static_cast<DrawableMetal*>(baseDrawable);
    if (!drawable->CanDraw())
    { return;
    };

    // Some static values to pass to the GPU
    static simd_float2 position = { 0, 0 };
    position.x = x;
    position.y = y;

    static vector_float4 gpuColorMod = { 1.f, 1.f, 1.f, 1.f };
    gpuColorMod.r = colorMod.r;
    gpuColorMod.g = colorMod.g;
    gpuColorMod.b = colorMod.b;
    gpuColorMod.a = colorMod.a;

    auto &rotation = drawable->GetRotationLowLevel();
    auto &rotationMatrix = drawable->GetRotationMatrix();

    // Pass data to the GPU. Render on screen or on offline-buffer specified
    // when using RendererTargetDrawablePush.
    MTL::RenderCommandEncoder *renderToPipline = m_renderEncoder;

    renderToPipline->setVertexBuffer(drawable->GetVertexBuffer(), drawable->GetVertexBufferOffset(), AAPLVertexInputIndexVertices);
    renderToPipline->setVertexBytes(&m_viewportSize, sizeof(m_viewportSize), AAPLVertexInputIndexWindowSize);
    renderToPipline->setVertexBytes(&position, sizeof(simd_float2), AAPLVertexInputIndexObjectOffset);
    renderToPipline->setVertexBytes(&m_viewportScale, sizeof(float), AAPLVertexInputIndexWindowScale);
    renderToPipline->setVertexBytes(drawable->GetScale(), sizeof(float), AAPLVertexInputIndexObjectScale);
    renderToPipline->setVertexBytes(drawable->GetSize(), sizeof(vector_float2), AAPLVertexInputIndexObjectSize);
    renderToPipline->setVertexBytes(&m_desiredViewport, sizeof(vector_float2), AAPLVertexInputIndexViewportSize);
    renderToPipline->setVertexBytes(&rotation, sizeof(rotation), AAPLVertexInputIndexRot);
    renderToPipline->setVertexBytes(&rotationMatrix, sizeof(rotationMatrix), AAPLVertexInputIndexRotationMatrix);

    renderToPipline->setFragmentBytes(drawable->GetAlpha(), sizeof(float), FragmentShaderIndexBaseAlpha);

    auto& lightManager = ENGINE().getLightMnaager();
    int lightsCount = drawable->GetAcceptsLight() && lightManager.GetLightsActive() ? lightManager.GetLightBufferCount() : 0;
    renderToPipline->setFragmentBytes(&lightsCount, sizeof(int), FragmentShaderIndexLightCount);
    renderToPipline->setFragmentBytes(lightManager.GetLightBuffer(), lightManager.GetLightBufferSize(), FragmentShaderIndexLight);
    renderToPipline->setFragmentBytes(&gpuColorMod, sizeof(vector_float4), FragmentShaderIndexColorMod);

    auto texture = drawable->GetTexture();
    if (texture != nullptr)
    {
        auto mtlTextureHandle = texture->GetMTLTextureHandle();
        if (mtlTextureHandle != nullptr)
        {
            renderToPipline->setFragmentTexture(mtlTextureHandle, FragmentShaderIndexBaseColor);
        }
    }

    renderToPipline->drawPrimitives(MTL::PrimitiveTypeTriangleStrip, (NS::UInteger)0, (NS::UInteger)drawable->GetVertexCount());
}

void EngineProviderMetal::DrawableTargetRender(DrawableTargetI *baseDrawable, float x, float y)
{
    // TODO: not implemented
    return;
//    // Cast interface to concrete instance and check if we can draw
//    auto drawable = static_cast<DrawableTargetMetal*>(baseDrawable);
//    if (!drawable->CanDraw()) { return; };
//
//    // Some values to pass to the GPU
//    static simd_float2 position = { 0, 0 };
//    position.x = x; position.y = y;
//
//    // Pass data to the GPU. Render on screen or on offline-buffer specified
//    // when using RendererTargetDrawablePush.
//    MTL::RenderPipelineState *renderToPipline = m_renderPipelineState;
//
//    m_renderEncoder->setRenderPipelineState(renderToPipline);
//    m_renderEncoder->setVertexBuffer(drawable->GetVertexBuffer(), 0, AAPLVertexInputIndexVertices);
//    m_renderEncoder->setVertexBytes(&m_viewportSize, sizeof(m_viewportSize), AAPLVertexInputIndexViewportSize);
//    m_renderEncoder->setVertexBytes(&position, sizeof(simd_float2), AAPLVertexInputIndexViewportOffset);
//    m_renderEncoder->setVertexBytes(drawable->GetScale(), sizeof(float), AAPLVertexInputIndexViewportScale);
//    m_renderEncoder->setVertexBytes(drawable->GetSize(), sizeof(vector_float2), AAPLVertexInputIndexObjectSize);
//    m_renderEncoder->setVertexBytes(&m_desiredViewport, sizeof(vector_float2), AAPLVertexInputIndexViewportTarget);
//    m_renderEncoder->setFragmentBytes(drawable->GetAlpha(), sizeof(float), AAPLTextureIndexBaseAlpha);
//
//    auto texture = drawable->GetTexture();
//    if (texture != nullptr)
//    {
//        auto mtlTextureHandle = texture->GetMTLTextureHandle();
//        if (mtlTextureHandle != nullptr)
//        {
//            m_renderEncoder->setFragmentTexture(mtlTextureHandle, AAPLTextureIndexBaseColor);
//        }
//    }
//
//    m_renderEncoder->drawPrimitives(MTL::PrimitiveTypeTriangleStrip, (NS::UInteger)0, (NS::UInteger)drawable->GetVertexCount());
}

MTL::RenderCommandEncoder *EngineProviderMetal::GetTopEncoder()
{
    return m_renderEncoder;
}

void EngineProviderMetal::RenderTargetClear()
{

}

void EngineProviderMetal::RenderClear()
{

}

void EngineProviderMetal::RenderSetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{

}

void EngineProviderMetal::RenderSetScale(float scaleX, float scaleY)
{

}

void EngineProviderMetal::RenderDrawRect(Engine_Rect *rect)
{

}

void EngineProviderMetal::RenderFillRect(Engine_Rect *rect)
{

}

void EngineProviderMetal::RenderDrawLine(int x1, int y1, int x2, int y2)
{

}

void EngineProviderMetal::RenderDrawPoint(int x1, int y1)
{

}

void EngineProviderMetal::RendererTargetDrawablePush(DrawableTargetI *drawable)
{
    m_rendererDrawableStack.emplace_back(drawable);
    m_rendererDrawableTop = drawable;
    SetCommandBuffer(m_commandBuffer);
}

void EngineProviderMetal::RendererTargetDrawablePop()
{
    m_rendererDrawableStack.pop_back();
    if (m_rendererDrawableStack.empty())
    {
        m_rendererDrawableTop = nullptr;
    }
    else
    {
        m_rendererDrawableStack.at(m_rendererDrawableStack.size()-1);
    }
}

void EngineProviderMetal::RendererTargetDrawableSet(DrawableTargetI *)
{

}
