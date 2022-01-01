//
//  sprite_draw.cpp
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#include "sprite_draw_static.hpp"
#include "common_engine.h"
#include "common.h"
#include "scripting_engine.hpp"

using namespace engine;

SpriteDrawStatic::SpriteDrawStatic(SpriteAtlasItemI *spriteAtlasItem, int scale)
    : SpriteDrawI(scale), m_sprite(spriteAtlasItem)
{
}

void SpriteDrawStatic::DrawAt(int x, int y)
{
    EngineProviderI &provider = GetMainEngine()->getProvider();
    TextureI *texture = m_sprite->GetTexture();

    provider.TextureAlphaSetMod(texture, m_alpha);

    provider.DrawTexture(
       texture,
       x,
       y,
       m_sprite->GetX(),
       m_sprite->GetY(),
       m_sprite->GetWidth(),
       m_sprite->GetHeight(),
       m_scale
    );
}

void SpriteDrawStatic::SetScale(float x)
{
    SpriteDrawI::SetScale(x);
}

void SpriteDrawStatic::Draw()
{
    DrawAt(m_position.x, m_position.y);
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

static int lua_SpriteDrawStatic_DrawAt(lua_State *L)
{
    SpriteDrawStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteDrawStatic>(L, 1);
    float x = lua_tonumberx(L, 2, NULL);
    float y = lua_tonumberx(L, 3, NULL);
    spr->DrawAt(x, y);
    return 0;
}

static int lua_SpriteDrawStatic_SetAlpha(lua_State *L)
{
    SpriteDrawStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteDrawStatic>(L, 1);
    float x = MAX(0, MIN(255, lua_tonumberx(L, 2, NULL)));
    spr->SetAlpha(x);
    return 0;
}

static int lua_SpriteDrawStatic_GetAlpha(lua_State *L)
{
    SpriteDrawStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteDrawStatic>(L, 1);
    float x = spr->GetAlpha();
    lua_pushnumber(L, x);
    return 1;
}

static int lua_SpriteDrawStatic_Draw(lua_State *L)
{
    SpriteDrawStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteDrawStatic>(L, 1);
    spr->Draw();
    return 0;
}

std::vector<luaL_Reg> SpriteDrawStatic::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"SetScale", &lua_SpriteDrawStatic_SetScale},
        {"DrawAt", &lua_SpriteDrawStatic_DrawAt},
        {"SetAlpha", &lua_SpriteDrawStatic_SetAlpha},
        {"GetAlpha", &lua_SpriteDrawStatic_GetAlpha},
        {"Draw", &lua_SpriteDrawStatic_Draw}
    });
    return result;
}
