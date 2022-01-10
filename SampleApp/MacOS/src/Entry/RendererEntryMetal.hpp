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

#include "AAPLShaderTypes.h"

namespace engine
{
    typedef struct
    {
        double width;
        double height;
    } MTLSize;

    inline MTLSize MTLSizeMake(double w, double h)
    {
        MTLSize result;
        result.width = w;
        result.height = h;
        return result;
    };

    class RendererEntryMetal
    {
        MTL::Device *m_device;
        vector_uint2 m_viewportSize;

//        MTL::RenderPipelineState *m_pipelineState;
//        MTL::Library *m_library;
//        MTL::Function *m_vertexFuntion;
//        MTL::Function *m_fragmentFunction;
//        MTL::RenderPipelineDescriptor *m_renderePipelineDescriptor;
//        MTL::CommandQueue *m_commandQueue;

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

        void Create(MTL::PixelFormat, MTL::Device*);

        void DrawableSizeWillChange(float width, float height);

        void Draw(MTL::CommandQueue*s, MTL::RenderPipelineState*, MTL::RenderPassDescriptor*, MTL::Drawable*, std::function<MTL::Drawable*(void)> lambda);
    };
};

#endif /* RendererEntryMetal_hpp */
