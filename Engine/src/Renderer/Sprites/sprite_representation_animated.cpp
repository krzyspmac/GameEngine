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

SpriteDrawAnimated::SpriteDrawAnimated(std::vector<SpriteAtlasItemI*> sprites, int frameAnimationDurationMs)
    : SpriteRepresetationI(1.0f)
    , m_maxWidth(0)
    , m_maxHeight(0)
    , m_frameAnimationDurationMs(frameAnimationDurationMs)
{
    auto& spriteManager = GetMainEngine()->getSpriteRendererManager();

    for (auto& item : sprites)
    {
        auto* spriteRepresentation = (SpriteRepresentationStatic*)spriteManager.SpriteRepresentationStaticLoad(item);
        m_sprites.emplace_back(spriteRepresentation);
    }
}

SpriteDrawAnimated::~SpriteDrawAnimated()
{
    auto& spriteManager = GetMainEngine()->getSpriteRendererManager();

    for (auto* item : m_sprites)
    {
        spriteManager.SpriteDrawUnload(item);
    }
}

SpriteDrawAnimated *SpriteDrawAnimated::CreateFromAtlas(std::vector<std::unique_ptr<SpriteAtlasItemI>>& sprites, int frameAnimationDurationMs)
{
    std::vector<SpriteAtlasItemI*> array;
    for (auto& item : sprites)
    {
        array.emplace_back(item.get());
    }

    return new SpriteDrawAnimated(array, frameAnimationDurationMs);
}

void SpriteDrawAnimated::SetPosition(Vector2 &pos)
{
    m_position = pos;
}

void SpriteDrawAnimated::SetScale(float value)
{
    for (auto& item : m_sprites)
    {
        item->SetScale(value);
    }
}

void SpriteDrawAnimated::SetAlpha(float val)
{
    for (auto& item : m_sprites)
    {
        item->SetAlpha(val);
    }
}

void SpriteDrawAnimated::PrepareAnimation()
{
}

void SpriteDrawAnimated::DrawAt(int x, int y)
{
    Uint64 ticks = GetMainEngine()->getProvider().GetTicks();
    Uint64 seconds = ticks / m_frameAnimationDurationMs;
    Uint64 spriteNo = seconds % m_sprites.size();
    SpriteRepresetationI *spriteItem = m_sprites.at(spriteNo);

    spriteItem->DrawAt(x, y);
//
//    GetMainEngine()->getProvider().DrawTexture(
//       spriteItem->GetTexture(),
//        x + ceil(m_scale *((m_maxWidth - spriteItem->GetWidth())/2)),
//        y + ceil(m_scale *((m_maxHeight - spriteItem->GetHeight())/2)),
//        spriteItem->GetX(),
//        spriteItem->GetY(),
//        spriteItem->GetWidth(),
//        spriteItem->GetHeight(),
//        m_scale
//    );
}

void SpriteDrawAnimated::Draw()
{
    DrawAt(m_position.x, m_position.y);
}

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(SpriteDrawAnimated);

static int lua_SpriteDrawStatic_SetScale(lua_State *L)
{
    SpriteDrawAnimated *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteDrawAnimated>(L, 1);
    float scale = lua_tonumberx(L, 2, NULL);
    spr->SetScale(scale);
    return 0;
}

static int lua_SpriteDrawStatic_SetAlpha(lua_State *L)
{
    SpriteDrawAnimated *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteDrawAnimated>(L, 1);
    float x = MAX(0, MIN(1, lua_tonumberx(L, 2, NULL)));
    spr->SetAlpha(x);
    return 0;
}

static int lua_SpriteDrawStatic_GetAlpha(lua_State *L)
{
    SpriteDrawAnimated *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteDrawAnimated>(L, 1);
    float x = spr->GetAlpha();
    lua_pushnumber(L, x);
    return 1;
}

static int lua_SpriteDrawStatic_SetPosition(lua_State *L)
{
    SpriteDrawAnimated *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteDrawAnimated>(L, 1);
    float x = lua_tonumberx(L, 2, nullptr);
    float y = lua_tonumberx(L, 3, nullptr);
    Vector2 pos = {x, y};
    spr->SetPosition(pos);
    return 0;
}

static int lua_SpriteDrawStatic_GetPosition(lua_State *L)
{
    SpriteDrawAnimated *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteDrawAnimated>(L, 1);
    Vector2 pos = spr->GetPosition();
    lua_pushnumber(L, pos.x);
    lua_pushnumber(L, pos.y);
    return 2;
}

std::vector<luaL_Reg> SpriteDrawAnimated::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "SetScale", &lua_SpriteDrawStatic_SetScale }
      , { "SetAlpha", &lua_SpriteDrawStatic_SetAlpha }
      , { "GetAlpha", &lua_SpriteDrawStatic_GetAlpha }
      , { "SetPosition", &lua_SpriteDrawStatic_SetPosition }
      , { "GetPosition", &lua_SpriteDrawStatic_GetPosition }
    });
    return result;
}
