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
    , m_shadowOffset({1.f, 1.f})
    , m_shadowColor({0.f, 0.f, 0.f, 0.f})
    , m_lineMultiplier(1.f)
    , m_textHorizontalAlignment(TEXT_ALIGN_LEFT)
    , m_textVerticalAlignment(TEXT_ALIGN_TOP)
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
    m_bitmapFont->SetAlpha(val);
}

void SpriteRepresentationText::SetZPosition(float zPos)
{
    m_bitmapFont->SetZPosition(zPos);
}

void SpriteRepresentationText::SetRotation(Rotation)
{
    // do nothing
}

void SpriteRepresentationText::SetAcceptsLight(bool val)
{
    SpriteRepresentationI::SetAcceptsLight(val);
}

void SpriteRepresentationText::SetColorMod(Color4 val)
{
    SpriteRepresentationI::SetColorMod(val);
}

void SpriteRepresentationText::SetShadowColor(Color4 val)
{
    m_shadowColor = val;
}

void SpriteRepresentationText::SetShadowOffset(OriginF val)
{
    m_shadowOffset = val;
}

void SpriteRepresentationText::SetLineHeightMultiplier(float lineMultiplier)
{
    m_lineMultiplier = lineMultiplier;
}

void SpriteRepresentationText::SetHorizontalAlignment(std::string stringValue)
{
    typedef struct { std::string name; TEXT_HORIZONTAL_ALIGNMENT value; } AlignmentInfo;
    static AlignmentInfo values[] =
    {
        {"left", TEXT_ALIGN_LEFT}
      , {"center", TEXT_ALIGN_CENTER}
      , {"right", TEXT_ALIGN_RIGHT}
    };

    for(auto& v : values)
    {   if (v.name.compare(stringValue) == 0)
        {   m_textHorizontalAlignment = v.value;
            break;
        }
    }
}

void SpriteRepresentationText::SetVerticalAlignment(std::string stringValue)
{
    typedef struct { std::string name; TEXT_VERTICAL_ALIGNMENT value; } AlignmentInfo;
    static AlignmentInfo values[] =
    {
        {"top", TEXT_ALIGN_TOP}
      , {"middle", TEXT_ALIGN_MIDDLE}
      , {"bottom", TEXT_ALIGN_BOTTOM}
    };

    for(auto& v : values)
    {   if (v.name.compare(stringValue) == 0)
        {   m_textVerticalAlignment = v.value;
            break;
        }
    }
}

void SpriteRepresentationText::DrawAt(int x, int y)
{
    if (m_shadowColor.a > 0.f)
    {
        m_bitmapFont->DrawAt(m_text, x + m_shadowOffset.x, y + m_shadowOffset.x, 1, 1, 1, 1, m_textHorizontalAlignment, m_textVerticalAlignment , m_shadowColor, m_lineMultiplier);
    }
    m_bitmapFont->DrawAt(m_text, x, y, 1, 1, 1, 1, m_textHorizontalAlignment, m_textVerticalAlignment, GetColorMod(), m_lineMultiplier);
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

static int lua_GetText(lua_State *L)
{
    SpriteRepresentationText *obj = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationText>(L, 1);
    std::string text = obj->GetText();
    lua_pushstring(L, text.c_str());
    return 1;
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

static int lua_SetColorMod(lua_State *L)
{
    SpriteRepresentationText *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationText>(L, 1);
    float r = lua_tonumber(L, 2);
    float g = lua_tonumber(L, 3);
    float b = lua_tonumber(L, 4);
    float a = lua_tonumber(L, 5);
    spr->SetColorMod({r, g, b, a});
    return 0;
}

static int lua_SetShadowColor(lua_State *L)
{
    SpriteRepresentationText *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationText>(L, 1);
    float r = lua_tonumber(L, 2);
    float g = lua_tonumber(L, 3);
    float b = lua_tonumber(L, 4);
    float a = lua_tonumber(L, 5);
    spr->SetShadowColor({r, g, b, a});
    return 0;
}

static int lua_SetShadowOffset(lua_State *L)
{
    SpriteRepresentationText *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationText>(L, 1);
    float x = lua_tonumber(L, 2);
    float y = lua_tonumber(L, 3);
    spr->SetShadowOffset({x, y});
    return 0;
}

static int lua_SetLineHeightMultiplier(lua_State *L)
{
    SpriteRepresentationText *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationText>(L, 1);
    float value = lua_tonumber(L, 2);
    spr->SetLineHeightMultiplier(value);
    return 0;
}

static int lua_SetHorizontalAlignment(lua_State *L)
{
    SpriteRepresentationText *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationText>(L, 1);
    std::string value = lua_tostring(L, 2);
    spr->SetHorizontalAlignment(value);
    return 0;
}

static int lua_SetVerticalAlignment(lua_State *L)
{
    SpriteRepresentationText *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationText>(L, 1);
    std::string value = lua_tostring(L, 2);
    spr->SetVerticalAlignment(value);
    return 0;
}

static int lua_SetZPosition(lua_State *L)
{
    SpriteRepresentationText *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationText>(L, 1);
    float value = lua_tonumber(L, 2);
    spr->SetZPosition(value);
    return 0;
}

std::vector<luaL_Reg> SpriteRepresentationText::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "SetText", &lua_SetText }
      , { "GetText", &lua_GetText }
      , { "SetScale", &lua_SetScale }
      , { "SetAlpha", &lua_SetAlpha }
      , { "GetAlpha", &lua_GetAlpha }
      , { "SetPosition", &lua_SetPosition }
      , { "GetPosition", &lua_GetPosition }
      , { "SetAcceptsLight", &lua_SetAcceptsLight }
      , { "SetColorMod", &lua_SetColorMod }
      , { "SetShadowColor", &lua_SetShadowColor }
      , { "SetShadowOffset", &lua_SetShadowOffset }
      , { "SetLineHeightMultiplier", &lua_SetLineHeightMultiplier }
      , { "SetHorizontalAlignment", &lua_SetHorizontalAlignment }
      , { "SetVerticalAlignment", &lua_SetVerticalAlignment }
      , { "SetZPosition", &lua_SetZPosition }
    });
    return result;
}
