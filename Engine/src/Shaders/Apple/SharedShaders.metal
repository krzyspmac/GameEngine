//
//  SharedShaders.metal
//  Engine
//
//  Created by krzysp on 13/02/2022.
//

#include <metal_stdlib>
using namespace metal;

// Vertex shader outputs and fragment shader inputs
struct RasterizerData
{
    // The [[position]] attribute of this member indicates that this value
    // is the clip space position of the vertex when this structure is
    // returned from the vertex function.
    float4 position [[position]];

    // Since this member does not have a special attribute qualifier, the rasterizer
    // will interpolate its value with values of other vertices making up the triangle
    // and pass that interpolated value to the fragment shader for each fragment in
    // that triangle.
    float2 textureCoordinate;
};

typedef enum {
  Position = 0,
  TextureCoordinate = 1,
} Attributes;

typedef struct
{
    // Positions in pixel space. A value of 100 indicates 100 pixels from the origin/center.
//    vector_float3 position;
//
//    // 2D texture coordinate
//    vector_float2 textureCoordinate;

    vector_float4 position [[attribute(Position)]];
    vector_float2 textureCoordinate [[attribute(TextureCoordinate)]];


} AAPLVertexIn;
