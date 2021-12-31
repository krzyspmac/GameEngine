//
//  sprite_draw.cpp
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#include "sprite_draw_static.hpp"
#include "common_engine.h"

using namespace engine;

SpriteDrawStatic::SpriteDrawStatic(SpriteAtlasItemI *spriteAtlasItem, int scale)
    : SpriteDrawI(scale), m_sprite(spriteAtlasItem)
{
}

void SpriteDrawStatic::Draw(int x, int y)
{
    EngineProviderI &provider = GetMainEngine()->getProvider();

    provider.DrawTexture(
       m_sprite->GetTexture(),
       x,
       y,
       m_sprite->getX(),
       m_sprite->getY(),
       m_sprite->getWidth(),
       m_sprite->getHeight(),
       m_scale
    );
}

void SpriteDrawStatic::SetScale(float x)
{
    SpriteDrawI::SetScale(x);
}

void SpriteDrawStatic::Draw()
{
    Draw(m_position.x, m_position.y);
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(SpriteDrawStatic);

static int lua_SpriteDrawStatic_SetScale(lua_State *L)
{
    SpriteDrawStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteDrawStatic>(L, 1);
    float scale = lua_tonumberx(L, 2, NULL);
    spr->SetScale(scale);
    return 0;
}

std::vector<luaL_Reg> SpriteDrawStatic::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"SetScale", &lua_SpriteDrawStatic_SetScale}
    });
    return result;
}
