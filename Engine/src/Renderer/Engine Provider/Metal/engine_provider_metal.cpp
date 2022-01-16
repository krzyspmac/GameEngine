//
//  engine_provider_metal.cpp
//  Engine
//
//  Created by krzysp on 11/01/2022.
//

#include "engine_provider_metal.hpp"

//
//#define NS_PRIVATE_IMPLEMENTATION
//#define CA_PRIVATE_IMPLEMENTATION
//#define MTL_PRIVATE_IMPLEMENTATION
#include <Metal/Metal.hpp>

#include "drawable_metal.hpp"
#include "texture.hpp"
#include "texture_target_metal.hpp"
#include "texture_metal.hpp"

//static NSDate

#include <chrono>
#include <iostream>
#include <chrono>
#include <ratio>
#include <thread>

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

void EngineProviderMetal::SetPixelFormat(MTL::PixelFormat val)
{
    m_pixelFormat = val;
}

void EngineProviderMetal::SetDesiredViewport(int width, int height)
{
    m_desiredViewport[0] = width;
    m_desiredViewport[1] = height;
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

void EngineProviderMetal::GetMousePosition(int *x, int *y)
{
    return;
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
    DrawableMetal *drawable = new DrawableMetal(atlasItem);
    return std::unique_ptr<DrawableSpriteI>(std::move(drawable));
}

std::unique_ptr<DrawableTargetI> EngineProviderMetal::DrawableTargetCreate(float, float)
{
    return nullptr;
}

void EngineProviderMetal::DrawableRender(DrawableI *baseDrawable, float x, float y)
{
    auto drawable = static_cast<DrawableMetal*>(baseDrawable);
    if (!drawable->CanDraw()) { return; };

    auto triangles = drawable->GetVertexData();
    size_t trianglesSize = drawable->GetVertexDataSize();
    size_t trianglesNum = drawable->GetVertexCount();
    simd_float2 pos = {x, y};

    m_renderEncoder->setVertexBytes(triangles, trianglesSize, AAPLVertexInputIndexVertices);
    m_renderEncoder->setVertexBytes(&m_viewportSize, sizeof(m_viewportSize), AAPLVertexInputIndexViewportSize);
    m_renderEncoder->setVertexBytes(&pos, sizeof(simd_float2), AAPLVertexInputIndexViewportOffset);
    m_renderEncoder->setVertexBytes(drawable->GetScale(), sizeof(float), AAPLVertexInputIndexViewportScale);
    m_renderEncoder->setVertexBytes(drawable->GetSize(), sizeof(vector_float2), AAPLVertexInputIndexObjectSize);
    m_renderEncoder->setVertexBytes(&m_desiredViewport, sizeof(vector_float2), AAPLVertexInputIndexViewportTarget);
    
    auto texture = drawable->GetTexture();
    if (texture != nullptr)
    {
        auto mtlTextureHandle = texture->GetMTLTextureHandle();
        if (mtlTextureHandle != nullptr)
        {
            m_renderEncoder->setFragmentTexture(mtlTextureHandle, AAPLTextureIndexBaseColor);
        }
    }

    m_renderEncoder->setFragmentBytes(drawable->GetAlpha(), sizeof(float), AAPLTextureIndexBaseAlpha);
    
    m_renderEncoder->drawPrimitives(MTL::PrimitiveTypeTriangleStrip, (NS::UInteger)0, (NS::UInteger)trianglesNum);
}

void EngineProviderMetal::DrawableTargetRender(DrawableTargetI*, float, float)
{

}

void EngineProviderMetal::DrawTexture(TextureI *texture, int x, int y)
{
////    /*static const*/ AAPLVertex triangleVertices[] =
////    {
////        // 2D positions,    RGBA colors
////        { {  250,  -250 }, { 1, 0, 0, 1 } },
////        { { -250,  -250 }, { 0, 1, 0, 1 } },
////        { {    0,   250 }, { 0, 0, 1, 1 } },
////    };
//
////    const vector_float2 p1[] = { 250, -250 };
//    float textureWidth = 200;
//    float viewportWidth = m_viewportSize.x;
//
//    /*static const*/ AAPLVertex triangleVertices[3] =
//    {
//        // 2D positions,    RGBA colors
//        { {  250,  -250 }, { 1, 0, 0, 1 } },
//        { { -250,  -250 }, { 0, 1, 0, 1 } },
//        { {    0,   250 }, { 0, 0, 1, 1 } },
//    };
//
////    AAPLVertexShift(triangleVertices, 3, -(float)m_viewportSize.x/2 + 250, -(float)m_viewportSize.y/2 + 250);
//
//    m_renderEncoder->setVertexBytes(triangleVertices, sizeof(triangleVertices), AAPLVertexInputIndexVertices);
//    m_renderEncoder->setVertexBytes(&m_viewportSize, sizeof(m_viewportSize), AAPLVertexInputIndexViewportSize);
//    m_renderEncoder->drawPrimitives(MTL::PrimitiveTypeTriangle, (NS::UInteger)0, (NS::UInteger)3);
    
}

void EngineProviderMetal::DrawTexture(TextureI *texture, int x, int y, int srcX, int srcY, int srcW, int srcH, float scale)
{
}

void EngineProviderMetal::DrawTexture(TextureI *texture, Anchor_Point anchorPoint, int x, int y, float scale, bool flipHorizontal)
{
}

void EngineProviderMetal::DrawTexture(TextureI *texture, Anchor_Point anchorPoint, Vector2& position, float scale, bool flipHorizontal)
{
}

void EngineProviderMetal::TextureAlphaSetMod(TextureI *texture, uint8_t alpha)
{
}

//void EngineProviderMetal::RendererTargetPush(TextureTargetI *targetTexture)
//{
//    TextureTargetMetal *metalTexture = (TextureTargetMetal*)targetTexture;
//
//    EngineProviderMetalTargetTextureDescriptor *targetRender = new EngineProviderMetalTargetTextureDescriptor();
//
//    targetRender->m_renderToTexturePassDescriptor = MTL::RenderPassDescriptor::alloc()->init();
//
//    targetRender->m_renderToTexturePassDescriptor->colorAttachments()->object(0)->setTexture(metalTexture->GetTexture());
//    targetRender->m_renderToTexturePassDescriptor->colorAttachments()->object(0)->setLoadAction(MTL::LoadActionClear);
//    targetRender->m_renderToTexturePassDescriptor->colorAttachments()->object(0)->setClearColor({1, 1, 1, 1 });
//    targetRender->m_renderToTexturePassDescriptor->colorAttachments()->object(0)->setStoreAction(MTL::StoreActionStore);
//
//    targetRender->m_renderToTexturePipeline = MTL::RenderPipelineDescriptor::alloc()->init();
//    targetRender->m_renderToTexturePipeline->setLabel(NS::MakeConstantString("Offscreen Render Pipe"));
//    targetRender->m_renderToTexturePipeline->setSampleCount(1);
//    targetRender->m_renderToTexturePipeline->setVertexFunction(m_library->newFunction(NS::MakeConstantString("simpleVertexShader")));
//    targetRender->m_renderToTexturePipeline->setFragmentFunction(m_library->newFunction(NS::MakeConstantString("simpleFragmentShader")));
//    targetRender->m_renderToTexturePipeline->colorAttachments()->object(0)->setPixelFormat(m_pixelFormat);
//
//
//
//    renderStack.emplace_back(targetRender);
//}

//void EngineProviderMetal::RendererTargetPop()
//{
//    if (!renderStack.empty()) {
//        auto item = renderStack.at(renderStack.size()-1);
//        delete item;
//        renderStack.pop_back();
//    }
//}

//void EngineProviderMetal::RenderTargetSet(TextureI *targetTexture)
//{
//
//}

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
}

void EngineProviderMetal::RendererTargetDrawablePop()
{
    m_rendererDrawableStack.pop_back();
}

void EngineProviderMetal::RendererTargetDrawableSet(DrawableTargetI *)
{

}
