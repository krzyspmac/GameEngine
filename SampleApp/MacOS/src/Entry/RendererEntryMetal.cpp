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

void RendererEntryMetal::Create(MTL::PixelFormat pixelFormat)
{
    m_device = MTL::CreateSystemDefaultDevice();

    m_library = m_device->newDefaultLibrary();

    m_vertexFuntion = m_library->newFunction(STR("vertexShader"));
    m_fragmentFunction = m_library->newFunction(STR("fragmentShader"));

    m_renderePipelineDescriptor = MTL::RenderPipelineDescriptor::alloc()->init();
    m_renderePipelineDescriptor->setLabel(STR("Simple Pipeline"));
    m_renderePipelineDescriptor->setVertexFunction(m_vertexFuntion);
    m_renderePipelineDescriptor->setFragmentFunction(m_fragmentFunction);
    m_renderePipelineDescriptor->colorAttachments()->object(0)->setPixelFormat(pixelFormat);

    NS::Error *error = nullptr;
    m_pipelineState = m_device->newRenderPipelineState(m_renderePipelineDescriptor, &error);
    if (m_pipelineState == nullptr)
    {
        printf("Failed to create pipeline state %s\n", error->description()->cString(NS::ASCIIStringEncoding));
    }
//    NSAssert(m_pipelineState, @"Failed to create pipeline state: %@", error);
/*



 // Configure a pipeline descriptor that is used to create a pipeline state.
 MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
 pipelineStateDescriptor.label = @"Simple Pipeline";
 pipelineStateDescriptor.vertexFunction = vertexFunction;
 pipelineStateDescriptor.fragmentFunction = fragmentFunction;
 pipelineStateDescriptor.colorAttachments[0].pixelFormat = mtkView.colorPixelFormat;

 _pipelineState = [_device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor
                                                          error:&error];

 // Pipeline State creation could fail if the pipeline descriptor isn't set up properly.
 //  If the Metal API validation is enabled, you can find out more information about what
 //  went wrong.  (Metal API validation is enabled by default when a debug build is run
 //  from Xcode.)
 NSAssert(_pipelineState, @"Failed to create pipeline state: %@", error);

 */

    m_commandQueue = m_device->newCommandQueue();
}
