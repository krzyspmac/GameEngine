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

/// Defaults

static SDL_Point flipPoint;
static SDL_FPoint flipPointF;

using namespace engine;

EngineProviderMetal::EngineProviderMetal()
: EngineProviderI()
{
//    flipPoint.x = 0.5;
//    flipPoint.y = 0.5;
//    flipPointF.x = 0.5;
//    flipPointF.y = 0.5;
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
    return 0;
}

Uint64 EngineProviderMetal::GetPerformanceTicks()
{
    return 0;
}

Uint64 EngineProviderMetal::GetPerformanceCounter()
{
    return 0;
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
    return new Texture(nullptr, filename);
}

TextureTargetI *EngineProviderMetal::CreateTargetTexture(int width, int height)
{
    return nullptr;
}

void EngineProviderMetal::UnloadTexture(TextureI *texture)
{
}

std::unique_ptr<DrawableI> EngineProviderMetal::DrawableCreate(SpriteAtlasItemI *atlasItem, float scale)
{
    float width = atlasItem->GetWidth();
    float height = atlasItem->GetHeight();
    DrawableMetal *drawable = new DrawableMetal(width, height);
    return std::unique_ptr<DrawableI>(std::move(drawable));
}

void EngineProviderMetal::DrawableRender(DrawableI *baseDrawable, float x, float y)
{
    auto drawable = static_cast<DrawableMetal*>(baseDrawable);
    auto triangles = drawable->GetVertexData();
    size_t trianglesSize = drawable->GetVertexDataSize();
    size_t trianglesNum = drawable->GetVertexCount();

    m_renderEncoder->setVertexBytes(triangles, trianglesSize, AAPLVertexInputIndexVertices);
    m_renderEncoder->setVertexBytes(&m_viewportSize, sizeof(m_viewportSize), AAPLVertexInputIndexViewportSize);
    m_renderEncoder->setVertexBytes(drawable->GetPosition(), sizeof(simd_float2), AAPLVertexInputIndexViewportOffset);
    m_renderEncoder->setVertexBytes(drawable->GetScale(), sizeof(float), AAPLVertexInputIndexViewportScale);
    m_renderEncoder->setVertexBytes(drawable->GetSize(), sizeof(vector_float2), AAPLVertexInputIndexObjectSize);
    m_renderEncoder->setVertexBytes(&m_desiredViewport, sizeof(vector_float2), AAPLVertexInputIndexViewportTarget);

    m_renderEncoder->drawPrimitives(MTL::PrimitiveTypeTriangleStrip, (NS::UInteger)0, (NS::UInteger)trianglesNum);
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

void EngineProviderMetal::RendererTargetPush(TextureTargetI *targetTexture)
{
}

void EngineProviderMetal::RendererTargetPop()
{
}

void EngineProviderMetal::RenderTargetSet(TextureI *targetTexture)
{

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
