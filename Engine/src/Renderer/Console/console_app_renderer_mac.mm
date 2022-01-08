//
//  console_app_renderer_mac.cpp
//  Engine
//
//  Created by krzysp on 08/01/2022.
//

#include <Metal/Metal.h>
#include <QuartzCore/QuartzCore.h>
#include <Cocoa/Cocoa.h>
#include "common.h"
#include "console_renderer.h"
#include "engine_provider.hpp"
#include "engine.hpp"
#include "console_logger.hpp"
#include "console_terminal.hpp"
#include "console_app_renderer_mac.hpp"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_metal.h"


/* Shared namespace */
using namespace engine;

/**
 Static definitions for the console. In case of a debug guild only one console can exist.
 */
#define SCREEN_WIDTH  1020
#define SCREEN_HEIGHT 1020

API_AVAILABLE(macos(10.11))
static CAMetalLayer* layer = nullptr;

API_AVAILABLE(macos(10.11))
static id<MTLCommandQueue> commandQueue;

API_AVAILABLE(macos(10.11))
static MTLRenderPassDescriptor* renderPassDescriptor;

static float clear_color[4] = {0.45f, 0.55f, 0.60f, 0.0f};

ConsoleAppRendererMac::ConsoleAppRendererMac()
    : ConsoleAppRendererI()
{
}

void ConsoleAppRendererMac::SetupWindow()
{
    int rendererFlags, windowFlags;
    windowFlags = 0;
    rendererFlags = SDL_RENDERER_ACCELERATED;

    m_app.window = SDL_CreateWindow("Console", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

    if(!m_app.window)
    {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        return;
    }

    m_app.renderer = SDL_CreateRenderer(m_app.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_app.renderer == NULL)
    {
        printf("Error creating renderer: %s\n", SDL_GetError());
        return;
    }

    SDL_SetWindowResizable(m_app.window, SDL_TRUE);

    m_isSetup = true;
}

void ConsoleAppRendererMac::DoFrame(std::function<void(void)> lambda)
{
#if SHOW_CONSOLE
    if (!m_isSetup) { return; };

    if (@available(macOS 10.11, *)) {
        int width;
        int height;
        SDL_GetRendererOutputSize(m_app.renderer, &width, &height);

        layer.drawableSize = CGSizeMake(width, height);
        id<CAMetalDrawable> drawable = [layer nextDrawable];
        id<MTLCommandBuffer> commandBuffer = [commandQueue commandBuffer];
        renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(clear_color[0] * clear_color[3], clear_color[1] * clear_color[3], clear_color[2] * clear_color[3], clear_color[3]);
        renderPassDescriptor.colorAttachments[0].texture = drawable.texture;
        renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
        renderPassDescriptor.colorAttachments[0].storeAction = MTLStoreActionStore;
        id <MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
        [renderEncoder pushDebugGroup:@"ImGui demo"];

        ImGui_ImplMetal_NewFrame(renderPassDescriptor);
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Gui
        lambda();

        // Rendering
        ImGui::Render();
        ImGui_ImplMetal_RenderDrawData(ImGui::GetDrawData(), commandBuffer, renderEncoder);

        [renderEncoder popDebugGroup];
        [renderEncoder endEncoding];

        [commandBuffer presentDrawable:drawable];
        [commandBuffer commit];
    } else {
        // Fallback on earlier versions
    }
#endif
}

void ConsoleAppRendererMac::SetupImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    if (@available(macOS 10.11, *)) {
        layer = (__bridge CAMetalLayer*)SDL_RenderGetMetalLayer(m_app.renderer);
        layer.pixelFormat = MTLPixelFormatBGRA8Unorm;
        layer.backgroundColor = [NSColor clearColor].CGColor;

        ImGui_ImplMetal_Init(layer.device);
        ImGui_ImplSDL2_InitForMetal(m_app.window);

        commandQueue = [layer.device newCommandQueue];
        renderPassDescriptor = [MTLRenderPassDescriptor new];
    } else {
        // Fallback on earlier versions
    }
}

bool ConsoleAppRendererMac::IsSetup()
{
    return m_isSetup;
}

void ConsoleAppRendererMac::SetConsoleHidden(bool hidden)
{
    if (!hidden)
    {
        SDL_ShowWindow(m_app.window);
    }
    else
    {
        SDL_HideWindow(m_app.window);
    }
}

void ConsoleAppRendererMac::Setup()
{
    SetupWindow();
    SetupImGui();
}
