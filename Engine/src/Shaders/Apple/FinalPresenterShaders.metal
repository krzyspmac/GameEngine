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

#include <metal_stdlib>
using namespace metal;

#include "AAPLShaderTypes.h"
#include "SharedShaders.metal"

inline float angle2rad(float angle) {
    return M_PI_F * angle / 180.0f;
}

// Vertex shader which adjusts positions by an aspect ratio and passes texture
// coordinates through to the rasterizer.
vertex RasterizerData
presenterVertexShader(const uint vertexID [[ vertex_id ]],
                      const device AAPLVertex *vertices             [[ buffer(AAPLVertexInputIndexVertices) ]],
                      constant vector_float2  *viewportSizePointer  [[buffer(AAPLVertexInputIndexWindowSize)]],
                      constant float          *viewportScalePointer [[buffer(AAPLVertexInputIndexWindowScale)]],
                      constant vector_float2  *desiredViewportSizePointer [[buffer(AAPLVertexInputIndexViewportSize)]],
                      constant float          *affineScalePointer   [[buffer(AAPLVertexInputIndexObjectScale)]],
                      constant vector_float2  *screenPosition       [[buffer(AAPLVertexInputIndexObjectOffset)]]
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

    // Get the screenOffset
    vector_float2 screenOffset = vector_float2(*screenPosition);

    // Get the target final scale for the texture
    float targetAffineScale = float(*affineScalePointer);
    float2 scale = viewportSize / desiredViewportSize;

    // Apply translation
    pixelSpacePosition.x += (screenOffset.x / viewportSize.x) * scale.x * 2;
    pixelSpacePosition.y -= (screenOffset.y / viewportSize.y) * scale.y * 2;

    float angle = angle2rad(0);//M_PI_F / 4.0;

    float4x4 rotationMatrix = float4x4{
    {cos(angle),        -sin(angle),          0,     0},
    {sin(angle),        cos(angle),           0,     0},
    {0.0,               0.0,                1.0,     0},
    {0.0,               0.0,                0.0,     1}
    };



    out.position = vector_float4(0.0, 0.0, 0.0, 1.0);
    out.position.xy = pixelSpacePosition / scale * targetAffineScale;
    out.position = rotationMatrix * out.position;

    out.textureCoordinate = vertices[vertexID].textureCoordinate;

    return out;
}
// Fragment shader that samples a texture and outputs the sampled color.
fragment float4 presenterFragmentShader(
      RasterizerData    in              [[stage_in]]
    , texture2d<float>  texture         [[texture (FragmentShaderIndexBaseColor)]]
    , constant float    *alphaPointer   [[ buffer (FragmentShaderIndexBaseAlpha)]]
)
{
    constexpr sampler simpleSampler;

    // Sample data from the texture.
    float4 colorSample = texture.sample(simpleSampler, in.textureCoordinate);

    // If still visible combine with the fragment's alpha
    colorSample.a *= *alphaPointer;

    if (colorSample.a <= 0.0001)
    {
        discard_fragment();
        return float4(colorSample);
    }


    // Return the color sample as the final color.
    return colorSample;
}
