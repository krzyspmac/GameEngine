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
    AAPLVertexInputIndexViewportSize    = 1,        // the current viewport size (window size)
    AAPLVertexInputIndexViewportOffset  = 3,        // the object translation from the top, left corner
    AAPLVertexInputIndexViewportScale   = 4,        // the object scale
    AAPLVertexInputIndexObjectSize      = 5,        // the size of the object
    AAPLVertexInputIndexViewportTarget  = 6,        // the desired viewport size
} AAPLVertexInputIndex;

//  This structure defines the layout of vertices sent to the vertex
//  shader. This header is shared between the .metal shader and C code, to guarantee that
//  the layout of the vertex array in the C code matches the layout that the .metal
//  vertex shader expects.
typedef struct
{
    vector_float2 position;
    vector_float4 color;
} AAPLVertex;

#endif /* AAPLShaderTypes_h */
