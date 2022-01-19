/*
See LICENSE folder for this sample’s licensing information.

Abstract:
Metal shaders used for this sample
*/

#include <metal_stdlib>

using namespace metal;

// Include header shared between this Metal shader code and C code executing Metal API commands.
#include "AAPLShaderTypes.h"

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

vertex RasterizerData
vertexShader(uint vertexID [[vertex_id]],
             constant AAPLVertex    *vertices               [[buffer(AAPLVertexInputIndexVertices)]],
             constant float         *viewportScalePointer   [[buffer(AAPLVertexInputIndexWindowScale)]],
             constant vector_float2 *viewportOffset         [[buffer(AAPLVertexInputIndexObjectOffset)]],
             constant float         *objectScalePointer     [[buffer(AAPLVertexInputIndexObjectScale)]],
             constant vector_float2 *objectSizePointer      [[buffer(AAPLVertexInputIndexObjectSize)]],
             constant vector_float2 *viewportSizePointer    [[buffer(AAPLVertexInputIndexViewportSize)]]
             )
{
    RasterizerData out;

    // Index into the array of positions to get the current vertex.
    // The positions are specified in pixel dimensions (i.e. a value of 100
    // is 100 pixels from the origin).
    float2 pixelSpacePosition = vertices[vertexID].position.xy;

    // Get the viewport size and cast to float.
    vector_float2 viewportSize = vector_float2(*viewportSizePointer);

    // Get the viewport scale
    float viewportScale = float(*viewportScalePointer);

    // Get the target object scale
    float objectScale = float(*objectScalePointer);

    // Get the object size
    vector_float2 objectSize = vector_float2(*objectSizePointer);

    // Calculate object size scaled
    vector_float2 objectSizeScaled = objectSize.xy * objectScale * viewportScale;

    // Get the target object translation
    vector_float2 objectTranslation = vector_float2(*viewportOffset);
    objectTranslation.xy *= 2;

    // Scale the object based on the viewport scale
    pixelSpacePosition.xy *= viewportScale;

    // Sacle the object based on internal scale
    pixelSpacePosition.xy *= objectScale;

    // Translate to top-left corner
    pixelSpacePosition.x -= (viewportSize.x - objectSizeScaled.x)/2;
    pixelSpacePosition.y += (viewportSize.y - objectSizeScaled.y)/2;

    // Apply translation
    pixelSpacePosition.x += objectTranslation.x / viewportScale;
    pixelSpacePosition.y -= objectTranslation.y / viewportScale;

    // To convert from positions in pixel space to positions in clip-space,
    //  divide the pixel coordinates by half the size of the viewport.
    out.position = vector_float4(0.0, 0.0, 0.0, 1.0);
    out.position.xy = pixelSpacePosition / (viewportSize / 2.0);

    // Pass the input color directly to the rasterizer.
    out.textureCoordinate = vertices[vertexID].textureCoordinate;

    return out;
}

// Fragment function
fragment float4
fragmentShader(RasterizerData in [[stage_in]],
               texture2d<half> colorTexture [[ texture(AAPLTextureIndexBaseColor) ]],
               constant float *alphaPointer [[buffer(AAPLTextureIndexBaseAlpha)]]
               )
{
    constexpr sampler textureSampler (mag_filter::nearest,
                                      min_filter::nearest);

    // Sample the texture to obtain a color
    const half4 colorSample = colorTexture.sample(textureSampler, in.textureCoordinate);

    // Get the chosen alpha transparency for the object
    float alpha = float(*alphaPointer);

    // If not visible hide the fragment anyway
    if (alpha <= 0)
    {
        discard_fragment();
    }

    // If still visible combine with the fragment's alpha
    colorSample.a *= *alphaPointer;

    if (colorSample.a <= 0.0001)
    {
        discard_fragment();
    }

    // return the color of the texture
    return float4(colorSample);
}


#pragma mark -
#pragma mark Final presenter shaders

// Vertex shader which adjusts positions by an aspect ratio and passes texture
// coordinates through to the rasterizer.
vertex RasterizerData
presenterVertexShader(const uint vertexID [[ vertex_id ]],
                      const device AAPLVertex *vertices [[ buffer(AAPLVertexInputIndexVertices) ]],
                      constant vector_float2 *viewportSizePointer [[buffer(AAPLVertexInputIndexWindowSize)]],
                      constant float *viewportScalePointer [[buffer(AAPLVertexInputIndexWindowScale)]],
                      constant vector_float2 *desiredViewportSizePointer [[buffer(AAPLVertexInputIndexViewportSize)]]
                      )
{
    RasterizerData out;

    // Index into the array of positions to get the current vertex.
    // The positions are specified in pixel dimensions (i.e. a value of 100
    // is 100 pixels from the origin).
    float2 pixelSpacePosition = vertices[vertexID].position.xy;

    // Get the viewport size and cast to float.
    vector_float2 viewportSize = vector_float2(*viewportSizePointer);

    // Get the desired viewport size; used to calaculate aspect ratio
    vector_float2 desiredViewportSize = vector_float2(*desiredViewportSizePointer);

    // Calculate aspect ratio & scale
    float scaleX, scaleY, scale;
    scaleX = viewportSize.x / desiredViewportSize.x;
    scaleY = viewportSize.y / desiredViewportSize.y;
    scale = min(scaleX, scaleY);

    out.position = vector_float4(0.0, 0.0, 0.0, 1.0);
//    out.position.xy = pixelSpacePosition / (viewportSize / 2.0);
    out.position.xy = pixelSpacePosition.xy;//* scale/2;

//    out.position = vector_float4(0.0, 0.0, 0.0, 1.0);
//    out.position.x = vertices[vertexID].position.x * 1;//aspectRatio;
//    out.position.y = vertices[vertexID].position.y;

    out.textureCoordinate = vertices[vertexID].textureCoordinate;

    return out;
}
// Fragment shader that samples a texture and outputs the sampled color.
fragment float4 presenterFragmentShader(RasterizerData in  [[stage_in]],
                                        texture2d<float> texture [[texture(AAPLTextureIndexBaseColor)]])
{
    constexpr sampler simpleSampler;

    // Sample data from the texture.
    float4 colorSample = texture.sample(simpleSampler, in.textureCoordinate);

    // Return the color sample as the final color.
    return colorSample;
}
