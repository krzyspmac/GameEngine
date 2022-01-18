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
    // Only process if the texture exists
    auto metalTextrue = (TextureMetal*)atlasItem->GetTexture();
    if (metalTextrue->GetMTLTextureHandle() == nullptr)
    {
        m_vertexCount = 0;
        return;
    };

    // Get texture options
    auto textureSize = metalTextrue->GetSize();
    auto isFlippedVertically = atlasItem->GetFlippedVertically();
    RectF textureCoodinagtes = atlasItem->GetTextureCoordinates();

    // If the atlas was marked as using a flipped texture, flip the original texture coordinates
    if (isFlippedVertically)
    {
        textureCoodinagtes.origin.y = textureSize.y - textureCoodinagtes.size.height - textureCoodinagtes.origin.y;
    }

    // Calculate texture cordinages in 0-1 system
    float x0 = textureCoodinagtes.origin.x / textureSize.x;
    float y0 = textureCoodinagtes.origin.y / textureSize.y;
    float x1 = (textureCoodinagtes.origin.x + textureCoodinagtes.size.width) / textureSize.x;
    float y1 = (textureCoodinagtes.origin.y + textureCoodinagtes.size.height) / textureSize.y;

    // If the atlas was marked as using a flipped texture, act accordingly
    if (isFlippedVertically)
    {
        float tmpY = y0;
        y0 = y1;
        y1 = tmpY;
    }

    // Prepare the verticies for this item
    float width = textureCoodinagtes.size.width;
    float height = textureCoodinagtes.size.height;
    float width2 = width/2;
    float height2 = height/2;

    AAPLVertex data[] =
    {
        // Pixel positions, Texture coordinates
        { { -width2,  -height2 },   { x0, y1 } },
        { { -width2,   height2 },   { x0, y0 } },
        { {  width2,   height2 },   { x1, y0 } },

        { {  width2,    height2 },  { x1, y0 } },
        { {  width2,   -height2 },  { x1, y1 } },
        { { -width2,   -height2 },  { x0, y1 } },
    };

    // Allocate a buffer for metal with sufficient size. Set mode to shared.
    m_vertexBuffer = device->newBuffer(sizeof(data), MTL::ResourceStorageModeShared);

    // Copy data over to the buffer.
    memcpy(m_vertexBuffer->contents(), data, sizeof(data));

    // Store the number of vertices of the primitive.
    m_vertexCount = 6;

    // Store the texture.
    m_texture = metalTextrue;
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
