//
//  scriptint_engine.cpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#include "common.h"
#include "sprite_interface_defs.h"
#include "scripting_engine.hpp"
#include "room.hpp"
#include "character_manager.hpp"
#include "sprite_atlas_manager.hpp"
#include "sprite_renderer_manager.hpp"
#include "value_animator_factory.hpp"
#include "property_animator_factory.hpp"
#include "time.hpp"
#include "engine_state.hpp"
#include "animation_group_factory.hpp"
#include "font_manager.hpp"

using namespace engine;

/// Main accessor for easy access.
static ScriptingEngine *sharedEngine = NULL;

engine::ScriptingEngine *GetScripting()
{
    return sharedEngine;
}

ScriptingEngine::ScriptingEngine()
{
    sharedEngine = this;
}

void *ScriptingEngine::GetState()
{
    return this->L;
}

void ScriptingEngine::newState()
{
    this->L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_base(L);
}

void ScriptingEngine::closeState()
{
    lua_close(L);
}

void ScriptingEngine::loadFile(FileStreamI *bufferStream)
{
    auto buffer = bufferStream->ReadBufferString();
    const char *str = buffer.c_str();

    if (luaL_loadbufferx(this->L, str, strlen(str), "script", NULL) == 0)
    {
        // Call priming lua_pcall
        int iErr = lua_pcall(L, 0, 0, 0);
        if (iErr != 0)
        {
            std::cout << "Error:" << lua_tostring(L, -1) << "\n";
        }
    }
    else
    {
        std::cout << "Final:" << lua_tostring(L, -1) << "\n";
    }
}

void ScriptingEngine::loadChunk(char *buffer)
{
    size_t tt = strlen(buffer);
    if (luaL_loadbufferx(this->L, (const char*)buffer, /*bufferStream->GetSize()*/tt, "insert", NULL) == 0)
    {
        // Call priming lua_pcall
        int iErr = lua_pcall(L, 0, 0, 0);
        if (iErr != 0)
        {
            std::cout << "Error:" << lua_tostring(L, -1) << "\n";
        }
    }
    else
    {
        std::cout << "Final:" << lua_tostring(L, -1) << "\n";
    }
}

void ScriptingEngine::registerFunctions()
{
    lua_pushcclosure(L, &ScriptingEngine::L_textureLoad, 0);
    lua_setglobal (L, "L_textureLoad");

    lua_pushcclosure(L, &ScriptingEngine::L_unloadTexture, 0);
    lua_setglobal (L, "unloadTexture");

    lua_pushcclosure(L, &ScriptingEngine::L_drawTexture, 0);
    lua_setglobal (L, "drawTexture");

    lua_pushcclosure(L, &ScriptingEngine::L_spriteAtlasLoad, 0);
    lua_setglobal (L, "L_spriteAtlasLoad");

    lua_pushcclosure(L, &ScriptingEngine::L_spriteAtlasGetSprite, 0);
    lua_setglobal (L, "L_spriteAtlasGetSprite");

    lua_pushcclosure(L, &ScriptingEngine::L_spriteDrawStaticCreate, 0);
    lua_setglobal (L, "L_spriteDrawStaticCreate");

    lua_pushcclosure(L, &ScriptingEngine::L_spriteDrawAnimatedCreate, 0);
    lua_setglobal (L, "L_spriteDrawAnimatedCreate");

    lua_pushcclosure(L, &ScriptingEngine::L_spriteDrawRender, 0);
    lua_setglobal (L, "L_spriteDrawRender");


    // Register global objects to be used at the start of the script lifecycle.
    CharacterManager &mgr = GetMainEngine()->getCharacterManager();
    mgr.ScriptingInterfaceRegisterFunctions(L, &mgr);
    lua_setglobal(L, "CharacterManager");

    SceneManager &sceneManager = GetMainEngine()->getSceneManager();
    sceneManager.ScriptingInterfaceRegisterFunctions(L, &sceneManager);
    lua_setglobal(L, "SceneManager");

    SpriteAtlasManager &atlasManager = GetMainEngine()->getAtlasManager();
    atlasManager.ScriptingInterfaceRegisterFunctions(L, &atlasManager);
    lua_setglobal(L, "AtlasManager");

    SpriteRendererManager &spriteRendererManager = GetMainEngine()->getSpriteRendererManager();
    spriteRendererManager.ScriptingInterfaceRegisterFunctions(L, &spriteRendererManager);
    lua_setglobal(L, "SpriteRendererManager");

    Time &time = GetMainEngine()->getTime();
    time.ScriptingInterfaceRegisterFunctions(L, &time);
    lua_setglobal(L, "Time");

    ValueAnimatorFactory &animationFactory = GetMainEngine()->getValueAnimatorFactory();
    animationFactory.ScriptingInterfaceRegisterFunctions(L, &animationFactory);
    lua_setglobal(L, "ValueAnimatorFactory");

    PropertyAnimatorFactory &propertyAnimator = GetMainEngine()->getPropertyAnimatorFactory();
    propertyAnimator.ScriptingInterfaceRegisterFunctions(L, &propertyAnimator);
    lua_setglobal(L, "PropertyAnimatorFactory");

    EngineState &engineState = GetMainEngine()->getEngineState();
    engineState.ScriptingInterfaceRegisterFunctions(L, &engineState);
    lua_setglobal(L, "EngineState");
    
    MemoryReleasePool &releasePool = GetMainEngine()->getReleasePool();
    releasePool.ScriptingInterfaceRegisterFunctions(L, &releasePool);
    lua_setglobal(L, "MemoryReleasePool");
    
    AnimationGroupFactory &animationGroupFactory = GetMainEngine()->getAnimationGroupFactory();
    animationGroupFactory.ScriptingInterfaceRegisterFunctions(L, &animationGroupFactory);
    lua_setglobal(L, "AnimationGroupFactory");

    FontManager &fontManager = GetMainEngine()->getFontManager();
    fontManager.ScriptingInterfaceRegisterFunctions(L, &fontManager);
    lua_setglobal(L, "FontManager");
};

void ScriptingEngine::CallRegistryFunction(int funcRef, std::function<int(lua_State*)> lambda)
{
    if (funcRef <= -1) { return; };

    /* push the callback onto the stack using the Lua reference we */
    /* stored in the registry */
    lua_rawgeti( L, LUA_REGISTRYINDEX, funcRef );

    int paramCount(lambda(L));

    /* call the callback */
    /* NOTE: This is using the one we duplicated with lua_pushvalue */
    if ( 0 != lua_pcall( L, paramCount, 0, 0 ) ) {
        printf("Failed to call the callback!\n %s\n", lua_tostring( L, -1 ) );
        return;
    }
}

void ScriptingEngine::callInit()
{
    lua_getglobal(L, "init");  /* function to be called */
    if (lua_pcall(L, 0, 0, 0) != 0)
    {
        std::cout << "Error:" << lua_tostring(L, -1) << "\n";
    }
}

void ScriptingEngine::callUpdate()
{
    /* push functions and arguments */
    lua_getglobal(L, "update");  /* function to be called */

    /* do the call (2 arguments, 1 result) */
    if (lua_pcall(L, 0, 0, 0) != 0) {
        std::cout << "Error:" << lua_tostring(L, -1) << "\n";
    }
}

/// loadTexture(name)
int ScriptingEngine::L_textureLoad(lua_State *L)
{
    int argc = lua_gettop(L);
    const char *msgX = (char *) lua_tostring (L, argc);

    TextureI *texture = GetMainEngine()->getTextureManager().LoadTexture(msgX);
    lua_pushlightuserdata(L, texture);

    return 1;
}

/// unloadtexture(texture_handle)
int ScriptingEngine::L_unloadTexture(lua_State *L)
{
    int argc = lua_gettop(L);
    TextureI *texturePointer = (TextureI*)lua_topointer(L, argc-0);

    if (texturePointer != NULL)
    {
        GetMainEngine()->getTextureManager().UnloadTexture(texturePointer);
    }

    return 0;
}

/// drawTexture(texture_handle, x, y)
int ScriptingEngine::L_drawTexture(lua_State *L)
{
    // TODO: not used; to be removed
//    int argc = lua_gettop(L);
//    int y = lua_tonumberx(L, argc--, NULL);
//    int x = lua_tonumberx(L, argc--, NULL);
//    TextureI *texturePointer = (TextureI*)lua_topointer(L, argc--);
//
//    if (texturePointer != NULL)
//    {
//        GetMainEngine()->getProvider().DrawTexture(texturePointer, x, y);
//    }
//
    return 0;
}

/// L_spriteAtlasLoad(json_path, texture_path)
int ScriptingEngine::L_spriteAtlasLoad(lua_State *L)
{
    int argc = lua_gettop(L);
    const char *texture_path = (char *) lua_tostring (L, argc--);
    const char *json_path = (char *) lua_tostring (L, argc--);

    SpriteAtlasI *atlas = GetMainEngine()->getAtlasManager().SpriteAtlasLoad(json_path, texture_path);
    lua_pushlightuserdata(L, atlas);

    return 1;
}

/// L_spriteAtlasGetSprite(atlas_handle, sprite_name)
/// returns: sprite_handle
int ScriptingEngine::L_spriteAtlasGetSprite(lua_State *L)
{
    int argc = lua_gettop(L);
    const char *spriteName = (char *) lua_tostring (L, argc--);
    SpriteAtlasI *atlasPointer = (SpriteAtlasI*)lua_topointer(L, argc--);

    if (atlasPointer)
    {
        SpriteAtlasItemI *spriteAtlasItem = atlasPointer->GetItemForName(spriteName);
        if (spriteAtlasItem)
        {
            lua_pushlightuserdata(L, spriteAtlasItem);
            return 1;
        }
    }

    return 0;
}

/// L_spriteDrawCreate(sprite_handle, scale)
int ScriptingEngine::L_spriteDrawStaticCreate(lua_State *L)
{
    int argc = lua_gettop(L);
    SpriteAtlasItemI *spritePointer = (SpriteAtlasItemI*)lua_topointer(L, argc--);

    if (spritePointer)
    {
        SpriteDrawI *sd = GetMainEngine()->getSpriteRendererManager().SpriteDrawLoadStatic(spritePointer);
        if (sd)
        {
            lua_pushlightuserdata(L, sd);
            return 1;
        }
    }

    return 0;
}

/// L_spriteDrawAnimatedCreate(frame_duration_ms, scale, sprite_handle1, ...)
/// returns: sprite_draw_handle
int ScriptingEngine::L_spriteDrawAnimatedCreate(lua_State *L)
{
    int argc = lua_gettop(L);
    std::vector<SpriteAtlasItemI*> sprites;
    int i;

    for (i = 3; i <= argc; i++) {
        SpriteAtlasItemI *spritePointer = (SpriteAtlasItemI*)lua_topointer(L, i);
        sprites.emplace_back(spritePointer);
    }

    int frame_duration_ms = lua_tonumberx(L, 1, NULL);

    SpriteDrawI *sd = GetMainEngine()->getSpriteRendererManager().SpriteDrawLoadAnimated(sprites, frame_duration_ms);
    if (sd)
    {
        lua_pushlightuserdata(L, sd);
        return 1;
    }
    else
    {
        return 0;
    }
}

/// L_spriteDrawRender(sprite_draw_handle, x, y)
int ScriptingEngine::L_spriteDrawRender(lua_State *L)
{
    int argc = lua_gettop(L);
    int y = lua_tonumberx(L, argc--, NULL);
    int x = lua_tonumberx(L, argc--, NULL);
    SpriteDrawI *spriteRender = (SpriteDrawI*)lua_topointer(L, argc--);

    if (spriteRender)
    {
        if (dynamic_cast<SpriteDrawI*>(spriteRender))
        {
            spriteRender->DrawAt(x, y);
        }
    }

    return 0;
}
