// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef drawable_metal_hpp
#define drawable_metal_hpp

#include "drawable_interface.h"
#include "common.h"
#include "interfaces.h"
#include "texture_metal.hpp"
#include "texture_target_metal.hpp"
#include "sprite_atlas_interface.h"
#include "AAPLShaderTypes.h"

namespace engine
{
    /** Defines the metal drawable that goes to the gpu. */
    class DrawableMetal: public DrawableSpriteI
    {
        MTL::Buffer *m_vertexBuffer;
        size_t m_vertexBufferOffset;
        size_t m_dataSize;
        vector_float2 m_size;
        TextureMetal *m_texture;
        size_t m_vertexCount;
        vector_float3 m_colorMod;
        vector_float3 m_rotation;
        simd::float4x4 m_rotationMatrix;
    public:
        DrawableMetal(MTL::Device*, SpriteAtlasItemI*);
    public: // DrawableI
        void SetRotation(float, float, float);
        void GetRotation(float*, float*, float*);
        auto& GetRotationLowLevel() { return m_rotation; };
        void SetRotateable(bool);
    public: // DrawableSpriteI
        /** Construct a drawable for metal given a sprite descriptor */
        void SetZPosition(float value);
        virtual ~DrawableMetal();
        bool CanDraw();
    public: // vertex data
        MTL::Buffer *GetVertexBuffer();
        size_t GetVertexBufferOffset();
        size_t GetVertexCount();

    public: // texture data
        vector_float2 *GetSize();
        TextureMetal *GetTexture() { return m_texture; };
        vector_float3 *GetColorModMetal();
        void SetColorMod(Color3 mod);

    public: // Hardware implementation based
        auto& GetRotationMatrix() { return m_rotationMatrix; };
    };

    /** Defines a concrete metal class for the target drawable that is capable of
        accepting the render pass as its input.
        note: not being used atm
     */
    class DrawableTargetMetal: public DrawableTargetI
    {
        TextureTargetMetal *m_texture;
        MTL::Buffer *m_vertexBuffer;
        size_t m_vertexCount;
        vector_float2 m_size;
        MTL::RenderPassDescriptor *m_renderPassDescriptor;
        MTL::Library *m_library;
        MTL::Function *m_vertexFunction;
        MTL::Function *m_fragmentFunction;
        MTL::RenderPipelineDescriptor *m_renderPipelineDescriptor;
        MTL::RenderPipelineState *m_rendererPipelineState;
        MTL::RenderCommandEncoder *m_encoder;
    public:
        DrawableTargetMetal(MTL::Device*, MTL::CommandBuffer*, TextureTargetMetal*);
        ~DrawableTargetMetal();

    public:
        void SetRotation(float, float, float) { };
        void GetRotation(float*, float*, float*) { };
        void SetRotateable(bool) { };
    public:
        bool CanDraw();
        void UpdateCommandEncoder(MTL::CommandBuffer*);
        MTL::RenderCommandEncoder *GetEncoder() { return m_encoder; };

    public: // vertex data
        MTL::Buffer *GetVertexBuffer();
        size_t GetVertexCount();

    public: // texture data
        vector_float2 *GetSize();
        TextureTargetMetal *GetTexture() { return m_texture; };

    private:
        void CreatePipeline();
    };
};

#endif /* drawable_metal_hpp */
