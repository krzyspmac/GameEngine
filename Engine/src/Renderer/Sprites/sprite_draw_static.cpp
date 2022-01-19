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

SpriteDrawStatic::SpriteDrawStatic(SpriteAtlasItemI *spriteAtlasItem, float scale)
    : SpriteDrawI(scale), m_sprite(spriteAtlasItem)
{
    auto drawable = GetMainEngine()->getProvider().DrawableCreate(spriteAtlasItem, scale);
    m_drawable = std::unique_ptr<DrawableSpriteI>(std::move(drawable));
}

void SpriteDrawStatic::DrawAt(int x, int y)
{
    EngineProviderI &provider = GetMainEngine()->getProvider();

//    TextureI *texture = m_sprite->GetTexture();
//
//    provider.TextureAlphaSetMod(texture, m_alpha);
//
//    provider.DrawTexture(
//       texture,
//       x,
//       y,
//       m_sprite->GetX(),
//       m_sprite->GetY(),
//       m_sprite->GetWidth(),
//       m_sprite->GetHeight(),
//       m_scale
//    );

    provider.DrawableRender(m_drawable.get(), x, y);
}

void SpriteDrawStatic::SetPosition(Vector2 &pos)
{
    m_position = pos;
}

void SpriteDrawStatic::SetScale(float x)
{
    SpriteDrawI::SetScale(x);
    m_drawable->SetScale(x);
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

static int lua_SpriteDrawStatic_SetAlpha(lua_State *L)
{
    SpriteDrawStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteDrawStatic>(L, 1);
    float x = MAX(0, MIN(1, lua_tonumberx(L, 2, NULL)));
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

static int lua_SpriteDrawStatic_GetSize(lua_State *L)
{
    SpriteDrawStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteDrawStatic>(L, 1);
    Size size = spr->GetSize();
    lua_pushnumber(L, size.width);
    lua_pushnumber(L, size.height);
    return 2;
}

static int lua_SpriteDrawStatic_SetPosition(lua_State *L)
{
    SpriteDrawStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteDrawStatic>(L, 1);
    float x = lua_tonumberx(L, 2, nullptr);
    float y = lua_tonumberx(L, 3, nullptr);
    Vector2 pos = {x, y};
    spr->SetPosition(pos);
    return 0;
}

static int lua_SpriteDrawStatic_GetPosition(lua_State *L)
{
    SpriteDrawStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteDrawStatic>(L, 1);
    Vector2 pos = spr->GetPosition();
    lua_pushnumber(L, pos.x);
    lua_pushnumber(L, pos.y);
    return 2;
}

static int lua_SpriteDrawStatic_DrawAt(lua_State *L)
{
    SpriteDrawStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteDrawStatic>(L, 1);
    float x = lua_tonumberx(L, 2, NULL);
    float y = lua_tonumberx(L, 3, NULL);
    spr->DrawAt(x, y);
    return 0;
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
        {"SetAlpha", &lua_SpriteDrawStatic_SetAlpha},
        {"GetAlpha", &lua_SpriteDrawStatic_GetAlpha},
        {"GetSize", &lua_SpriteDrawStatic_GetSize},
        {"SetPosition", &lua_SpriteDrawStatic_SetPosition},
        {"GetPosition", &lua_SpriteDrawStatic_GetPosition},
        {"DrawAt", &lua_SpriteDrawStatic_DrawAt},
        {"Draw", &lua_SpriteDrawStatic_Draw}
    });
    return result;
}
