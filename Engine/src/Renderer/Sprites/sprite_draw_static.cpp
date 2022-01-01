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

int ref_t = -1;

void call_callback( lua_State *L ) {
    if (ref_t <= -1) { return; };

  /* push the callback onto the stack using the Lua reference we */
  /*  stored in the registry */
  lua_rawgeti( L, LUA_REGISTRYINDEX, ref_t );

  /* duplicate the value on the stack */
  /* NOTE: This is unnecessary, but it shows how you keep the */
  /*  callback for later */
  //lua_pushvalue( L, 1 );

  /* call the callback */
  /* NOTE: This is using the one we duplicated with lua_pushvalue */
  if ( 0 != lua_pcall( L, 0, 0, 0 ) ) {
    printf("Failed to call the callback!\n %s\n", lua_tostring( L, -1 ) );
    return;
  }

  /* get a new reference to the Lua function and store it again */
  /* NOTE: This is only used in conjunction with the lua_pushvalue */
  /*  above and can be removed if you remove that */
  ref_t = luaL_ref( L, LUA_REGISTRYINDEX );
}


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
    DrawAt(m_position.x, m_position.y);
    ScriptingEngine &se = (ScriptingEngine&)GetMainEngine()->getScripting();
    call_callback( se.GetL() );
}

void SpriteDrawStatic::GetFunction()
{

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

static int lua_SpriteDrawStatic_Function(lua_State *L)
{
    int arg_count = lua_gettop(L);
    SpriteDrawStatic *spr = ScriptingEngineI::GetScriptingObjectPtr<SpriteDrawStatic>(L, 1);

//    decContext *dc = (decContext *)lua_newuserdata(L, sizeof(decContext));
//    luaL_getmetatable (L, dn_context_meta);

//    int ref = luaL_ref(L, 2);
//    ref_t = ref;
//
    /* store the reference to the Lua function in a variable to be used later */
    ref_t = luaL_ref( L, LUA_REGISTRYINDEX );

//    lua_State *S = lua_tothread(L, 2);
//    const void *p = lua_topointer(L, 2);

//    int pp = lua_rawgeti(L, 2, 1);
//    lua_rawgetp
//    int p = lua_getmetatable(L, 2);
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
        {"Draw", &lua_SpriteDrawStatic_Draw},
        {"Function", &lua_SpriteDrawStatic_Function}
    });
    return result;
}
