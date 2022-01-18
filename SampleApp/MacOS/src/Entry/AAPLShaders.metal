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
             constant AAPLVertex *vertices [[buffer(AAPLVertexInputIndexVertices)]],
             constant vector_float2 *viewportSizePointer [[buffer(AAPLVertexInputIndexViewportSize)]],
             constant vector_float2 *viewportOffset [[buffer(AAPLVertexInputIndexViewportOffset)]],
             constant float *objectScalePointer [[buffer(AAPLVertexInputIndexViewportScale)]],
             constant vector_float2 *objectSizePointer [[buffer(AAPLVertexInputIndexObjectSize)]],
             constant vector_float2 *desiredViewportSizePointer [[buffer(AAPLVertexInputIndexViewportTarget)]]
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

    // Get the target object scale
    float objectScale = float(*objectScalePointer);

    // Get the object size
    vector_float2 objectSize = vector_float2(*objectSizePointer);

    // Get the target object translation
    vector_float2 objectTranslation = vector_float2(*viewportOffset);

    // Calculate aspect ratio & scale
    float scaleX, scaleY, scale;
    scaleX = viewportSize.x / (desiredViewportSize.x / objectScale);
    scaleY = viewportSize.y / (desiredViewportSize.y / objectScale);
    scale = min(scaleX, scaleY);

    float trscaleX, trscaleY, trscale;
    trscaleX = viewportSize.x / (desiredViewportSize.x / 1);
    trscaleY = viewportSize.y / (desiredViewportSize.y / 1);
    trscale = min(trscaleX, trscaleY);
//
//    // Calculate offsets due to scaling
//    // TBD
//    vector_float2 targetViewportSize;
//    targetViewportSize.xy = desiredViewportSize * trscale;
//
//    vector_float2 targetObjectSize;
//    targetObjectSize.xy = objectSize * scale;

    pixelSpacePosition.xy *= scale;
//
    pixelSpacePosition.x += objectTranslation.x * trscale;// - targetViewportSize.x/2;
    pixelSpacePosition.y += objectTranslation.y * trscale;// - targetViewportSize.x/2;







//    pixelSpacePosition.x -= (viewportSize.x - targetViewportSize.x)/2;

//    float offsetXToEdge = viewportSize.x/2 - ((targetObjectSize.x)/2);
//
//    float offsetXToViewport = (viewportSize.x - targetViewportSize.x) / 2;
//
//
//    float pos = objectTranslation.x * scale;
//
//    pixelSpacePosition.x -= offsetXToEdge;// + (viewportSize.x/2 - targetObjectSize.x/2);
//    pixelSpacePosition.x -= targetObjectSize.x/2;
//
//    pixelSpacePosition.x += pos;
//
//    pixelSpacePosition.x += targetObjectSize.x/2;
//    pixelSpacePosition.x += offsetXToEdge;

    
//    pixelSpacePosition.x += pos;
    
//    pixelSpacePosition.x -= offsetXToEdge;
    
//    pixelSpacePosition.x += targetObjectSize.x/2;
//    pixelSpacePosition.x += 1280 / scale;
//    pixelSpacePosition.x -= targetObjectSize.x / 2;
//
//    pixelSpacePosition.x += objectTranslation.x * scale;
//
//    pixelSpacePosition.x += targetObjectSize.x / 2;
//    pixelSpacePosition.x += offsetXToEdge;
    
//    pixelSpacePosition.x += objectTranslation.x * scale;
//    pixelSpacePosition.x -=
//    pixelSpacePosition.x += (objectTranslation.x * scale / 1);
//    pixelSpacePosition.x -= viewportSize.x / 2;
//    pixelSpacePosition.x -= (objectSize.x * objectScale * scale);
//    pixelSpacePosition.x -= objectSize.x / 2;
//    pixelSpacePosition.x += objectTranslation.x * scale;
//    pixelSpacePosition.x += offsetXToEdge;

//    pixelSpacePosition.x = pixelSpacePosition.x + objectTranslation.x * scale / 2;

    // To convert from positions in pixel space to positions in clip-space,
    //  divide the pixel coordinates by half the size of the viewport.
    out.position = vector_float4(0.0, 0.0, 0.0, 1.0);
    out.position.xy = pixelSpacePosition / (viewportSize / 2.0);

    // Pass the input color directly to the rasterizer.
//    out.color = vertices[vertexID].color;
    out.textureCoordinate = vertices[vertexID].textureCoordinate;

    return out;
}

//fragment float4 fragmentShader(RasterizerData in [[stage_in]])
//{
//    // Return the interpolated color.
//    return in.color;
//}

// Fragment function
fragment float4
fragmentShader(RasterizerData in [[stage_in]],
               texture2d<half> colorTexture [[ texture(AAPLTextureIndexBaseColor) ]],
               constant float *alphaPointer [[buffer(AAPLTextureIndexBaseAlpha)]]
               )
{
//    return in.color;

    constexpr sampler textureSampler (mag_filter::nearest,
                                      min_filter::nearest);

    // Sample the texture to obtain a color
    const half4 colorSample = colorTexture.sample(textureSampler, in.textureCoordinate);

//    colorSample.a = *alphaPointer;

    // 3
    if (/*transparencyEnabled && */colorSample.a < 0.1) {
      discard_fragment();
    }

    // return the color of the texture
    return float4(colorSample);
}

