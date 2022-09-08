//
//  drawable_metal.cpp
//  Engine
//
//  Created by krzysp on 12/01/2022.
//

#include "drawable_metal.hpp"
#include "engine_metal_buffer_manager.hpp"

using namespace engine;

DrawableMetal::DrawableMetal(MTL::Device *device, SpriteAtlasItemI *atlasItem)
    : DrawableSpriteI(atlasItem)
    , m_vertexBuffer(nullptr)
    , m_vertexBufferOffset(0)
{
    // Only process if the texture exists
    auto metalTextrue = (TextureMetal*)atlasItem->GetTexture();
    if (metalTextrue->GetMTLTextureHandle() == nullptr)
    {
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
    float width = ceil(textureCoodinagtes.size.width);
    float height = ceil(textureCoodinagtes.size.height);
    float width2 = ceil(width/2);
    float height2 = ceil(height/2);
    
    // Standard, default z-axis vertex position. In metal 0 if closer to the screen, 1 is farther.
    // By default we put our sprites at the end. Setting DrawableI::SetZPosition(0) brings the
    // sprite to the front.
    static float zStdPos = 0.0f;

    AAPLVertex data[] =
    {
        // Pixel positions, Texture coordinates, normals
        { { -width2,  -height2, zStdPos },   { x0, y1 } },
        { { -width2,   height2, zStdPos },   { x0, y0 } },
        { {  width2,   height2, zStdPos },   { x1, y0 } },

        { {  width2,    height2, zStdPos },  { x1, y0 } },
        { {  width2,   -height2, zStdPos },  { x1, y1 } },
        { { -width2,   -height2, zStdPos },  { x0, y1 } },
    };

    m_dataSize = sizeof(data);
    
    // Allocate a buffer for metal with sufficient size. Set mode to shared.
    MetalBufferManager::Shared()->RegisterData(device, data, m_dataSize, [&](MTL::Buffer *buffer, size_t offset){
        m_vertexBuffer = buffer;
        m_vertexBufferOffset = offset;
    });

    // Store the number of vertices of the primitive.
    m_vertexCount = 6;

    // Store the texture.
    m_texture = metalTextrue;

    // Store the size of the object
    m_size.x = (float)atlasItem->GetWidth();
    m_size.y = (float)atlasItem->GetHeight();

    // Color mod
    m_colorMod = {1.f, 1.f, 1.f};

    // Rotation
    m_rotation[0] = 0.0f;
    m_rotation[1] = 0.0f;
    m_rotation[2] = 0.0f;
}

DrawableMetal::~DrawableMetal()
{
}

bool DrawableMetal::CanDraw()
{
    return m_vertexBuffer != nullptr && m_alpha > 0;
}

vector_float2 *DrawableMetal::GetSize()
{
    return &m_size;
}

void DrawableMetal::SetRotation(float angle, float v1x, float v1y)
{
    m_rotation[0] = angle;
    m_rotation[1] = v1x;
    m_rotation[2] = v1y;
}

void DrawableMetal::GetRotation(float *outAngle, float *outV1x, float *outV1y)
{
    *outAngle = m_rotation[0];
    *outV1x = m_rotation[1];
    *outV1y = m_rotation[2];
}

void DrawableMetal::SetZPosition(float value)
{
    DrawableSpriteI::SetZPosition(value);

    size_t offset = m_dataSize / m_vertexCount;
    size_t i;
    char * ptr = (char*)m_vertexBuffer->contents() + m_vertexBufferOffset;
    for (i = 0; i < m_vertexCount; i++)
    {
        AAPLVertex *vertex = (AAPLVertex*)((char*)ptr + (i*offset));
        vertex->position[2] = value;
    }
}

MTL::Buffer *DrawableMetal::GetVertexBuffer()
{
    return m_vertexBuffer;
}

size_t DrawableMetal::GetVertexBufferOffset()
{
    return m_vertexBufferOffset;
}

size_t DrawableMetal::GetVertexCount()
{
    return m_vertexCount;
}

vector_float3 *DrawableMetal::GetColorModMetal()
{
    return &m_colorMod;
}

void DrawableMetal::SetColorMod(Color3 mod)
{
    m_colorMod = {mod.r, mod.g, mod.b};
}

/////

DrawableTargetMetal::DrawableTargetMetal(MTL::Device* device, MTL::CommandBuffer *commandBuffer, TextureTargetMetal *texture)
    : DrawableTargetI(texture->GetSize().x, texture->GetSize().y)
    , m_texture(texture)
{
    m_renderPassDescriptor = MTL::RenderPassDescriptor::alloc()->init();
    auto colorAtt = m_renderPassDescriptor->colorAttachments()->object(0);
    colorAtt->setTexture(texture->GetMTLTextureHandle());
    colorAtt->setLoadAction(MTL::LoadActionClear);
    colorAtt->setClearColor(MTL::ClearColor(1, 1, 1, 1));
    colorAtt->setStoreAction(MTL::StoreActionStore);

    m_library = device->newDefaultLibrary();
    m_vertexFunction = m_library->newFunction(NS::MakeConstantString("simpleVertexShader"));
    m_fragmentFunction = m_library->newFunction(NS::MakeConstantString("simpleFragmentShader"));

    m_renderPipelineDescriptor = MTL::RenderPipelineDescriptor::alloc()->init();
    m_renderPipelineDescriptor->setLabel(NS::MakeConstantString("Texture Target Pipeline"));
    m_renderPipelineDescriptor->setSampleCount(1);
    m_renderPipelineDescriptor->setVertexFunction(m_vertexFunction);
    m_renderPipelineDescriptor->setFragmentFunction(m_fragmentFunction);
    m_renderPipelineDescriptor->colorAttachments()->object(0)->setPixelFormat(texture->GetMTLTextureHandle()->pixelFormat());

    NS::Error *error;
    m_rendererPipelineState = device->newRenderPipelineState(m_renderPipelineDescriptor, &error);

//    id<MTLRenderCommandEncoder> renderEncoder =
//        [commandBuffer renderCommandEncoderWithDescriptor:_renderToTextureRenderPassDescriptor];


    m_renderPassDescriptor->retain();


    // Calculate texture cordinages in 0-1 system
    float x0 = 0;
    float y0 = 0;
    float x1 = 1.0;
    float y1 = 1.0f;

    // Prepare the verticies for this item
    float width = texture->GetSize().x;
    float height = texture->GetSize().y;
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
    m_texture = texture;
}

void DrawableTargetMetal::UpdateCommandEncoder(MTL::CommandBuffer *commandBuffer)
{
//    m_encoder->release();
//
//    m_encoder = commandBuffer->renderCommandEncoder(m_renderPassDescriptor);
//    m_encoder->setLabel(NS::MakeConstantString("Offscreen rendering pass"));
//    m_encoder->setRenderPipelineState(m_rendererPipelineState);
}

void DrawableTargetMetal::CreatePipeline()
{

}

bool DrawableTargetMetal::CanDraw()
{
    return m_vertexBuffer != nullptr;
}


vector_float2 *DrawableTargetMetal::GetSize()
{
    return &m_size;
}

MTL::Buffer *DrawableTargetMetal::GetVertexBuffer()
{
    return m_vertexBuffer;
}

size_t DrawableTargetMetal::GetVertexCount()
{
    return m_vertexCount;
}

DrawableTargetMetal::~DrawableTargetMetal()
{
    m_renderPipelineDescriptor->release();
    m_vertexFunction->release();
    m_fragmentFunction->release();
    m_library->release();
    m_renderPassDescriptor->release();
    m_rendererPipelineState->release();
    m_encoder->release();
}
