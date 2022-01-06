//
//  sprite_renderer_manager.cpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#include "sprite_renderer_manager.hpp"
#include "sprite_draw_static.hpp"
#include "sprite_draw_animated.hpp"
#include "engine.hpp"

using namespace engine;

SpriteDrawI *SpriteRendererManager::SpriteDrawLoadStatic(SpriteAtlasItemI *sprite)
{
    SpriteDrawStatic *sd = new engine::SpriteDrawStatic(sprite, 1);

    if (sd)
    {
//        GetMainEngine()->getScripting().RegisterScriptingObject(sd);
        m_spriteDraws.emplace_back(std::move(sd));
    }
    return sd;
}

SpriteDrawI *SpriteRendererManager::SpriteDrawLoadAnimated(std::vector<SpriteAtlasItemI*> sprites, int frameAnimationDurationMs)
{
    engine::SpriteDrawAnimated *sd = new engine::SpriteDrawAnimated(sprites, frameAnimationDurationMs, 1);

    if (sd)
    {
        m_spriteDraws.emplace_back(std::move(sd));
    }
    return sd;

}

void SpriteRendererManager::SpriteDrawUnload(SpriteDrawI *spriteDraw)
{
    for(auto it = std::begin(m_spriteDraws); it != std::end(m_spriteDraws); ++it)
    {
        SpriteDrawI *item = it->get();
        if (item == spriteDraw)
        {
            m_spriteDraws.erase(it);
            break;
        }
    }
}

void SpriteRendererManager::SpriteDrawDisposeAll()
{
    m_spriteDraws.clear();
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(SpriteRendererManager);

static int lua_SpriteRendererManager_spriteDrawLoadStatic(lua_State *L)
{
    SpriteRendererManager *spriteRendererManager = ScriptingEngineI::GetScriptingObjectPtr<SpriteRendererManager>(L, 1);
    SpriteAtlasItemI *atlasItem = ScriptingEngineI::GetNormalObjectPtr<SpriteAtlasItemI>(L, 2);

    SpriteDrawStatic *result = (SpriteDrawStatic*)spriteRendererManager->SpriteDrawLoadStatic(atlasItem);
    if (result == nullptr) { return 0; };

    result->ScriptingInterfaceRegisterFunctions(L, result);
    //lua_pushlightuserdata(L, result); // SpriteDrawStatic not scriptable for now
    return 1;
}

std::vector<luaL_Reg> SpriteRendererManager::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "SpriteDrawLoadStatic", &lua_SpriteRendererManager_spriteDrawLoadStatic}
    });
    return result;
}
