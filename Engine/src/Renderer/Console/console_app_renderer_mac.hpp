//
//  console_app_renderer_mac.hpp
//  Engine
//
//  Created by krzysp on 08/01/2022.
//

#ifndef console_app_renderer_mac_hpp
#define console_app_renderer_mac_hpp

#include "console_renderer_interface.h"
#include "common_engine_impl.h"
#include <Metal/Metal.hpp>

#if TARGET_OS_OSX
//#import <Cocoa/Cocoa.h>
#else
#import <UIKit/UIKit.h>
#endif

namespace engine
{
    class ConsoleAppRendererMac: public ConsoleAppRendererI
    {
        bool m_hidden;
        bool m_isSetup;
        MTL::Device *m_device;
        MTL::RenderPassDescriptor *m_renderPassDescriptor;
        MTL::CommandBuffer *m_commandBuffer;
        MTL::RenderCommandEncoder *m_encoder;
#if TARGET_OS_OSX
        NSView *m_view;
#endif
    public: // ConsoleAppRendererI
        ConsoleAppRendererMac();
        virtual ~ConsoleAppRendererMac() { };

        void Setup();
        void SetDevice(MTL::Device*);
        void SetView(NSView*);
        void PrepareForFrame(NSView*, MTL::RenderPassDescriptor*, MTL::CommandBuffer*, MTL::RenderCommandEncoder*);
        void HandleEvent(NSEvent*);
        bool IsSetup();
        void DoFrame(std::function<void(void)>);
        void Render();
        void SetConsoleHidden(bool);

    private:
        void SetupWindow();
    };
};

#endif /* console_app_renderer_mac_hpp */
