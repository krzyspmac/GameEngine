//
//  sprite_draw.cpp
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#include "sprite_representation_static.hpp"
#include "common_engine.h"
#include "common.h"
#include "scripting_engine.hpp"

using namespace engine;

SpriteRepresentationStatic::SpriteRepresentationStatic(SpriteAtlasItemI *spriteAtlasItem)
    : SpriteRepresentationI(1.0f)
    , m_sprite(spriteAtlasItem)
{
    auto drawable = ENGINE().getProvider().DrawableCreate(spriteAtlasItem, 1.f);
    m_drawable = std::unique_ptr<DrawableSpriteI>(std::move(drawable));
}

void SpriteRepresentationStatic::DrawAt(int x, int y)
{
    EngineProviderI &provider = ENGINE().getProvider();
    provider.DrawableRender(m_drawable.get(), this, x, y);
}

void SpriteRepresentationStatic::SetPosition(Vector2 &pos)
{
    m_position = pos;
}

void SpriteRepresentationStatic::SetZPosition(float zPos)
{
    SpriteRepresentationI::SetZPosition(zPos);
    m_drawable->SetZPosition(zPos);
}

void SpriteRepresentationStatic::SetRotation(Rotation rotation)
{
    SpriteRepresentationI::SetRotation(rotation);
    m_drawable->SetRotation(rotation.angle, rotation.anchor.x, rotation.anchor.y);
}

void SpriteRepresentationStatic::SetScale(float x)
{
    SpriteRepresentationI::SetScale(x);
    m_drawable->SetScale(x);
}

void SpriteRepresentationStatic::Draw()
{
    DrawAt(m_position.x, m_position.y);
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(SpriteRepresentationStatic);

static int lua_SpriteDrawStatic_SetScale(lua_State *L)
{
    SpriteRepresentationStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationStatic>(L, 1);
    float scale = lua_tonumberx(L, 2, NULL);
    spr->SetScale(scale);
    return 0;
}

static int lua_SpriteDrawStatic_SetAlpha(lua_State *L)
{
    SpriteRepresentationStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationStatic>(L, 1);
    float x = MAX(0, MIN(1, lua_tonumberx(L, 2, NULL)));
    spr->SetAlpha(x);
    return 0;
}

static int lua_SpriteDrawStatic_GetAlpha(lua_State *L)
{
    SpriteRepresentationStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationStatic>(L, 1);
    float x = spr->GetAlpha();
    lua_pushnumber(L, x);
    return 1;
}

static int lua_SpriteDrawStatic_GetSize(lua_State *L)
{
    SpriteRepresentationStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationStatic>(L, 1);
    Size size = spr->GetSize();
    lua_pushnumber(L, size.width);
    lua_pushnumber(L, size.height);
    return 2;
}

static int lua_SpriteDrawStatic_SetPosition(lua_State *L)
{
    SpriteRepresentationStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationStatic>(L, 1);
    float x = lua_tonumberx(L, 2, nullptr);
    float y = lua_tonumberx(L, 3, nullptr);
    Vector2 pos = {x, y};
    spr->SetPosition(pos);
    return 0;
}

static int lua_SpriteDrawStatic_GetPosition(lua_State *L)
{
    SpriteRepresentationStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationStatic>(L, 1);
    Vector2 pos = spr->GetPosition();
    lua_pushnumber(L, pos.x);
    lua_pushnumber(L, pos.y);
    return 2;
}

static int lua_SpriteDrawStatic_DrawAt(lua_State *L)
{
    SpriteRepresentationStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationStatic>(L, 1);
    float x = lua_tonumberx(L, 2, NULL);
    float y = lua_tonumberx(L, 3, NULL);
    spr->DrawAt(x, y);
    return 0;
}

static int lua_SpriteDrawStatic_Draw(lua_State *L)
{
    SpriteRepresentationStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationStatic>(L, 1);
    spr->Draw();
    return 0;
}

static int lua_SpriteDrawStatic_SetAcceptsLight(lua_State *L)
{
    SpriteRepresentationStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationStatic>(L, 1);
    bool value = lua_toboolean(L, 2);
    spr->SetAcceptsLight(value);
    return 0;
}

static int lua_SpriteDrawStatic_SetType(lua_State *L)
{
    SpriteRepresentationStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationStatic>(L, 1);
    const char* type = lua_tostring(L, 2);

    std::vector<std::string> spriteTypes = { "background", "foreground", "light" };
    for (int i = 0; i < spriteTypes.size(); i++)
    {
        auto val = spriteTypes.at(i);
        if (val.compare(type) == 0)
        {
            spr->GetType() = (SpriteDrawType)i;
        }
    }
    return 0;
}

static int lua_SetColorMod(lua_State *L)
{
    SpriteRepresentationStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationStatic>(L, 1);
    float r = lua_tonumber(L, 2);
    float g = lua_tonumber(L, 3);
    float b = lua_tonumber(L, 4);
    float a = lua_tonumber(L, 5);
    spr->SetColorMod({r, g, b, a});
    return 0;
}

static int lua_setZPosition(lua_State *L)
{
    SpriteRepresentationStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationStatic>(L, 1);
    float value = lua_tonumber(L, 2);
    spr->SetZPosition(value);
    return 0;
}

static int lua_setRotation(lua_State *L)
{
    SpriteRepresentationStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationStatic>(L, 1);
    float value = lua_tonumber(L, 2);
    float vec1 = lua_tonumber(L, 3);
    float vec2 = lua_tonumber(L, 4);
    spr->SetRotation(Rotation(value, Vector2(vec1, vec2)));
    return 0;
}

std::vector<luaL_Reg> SpriteRepresentationStatic::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        {"SetScale", &lua_SpriteDrawStatic_SetScale},
        {"SetAlpha", &lua_SpriteDrawStatic_SetAlpha},
        {"GetAlpha", &lua_SpriteDrawStatic_GetAlpha},
        {"GetSize", &lua_SpriteDrawStatic_GetSize},
        {"SetPosition", &lua_SpriteDrawStatic_SetPosition},
        {"GetPosition", &lua_SpriteDrawStatic_GetPosition},
        {"DrawAt", &lua_SpriteDrawStatic_DrawAt},
        {"Draw", &lua_SpriteDrawStatic_Draw},
        {"SetAcceptsLight", &lua_SpriteDrawStatic_SetAcceptsLight},
        {"SetType", &lua_SpriteDrawStatic_SetType},
        {"SetColorMod", &lua_SetColorMod},
        {"SetZPosition", &lua_setZPosition},
        {"SetRotation", &lua_setRotation}
    });
    return result;
}
