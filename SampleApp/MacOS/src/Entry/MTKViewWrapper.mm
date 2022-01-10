//
//  MTKViewWrapper.cpp
//  SampleApp
//
//  Created by krzysp on 10/01/2022.
//

#include "MTKViewWrapper.hpp"
#include <Metal/Metal.h>

using namespace engine;

MTKViewWrapper::MTKViewWrapper(CPPMetalInternal::View objCObj, MTL::Device & device)
    : m_objCObj(objCObj)
//    , m_device(&device),
//    , m_currentDrawable(nullptr),
//    , m_currentRenderPassDescriptor(nullptr),
//    , m_depthStencilTexture(nullptr)
{
//    m_objCObj.device = device.objCObj();
}

MTKViewWrapper::~MTKViewWrapper()
{
    m_objCObj = nil;
//    destroy(m_device->allocator(), m_currentDrawable);
//    destroy(m_device->allocator(), m_currentRenderPassDescriptor);
//    destroy(m_device->allocator(), m_depthStencilTexture);
}

void MTKViewWrapper::Draw()
{
//    (MTKVi)
//    [m_objCObj draw];
}

//
//View::View(const View & rhs) :
//m_objCObj(rhs.m_objCObj),
//m_device(rhs.m_device),
//m_currentDrawable(nullptr),
//m_currentRenderPassDescriptor(nullptr),
//m_depthStencilTexture(nullptr)
//{
//    if(rhs.m_depthStencilTexture)
//    {
//        m_depthStencilTexture = construct<Texture>(m_device->allocator(), *rhs.m_depthStencilTexture);
//    }
//}
//
//View::~View()
//{
//    m_objCObj = nil;
//    destroy(m_device->allocator(), m_currentDrawable);
//    destroy(m_device->allocator(), m_currentRenderPassDescriptor);
//    destroy(m_device->allocator(), m_depthStencilTexture);
//}
//
