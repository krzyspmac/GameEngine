/*
See LICENSE folder for this sample’s licensing information.

Abstract:
Header containing types and enum constants shared between Metal shaders and C/ObjC source
*/

#ifndef AAPLShaderTypes_h
#define AAPLShaderTypes_h

#include <simd/simd.h>

// Buffer index values shared between shader and C code to ensure Metal shader buffer inputs
// match Metal API buffer set calls.
typedef enum AAPLVertexInputIndex
{
    AAPLVertexInputIndexVertices        = 0,        // the vertices
    AAPLVertexInputIndexWindowSize      = 1,        // the current window size
    AAPLVertexInputIndexWindowScale     = 2,        // the current window scale
    AAPLVertexInputIndexObjectOffset    = 3,        // the object translation from the top, left corner in viewport coordinates
    AAPLVertexInputIndexObjectScale     = 4,        // the object scale
    AAPLVertexInputIndexObjectSize      = 5,        // the size of the object
    AAPLVertexInputIndexViewportSize    = 6,        // the current viewport size; usually
                                                    // set at the beginning; this is also the
                                                    // size of the framebuffer texture
} AAPLVertexInputIndex;

typedef enum FragmentShaderIndex
{
    FragmentShaderIndexBaseColor        = 0,
    FragmentShaderIndexBaseAlpha        = 1,
    FragmentShaderIndexLight            = 2,        // An array of light information
    FragmentShaderIndexLightCount       = 3,
    FragmentShaderIndexColorMod         = 4
} FragmentShaderIndex;

//  This structure defines the layout of vertices sent to the vertex
//  shader. This header is shared between the .metal shader and C code, to guarantee that
//  the layout of the vertex array in the C code matches the layout that the .metal
//  vertex shader expects.
typedef struct
{
    // Positions in pixel space. A value of 100 indicates 100 pixels from the origin/center.
    vector_float2 position;

    // 2D texture coordinate
    vector_float2 textureCoordinate;
} AAPLVertex;

typedef struct
{
    float lightType;
    vector_float3 color;            // 0-2
    float ambientIntensity;         // 3

    vector_float2 position;         // 4-5
    float diffuse_size;             // 6

    float diffuse_intensity;        // 7

    float enabled;                  // 8
//    float reserved1;                // 9
//    float reserved2;                // 10
//    float reserved3;                // 11

    /* Keep the structure aligned to 16 bytes!
        _________________________
       |0 1 2 3|4 5 6 7|8 9 10 11|
        -------------------------
       |       |       |         |
       | chunk0| chunk1| chunk2  |
    */
} AAPAmbientLLight;

typedef struct
{
    vector_float3 colorMod;
} ShaderColorMod;

#endif /* AAPLShaderTypes_h */
