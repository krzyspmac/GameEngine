//
//  console_view.cpp
//  Engine
//
//  Created by krzysp on 29/12/2021.
//

#include "console_view.hpp"
#include "engine.hpp"

#define CONSOLE_BACKGROUND_C    0, 0, 0, 200

using namespace engine;

ConsoleView::ConsoleView(FontI *font, char keyTrigger)
: ConsoleViewI(font, keyTrigger)
{
    Size &vs = GetMainEngine()->GetViewport();
    m_consoleViewportRect.x = 0;
    m_consoleViewportRect.y = 0;
    m_consoleViewportRect.w = vs.width;
    m_consoleViewportRect.h = vs.height;
    m_bufferTexture = GetMainEngine()->CreateTargetTexture(vs.width, vs.height);
}

ConsoleView::~ConsoleView()
{
    delete m_bufferTexture;
}

bool ConsoleView::ShouldPresentConsole()
{
    return true;
}

bool ConsoleView::IsPresented()
{
    return false;
}

bool ConsoleView::PresentConsole()
{
    return false;
}

void ConsoleView::RenderConsole()
{
    EngineProviderI &provider = GetMainEngine()->getProvider();
    provider.RendererTargetPush(m_bufferTexture);
    RenderScene();
    provider.RendererTargetPop();
    provider.DrawTexture(m_bufferTexture, 0, 0);
}

void ConsoleView::RenderScene()
{
    EngineProviderI &provider = GetMainEngine()->getProvider();

    provider.RenderSetColor(CONSOLE_BACKGROUND_C);
    provider.RenderFillRect(&m_consoleViewportRect);
}
