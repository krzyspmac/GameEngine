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

void EngineProviderMetal::SetRendererCommandEncoder(MTL::RenderCommandEncoder *renderEncoder)
{
    m_renderEncoder = renderEncoder;
}

void EngineProviderMetal::SetViewportSize(vector_uint2 size)
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
    return nullptr;
}

TextureTargetI *EngineProviderMetal::CreateTargetTexture(int width, int height)
{
    return nullptr;
}

void EngineProviderMetal::UnloadTexture(TextureI *texture)
{
}

void EngineProviderMetal::DrawTexture(TextureI *texture, int x, int y)
{
    static const AAPLVertex triangleVertices[] =
    {
        // 2D positions,    RGBA colors
        { {  250,  -250 }, { 1, 0, 0, 1 } },
        { { -250,  -250 }, { 0, 1, 0, 1 } },
        { {    0,   250 }, { 0, 0, 1, 1 } },
    };

    m_renderEncoder->setVertexBytes(triangleVertices, sizeof(triangleVertices), AAPLVertexInputIndexVertices);
    m_renderEncoder->setVertexBytes(&m_viewportSize, sizeof(m_viewportSize), AAPLVertexInputIndexViewportSize);
    m_renderEncoder->drawPrimitives(MTL::PrimitiveTypeTriangle, (NS::UInteger)0, (NS::UInteger)3);
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
