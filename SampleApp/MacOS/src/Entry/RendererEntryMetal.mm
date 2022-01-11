//
//  RendererEntryMetal.cpp
//  SampleApp
//
//  Created by krzysp on 09/01/2022.
//

#include "RendererEntryMetal.hpp"

using namespace engine;

#define STR(x) NS::MakeConstantString(#x)

RendererEntryMetal::RendererEntryMetal()
{
}

void RendererEntryMetal::Create(MTL::PixelFormat pixelFormat, MTL::Device *device)
{
    m_device = device;

    m_library = m_device->newDefaultLibrary();
    m_vertexFuntion = m_library->newFunction(NS::MakeConstantString("vertexShader"));
    m_fragmentFunction = m_library->newFunction(NS::MakeConstantString("fragmentShader"));

    m_renderePipelineDescriptor = MTL::RenderPipelineDescriptor::alloc()->init();
    m_renderePipelineDescriptor->setLabel(NS::MakeConstantString("Simple Pipeline"));
    m_renderePipelineDescriptor->setVertexFunction(m_vertexFuntion);
    m_renderePipelineDescriptor->setFragmentFunction(m_fragmentFunction);
    m_renderePipelineDescriptor->colorAttachments()->object(0)->setPixelFormat(pixelFormat);

    NS::Error *error = nullptr;
    m_pipelineState = m_device->newRenderPipelineState(m_renderePipelineDescriptor, &error);
    if (m_pipelineState == nullptr)
    {
        printf("Failed to create pipeline state %s\n", error->description()->cString(NS::ASCIIStringEncoding));
    }

    m_commandQueue = m_device->newCommandQueue();
}

void RendererEntryMetal::DrawableSizeWillChange(float width, float height)
{
    m_viewportSize.x = width;
    m_viewportSize.y = height;
}

void RendererEntryMetal::Draw(MTL::RenderPassDescriptor *renderPassDescriptor, MTL::Drawable *currentDrawable)
{
    static const AAPLVertex triangleVertices[] =
    {
        // 2D positions,    RGBA colors
        { {  250,  -250 }, { 1, 0, 0, 1 } },
        { { -250,  -250 }, { 0, 1, 0, 1 } },
        { {    0,   250 }, { 0, 0, 1, 1 } },
    };

    // Create a new command buffer for each render pass to the curernt drawable.
    auto commandBuffer = (m_commandQueue)->commandBuffer();

    // Obtain a renderPassDescriptor generated from the view's drawable textures.
    if (renderPassDescriptor != nullptr)
    {
        // Create a render command encoder.
        auto renderEncoder = commandBuffer->renderCommandEncoder(renderPassDescriptor);

        // Set the region of the drawable to draw into.
        double x = m_viewportSize.x;
        double y = m_viewportSize.y;
        MTL::Viewport viewport = {0.0, 0.0, x, y, 0.0, 1.0};
        renderEncoder->setViewports( &viewport, 1 );

        // Set pipeline state
        renderEncoder->setRenderPipelineState(m_pipelineState);

        // Pass in the parameter data.
        renderEncoder->setVertexBytes(triangleVertices, sizeof(triangleVertices), AAPLVertexInputIndexVertices);
        renderEncoder->setVertexBytes(&m_viewportSize, sizeof(m_viewportSize), AAPLVertexInputIndexViewportSize);

        // Draw the triangle
        renderEncoder->drawPrimitives(MTL::PrimitiveTypeTriangle, (NS::UInteger)0, (NS::UInteger)3);

        renderEncoder->endEncoding();

        // Schedule a present once the framebuffer is complete using the current drawable.
        commandBuffer->presentDrawable(currentDrawable);
    }

    commandBuffer->commit();

}
