//
//  RendererEntryMetal.hpp
//  SampleApp
//
//  Created by krzysp on 09/01/2022.
//

#ifndef RendererEntryMetal_hpp
#define RendererEntryMetal_hpp

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include <Metal/Metal.hpp>

namespace engine
{
    class RendererEntryMetal
    {
        MTL::Device *m_device;

        MTL::RenderPipelineState *m_pipelineState;
        MTL::Library *m_library;
        MTL::Function *m_vertexFuntion;
        MTL::Function *m_fragmentFunction;
        MTL::RenderPipelineDescriptor *m_renderePipelineDescriptor;
        MTL::CommandQueue *m_commandQueue;

        /*
         id<MTLDevice> _device;

         // The render pipeline generated from the vertex and fragment shaders in the .metal shader file.
         id<MTLRenderPipelineState> _pipelineState;

         // The command queue used to pass commands to the device.
         id<MTLCommandQueue> _commandQueue;

         // The current size of the view, used as an input to the vertex shader.
         vector_uint2 _viewportSize;

         */
    public:
        RendererEntryMetal();

        void Create(MTL::PixelFormat);
    };
};

#endif /* RendererEntryMetal_hpp */
