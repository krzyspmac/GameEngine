//
//  sprite_renderer_manager.cpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#include "sprite_renderer_manager.hpp"
#include "sprite_representation_static.hpp"
#include "sprite_representation_animated.hpp"
#include "engine.hpp"

using namespace engine;

SpriteRepresetationI *SpriteRendererManager::SpriteRepresentationStaticLoad(SpriteAtlasItemI *sprite)
{
    SpriteRepresentationStatic *sd = new SpriteRepresentationStatic(sprite);

    if (sd)
    {
        m_spriteDraws.emplace_back(std::move(sd));
    }
    return sd;
}

SpriteRepresetationI *SpriteRendererManager::SpriteRepresentationAnimatedLoad(int frameAnimationDurationMs, std::vector<SpriteAtlasItemI*> sprites)
{
    engine::SpriteRepresentationAnimated *sd = new SpriteRepresentationAnimated(sprites, frameAnimationDurationMs);
    if (sd)
    {
        m_spriteDraws.emplace_back(std::move(sd));
    }
    return sd;
}

SpriteRepresetationI *SpriteRendererManager::SpriteRepresentationAnimatedLoad(int frameAnimationDurationMs, SpriteAtlasI *atlas)
{
    engine::SpriteRepresentationAnimated *sd = SpriteRepresentationAnimated::CreateFromAtlas(atlas->GetAllItems(), frameAnimationDurationMs);
    if (sd)
    {
        m_spriteDraws.emplace_back(std::move(sd));
    }
    return sd;
}

void SpriteRendererManager::SpriteDrawUnload(SpriteRepresetationI *spriteDraw)
{
    for(auto it = std::begin(m_spriteDraws); it != std::end(m_spriteDraws); ++it)
    {
        SpriteRepresetationI *item = it->get();
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

    SpriteRepresentationStatic *result = (SpriteRepresentationStatic*)spriteRendererManager->SpriteRepresentationStaticLoad(atlasItem);
    if (result == nullptr) { return 0; };

    result->ScriptingInterfaceRegisterFunctions(L, result);
    return 1;
}

static int lua_SpriteRendererManager_spriteDrawLoadAnimated(lua_State *L)
{
    SpriteRendererManager *spriteRendererManager = ScriptingEngineI::GetScriptingObjectPtr<SpriteRendererManager>(L, 1);
    SpriteAtlasItemI *atlasItem = ScriptingEngineI::GetNormalObjectPtr<SpriteAtlasItemI>(L, 2);

    SpriteRepresentationStatic *result = (SpriteRepresentationStatic*)spriteRendererManager->SpriteRepresentationStaticLoad(atlasItem);
    if (result == nullptr) { return 0; };

    result->ScriptingInterfaceRegisterFunctions(L, result);
    return 1;
}

std::vector<luaL_Reg> SpriteRendererManager::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "SpriteRepresentationStaticLoad", &lua_SpriteRendererManager_spriteDrawLoadStatic }
      , { "SpriteRepresentationAnimatedLoad",  &lua_SpriteRendererManager_spriteDrawLoadAnimated }
    });
    return result;
}
