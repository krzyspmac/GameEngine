//
//  drawable_metal.cpp
//  Engine
//
//  Created by krzysp on 12/01/2022.
//

#include "drawable_metal.hpp"

using namespace engine;

DrawableMetal::DrawableMetal(SpriteAtlasItemI *atlasItem, float width, float height)
    : DrawableI(atlasItem->GetWidth(), atlasItem->GetHeight())
    , m_scale(1.0)
    , m_atlasItem(atlasItem)
{
    m_triangleVertices = (AAPLVertex*)malloc(6 * sizeof(AAPLVertex));

    auto metalTextrue = (TextureMetal*)atlasItem->GetTexture();
    auto textureSize = metalTextrue->GetSize();
    
    float x = atlasItem->GetX() / textureSize.x;
    float y = atlasItem->GetY() / textureSize.y;
    float w = (atlasItem->GetX() +atlasItem->GetWidth()) / textureSize.x;
    float h = (atlasItem->GetY() + atlasItem->GetHeight()) / textureSize.y;
    
    m_texture = metalTextrue;

    float width2 = width/2;
    float height2 = height/2;
    
    // Set up a simple MTLBuffer with vertices which include texture coordinates
    static const AAPLVertex data[] =
    {
        // Pixel positions, Texture coordinates
        { { -width2,  -height2 },   { x, h} },
        { { -width2,   height2 },   { x, y } },
        { {  width2,   height2 },   { w, y } },

        { {  width2,    height2 },  { w, y } },
        { {  width2,   -height2 },  { w, h } },
        { { -width2,   -height2 },  { x, h } },
    };
    
    m_triangleVerticiesDataSize = sizeof(data);
    memcpy(m_triangleVertices, data, m_triangleVerticiesDataSize);
}

void DrawableMetal::SetScale(float scale)
{
    m_scale = scale;
}

vector_float2 *DrawableMetal::GetSize()
{
    return &m_size;
}

float *DrawableMetal::GetScale()
{
    return &m_scale;
}

AAPLVertex *DrawableMetal::GetVertexData()
{
    return m_triangleVertices;
}

size_t DrawableMetal::GetVertexDataSize()
{
    return m_triangleVerticiesDataSize;
}

size_t DrawableMetal::GetVertexCount()
{
    return 6;
}
