//
//  sprite_representation_text.cpp
//  Engine
//
//  Created by krzysp on 13/02/2022.
//

#include "sprite_representation_text.hpp"

using namespace engine;

SpriteRepresentationText::SpriteRepresentationText(FontI *font)
    : SpriteRepresentationI(1.f)
    , m_bitmapFont(font)
    , m_shadowOffset({0.f, 0.f})
    , m_shadowColor({0.f, 0.f, 0.f, 0.f})
{
}

void SpriteRepresentationText::SetText(std::string value)
{
    m_text = value;
}

void SpriteRepresentationText::SetScale(float x)
{
    SpriteRepresentationI::SetScale(x);
    m_bitmapFont->SetScale(x);
}

void SpriteRepresentationText::SetPosition(Vector2 pos)
{
    SpriteRepresentationI::SetPosition(pos);
}

void SpriteRepresentationText::SetAlpha(float val)
{
    SpriteRepresentationI::SetAlpha(val);
}

void SpriteRepresentationText::SetAcceptsLight(bool val)
{
    SpriteRepresentationI::SetAcceptsLight(val);
}

void SpriteRepresentationText::DrawAt(int x, int y)
{
    m_bitmapFont->DrawAt(m_text, x, y, 1, 1, 1, 1, TEXT_ALIGN_LEFT);
}

void SpriteRepresentationText::Draw()
{
    DrawAt(m_position.x, m_position.y);
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(SpriteRepresentationText);

static int lua_SetText(lua_State *L)
{
    SpriteRepresentationText *obj = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationText>(L, 1);
    std::string text = lua_tostring(L, 2);
    obj->SetText(text);
    return 0;
}

static int lua_SetScale(lua_State *L)
{
    SpriteRepresentationText *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationText>(L, 1);
    float scale = lua_tonumberx(L, 2, NULL);
    spr->SetScale(scale);
    return 0;
}

static int lua_SetAlpha(lua_State *L)
{
    SpriteRepresentationText *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationText>(L, 1);
    float x = MAX(0, MIN(1, lua_tonumberx(L, 2, NULL)));
    spr->SetAlpha(x);
    return 0;
}

static int lua_GetAlpha(lua_State *L)
{
    SpriteRepresentationText *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationText>(L, 1);
    float x = spr->GetAlpha();
    lua_pushnumber(L, x);
    return 1;
}

static int lua_SetPosition(lua_State *L)
{
    SpriteRepresentationText *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationText>(L, 1);
    float x = lua_tonumberx(L, 2, nullptr);
    float y = lua_tonumberx(L, 3, nullptr);
    Vector2 pos = {x, y};
    spr->SetPosition(pos);
    return 0;
}

static int lua_GetPosition(lua_State *L)
{
    SpriteRepresentationText *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationText>(L, 1);
    Vector2 pos = spr->GetPosition();
    lua_pushnumber(L, pos.x);
    lua_pushnumber(L, pos.y);
    return 2;
}

static int lua_SetAcceptsLight(lua_State *L)
{
    SpriteRepresentationText *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationText>(L, 1);
    bool value = lua_toboolean(L, 2);
    spr->SetAcceptsLight(value);
    return 0;
}

std::vector<luaL_Reg> SpriteRepresentationText::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "SetText", &lua_SetText }
      , { "SetScale", &lua_SetScale }
      , { "SetAlpha", &lua_SetAlpha }
      , { "GetAlpha", &lua_GetAlpha }
      , { "SetPosition", &lua_SetPosition }
      , { "GetPosition", &lua_GetPosition }
      , { "SetAcceptsLight", &lua_SetAcceptsLight }
    });
    return result;
}
