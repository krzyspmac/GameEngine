//
//  drawable_metal.hpp
//  Engine
//
//  Created by krzysp on 12/01/2022.
//

#ifndef drawable_metal_hpp
#define drawable_metal_hpp

#include "drawable_interface.h"
#include "common.h"
#include "common_engine_impl.h"
#include "texture_metal.hpp"
#include "sprite_atlas_interface.h"
#include "AAPLShaderTypes.h"

namespace engine
{
    /** Defines the metal drawable that goes to the gpu. */
    class DrawableMetal: public DrawableSpriteI
    {
        MTL::Buffer *m_vertexBuffer;
        vector_float2 m_size;
        TextureMetal *m_texture;
        size_t m_vertexCount;
    public: // DrawableSpriteI
        /** Construct a drawable for metal given a sprite descriptor */
        DrawableMetal(MTL::Device*, SpriteAtlasItemI*);
        virtual ~DrawableMetal();
        bool CanDraw();
    public:
        MTL::Buffer *GetVertexBuffer();
        size_t GetVertexCount();
        vector_float2 *GetSize();
        TextureMetal *GetTexture() { return m_texture; };
    };

    /** Defines a concrete metal class for the target drawable that is capable of
        accepting the render pass as its input.
     */
    class DrawableTargetMetal: public DrawableTargetI
    {

    };
};

#endif /* drawable_metal_hpp */
