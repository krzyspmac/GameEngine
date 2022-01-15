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
    class DrawableMetal: public DrawableI
    {
        AAPLVertex *m_triangleVertices;
        size_t m_triangleVerticiesDataSize;
        vector_float2 m_size;
        float m_scale;
        SpriteAtlasItemI *m_atlasItem;
        TextureMetal *m_texture;
    public: // Drawable I
        DrawableMetal(SpriteAtlasItemI*, float, float);
        void SetPosition(float, float);
        void SetScale(float);

    public:
        AAPLVertex *GetVertexData();
        size_t GetVertexDataSize();
        size_t GetVertexCount();
        float *GetScale();
        vector_float2 *GetSize();
        TextureMetal *GetTexture() { return m_texture; };
    };
};

#endif /* drawable_metal_hpp */
