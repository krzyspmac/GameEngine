//
//  drawable_metal.cpp
//  Engine
//
//  Created by krzysp on 12/01/2022.
//

#include "drawable_metal.hpp"

using namespace engine;

DrawableMetal::DrawableMetal(MTL::Device *device, SpriteAtlasItemI *atlasItem)
    : DrawableSpriteI(atlasItem)
    , m_vertexBuffer(nullptr)
{
    auto metalTextrue = (TextureMetal*)atlasItem->GetTexture();
    if (metalTextrue->GetMTLTextureHandle() == nullptr)
    {
        m_vertexCount = 0;
        return;
    };

    m_vertexCount = 6;

    auto textureSize = metalTextrue->GetSize();
    
    float x = atlasItem->GetX() / textureSize.x;
    float y = atlasItem->GetY() / textureSize.y;
    float w = (atlasItem->GetX() +atlasItem->GetWidth()) / textureSize.x;
    float h = (atlasItem->GetY() + atlasItem->GetHeight()) / textureSize.y;
    
    m_texture = metalTextrue;

    float width = atlasItem->GetWidth();
    float height = atlasItem->GetHeight();
    float width2 = width/2;
    float height2 = height/2;

    AAPLVertex data[] =
    {
        // Pixel positions, Texture coordinates
        { { -width2,  -height2 },   { x, h } },
        { { -width2,   height2 },   { x, y } },
        { {  width2,   height2 },   { w, y } },

        { {  width2,    height2 },  { w, y } },
        { {  width2,   -height2 },  { w, h } },
        { { -width2,   -height2 },  { x, h } },
    };

    m_vertexBuffer = device->newBuffer(sizeof(data), MTL::ResourceStorageModeShared);
    memcpy(m_vertexBuffer->contents(), data, sizeof(data));
}

DrawableMetal::~DrawableMetal()
{
    m_vertexBuffer->release();
}

bool DrawableMetal::CanDraw()
{
    return m_vertexCount > 0;
}

vector_float2 *DrawableMetal::GetSize()
{
    return &m_size;
}

MTL::Buffer *DrawableMetal::GetVertexBuffer()
{
    return m_vertexBuffer;
}

size_t DrawableMetal::GetVertexCount()
{
    return m_vertexCount;
}
