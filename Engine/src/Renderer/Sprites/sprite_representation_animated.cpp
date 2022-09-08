//
//  sprite_draw_animated.cpp
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#include "sprite_representation_animated.hpp"
#include "common_engine.h"
#include "engine.hpp"
#include "general.hpp"

using namespace engine;

SpriteRepresentationAnimated::SpriteRepresentationAnimated(std::vector<SpriteAtlasItemI*> sprites, int frameAnimationDurationMs)
    : SpriteRepresentationI(1.0f)
    , m_maxWidth(0)
    , m_maxHeight(0)
    , m_frameAnimationDurationMs(frameAnimationDurationMs)
{
    auto& spriteManager = ENGINE().getSpriteRendererManager();

    for (auto& item : sprites)
    {
        auto* spriteRepresentation = (SpriteRepresentationStatic*)spriteManager.SpriteRepresentationStaticLoad(item);
        m_sprites.emplace_back(spriteRepresentation);
    }
}

SpriteRepresentationAnimated::~SpriteRepresentationAnimated()
{
    auto& spriteManager = ENGINE().getSpriteRendererManager();

    for (auto* item : m_sprites)
    {
        spriteManager.SpriteDrawUnload(item);
    }
}

SpriteRepresentationAnimated *SpriteRepresentationAnimated::CreateFromAtlas(std::vector<std::unique_ptr<SpriteAtlasItemI>>& sprites, int frameAnimationDurationMs)
{
    std::vector<SpriteAtlasItemI*> array;
    for (auto& item : sprites)
    {
        array.emplace_back(item.get());
    }

    return new SpriteRepresentationAnimated(array, frameAnimationDurationMs);
}

void SpriteRepresentationAnimated::SetPosition(Vector2 &pos)
{
    m_position = pos;
}

void SpriteRepresentationAnimated::SetScale(float value)
{
    for (auto& item : m_sprites)
    {
        item->SetScale(value);
    }
}

void SpriteRepresentationAnimated::SetAlpha(float val)
{
    for (auto& item : m_sprites)
    {
        item->SetAlpha(val);
    }
}

void SpriteRepresentationAnimated::PrepareAnimation()
{
}

void SpriteRepresentationAnimated::SetRotation(Rotation rotation)
{
    SpriteRepresentationI::SetRotation(rotation);
    
    for (auto& item : m_sprites)
    {
        item->SetRotation(rotation);
    }
}

void SpriteRepresentationAnimated::SetAcceptsLight(bool val)
{
    for (auto& item : m_sprites)
    {
        item->SetAcceptsLight(val);
    }
}

void SpriteRepresentationAnimated::SetZPosition(float zPos)
{
    for (auto& item : m_sprites)
    {
        item->SetZPosition(zPos);
    }
}

void SpriteRepresentationAnimated::SetAnimationFrameDuration(float value)
{
    m_frameAnimationDurationMs = value;
}

void SpriteRepresentationAnimated::SetColorMod(Color4 val)
{
    for (auto& item : m_sprites)
    {   item->SetColorMod(val);
    }
}

void SpriteRepresentationAnimated::DrawAt(int x, int y)
{
    Uint64 ticks = ENGINE().getProvider().GetTicks();
    Uint64 seconds = ticks / m_frameAnimationDurationMs;
    Uint64 spriteNo = seconds % m_sprites.size();
    SpriteRepresentationI *spriteItem = m_sprites.at(spriteNo);
    spriteItem->DrawAt(x, y);
}

void SpriteRepresentationAnimated::Draw()
{
    DrawAt(m_position.x, m_position.y);
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(SpriteRepresentationAnimated);

static int lua_SpriteDrawStatic_SetScale(lua_State *L)
{
    SpriteRepresentationAnimated *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationAnimated>(L, 1);
    float scale = lua_tonumberx(L, 2, NULL);
    spr->SetScale(scale);
    return 0;
}

static int lua_SpriteDrawStatic_SetAlpha(lua_State *L)
{
    SpriteRepresentationAnimated *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationAnimated>(L, 1);
    float x = MAX(0, MIN(1, lua_tonumberx(L, 2, NULL)));
    spr->SetAlpha(x);
    return 0;
}

static int lua_SpriteDrawStatic_GetAlpha(lua_State *L)
{
    SpriteRepresentationAnimated *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationAnimated>(L, 1);
    float x = spr->GetAlpha();
    lua_pushnumber(L, x);
    return 1;
}

static int lua_SpriteDrawStatic_SetPosition(lua_State *L)
{
    SpriteRepresentationAnimated *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationAnimated>(L, 1);
    float x = lua_tonumberx(L, 2, nullptr);
    float y = lua_tonumberx(L, 3, nullptr);
    Vector2 pos = {x, y};
    spr->SetPosition(pos);
    return 0;
}

static int lua_SpriteDrawStatic_GetPosition(lua_State *L)
{
    SpriteRepresentationAnimated *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationAnimated>(L, 1);
    Vector2 pos = spr->GetPosition();
    lua_pushnumber(L, pos.x);
    lua_pushnumber(L, pos.y);
    return 2;
}

static int lua_SpriteDrawStatic_SetAcceptsLight(lua_State *L)
{
    SpriteRepresentationAnimated *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationAnimated>(L, 1);
    bool value = lua_toboolean(L, 2);
    spr->SetAcceptsLight(value);
    return 0;
}

static int lua_SpriteDrawStatic_SetType(lua_State *L)
{
    SpriteRepresentationAnimated *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationAnimated>(L, 1);
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

static int lua_SpriteDrawStatic_SetAnimationFrameDuration(lua_State *L)
{
    SpriteRepresentationAnimated *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationAnimated>(L, 1);
    spr->SetAnimationFrameDuration(lua_tonumber(L, 2));
    return 0;
}

static int lua_SpriteDrawStatic_SetColorMod(lua_State *L)
{
    SpriteRepresentationAnimated *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationAnimated>(L, 1);
    float r = lua_tonumber(L, 2);
    float g = lua_tonumber(L, 3);
    float b = lua_tonumber(L, 4);
    float a = lua_tonumber(L, 5);
    spr->SetColorMod({r, g, b, a});
    return 0;
}

static int lua_SpriteDrawStatic_SetZPosition(lua_State *L)
{
    SpriteRepresentationAnimated *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationAnimated>(L, 1);
    float value = lua_tonumber(L, 2);
    spr->SetZPosition(value);
    return 0;
}

static int lua_SpriteDrawStatic_SetRotation(lua_State *L)
{
    SpriteRepresentationAnimated *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationAnimated>(L, 1);
    float value = lua_tonumber(L, 2);
    float vec1 = lua_tonumber(L, 3);
    float vec2 = lua_tonumber(L, 4);
    spr->SetRotation(Rotation(DEG2RAD(value), Vector2(vec1, vec2)));
    return 0;
}

static int lua_SpriteDrawStatic_GetRotation(lua_State *L)
{
    SpriteRepresentationAnimated *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteRepresentationAnimated>(L, 1);
    auto &rotation = spr->GetRotation();
    lua_pushnumber(L, RAD2DEG(rotation.angle));
    lua_pushnumber(L, rotation.anchor.x);
    lua_pushnumber(L, rotation.anchor.y);
    return 3;
}

std::vector<luaL_Reg> SpriteRepresentationAnimated::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "SetScale", &lua_SpriteDrawStatic_SetScale }
      , { "SetAlpha", &lua_SpriteDrawStatic_SetAlpha }
      , { "GetAlpha", &lua_SpriteDrawStatic_GetAlpha }
      , { "SetPosition", &lua_SpriteDrawStatic_SetPosition }
      , { "GetPosition", &lua_SpriteDrawStatic_GetPosition }
      , { "SetAcceptsLight", &lua_SpriteDrawStatic_SetAcceptsLight }
      , { "SetType", &lua_SpriteDrawStatic_SetType }
      , { "SetAnimationFrameDuration", &lua_SpriteDrawStatic_SetAnimationFrameDuration }
      , { "SetColorMod", &lua_SpriteDrawStatic_SetColorMod }
      , { "SetZPosition", &lua_SpriteDrawStatic_SetZPosition }
      , { "SetRotation", &lua_SpriteDrawStatic_SetRotation }
      , { "GetRotation", &lua_SpriteDrawStatic_GetRotation }
    });
    return result;
}
