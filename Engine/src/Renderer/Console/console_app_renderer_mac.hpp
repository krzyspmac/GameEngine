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

#ifndef console_app_renderer_mac_hpp
#define console_app_renderer_mac_hpp

#include "console_renderer_interface.h"
#include "interfaces.h"
#include <Metal/Metal.hpp>

#if TARGET_OS_OSX
#import <Cocoa/Cocoa.h>
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
        virtual ~ConsoleAppRendererMac();

        void Setup();
        void SetDevice(MTL::Device*);
#if TARGET_OS_OSX
        void SetView(NSView*);
        void PrepareForFrame(NSView*, MTL::RenderPassDescriptor*, MTL::CommandBuffer*, MTL::RenderCommandEncoder*);
        bool HandleEvent(NSEvent*);
#endif
        bool IsSetup();
        void DoFrame(std::function<void(void)>);
        void Render();
        void SetConsoleHidden(bool);

    private:
        void SetupWindow();
    };
};

#endif /* console_app_renderer_mac_hpp */
