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
#include "events_manager.hpp"
#include "light_manager.hpp"
#include "sound_manager.hpp"
#include "engine_screen.hpp"

using namespace engine;

/// Main accessor for easy access.
static ScriptingEngine *sharedEngine = NULL;

/// Main function loader
int PictureModuleLoader(lua_State *L);

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
    registerModuleSearcher();
}

void ScriptingEngine::registerModuleSearcher()
{
    lua_register(L, "pictel_searcher", PictureModuleLoader);
    std::string str;
    str += "table.insert(package.searchers, 2, pictel_searcher) \n";
    luaL_dostring(L, str.c_str());
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
    CharacterManager &mgr = ENGINE().getCharacterManager();
    mgr.ScriptingInterfaceRegisterFunctions(L, &mgr);
    lua_setglobal(L, "CharacterManager");

    SceneManager &sceneManager = ENGINE().getSceneManager();
    sceneManager.ScriptingInterfaceRegisterFunctions(L, &sceneManager);
    lua_setglobal(L, "SceneManager");

//    SpriteAtlasManager &atlasManager = ENGINE().getAtlasManager();
//    atlasManager.ScriptingInterfaceRegisterFunctions(L, &atlasManager);
//    lua_setglobal(L, "AtlasManager");

    SpriteRendererManager &spriteRendererManager = ENGINE().getSpriteRendererManager();
    spriteRendererManager.ScriptingInterfaceRegisterFunctions(L, &spriteRendererManager);
    lua_setglobal(L, "SpriteRendererManager");

//    Time &time = ENGINE().getTime();
//    time.ScriptingInterfaceRegisterFunctions(L, &time);
//    lua_setglobal(L, "Time");

    ValueAnimatorFactory &animationFactory = ENGINE().getValueAnimatorFactory();
    animationFactory.ScriptingInterfaceRegisterFunctions(L, &animationFactory);
    lua_setglobal(L, "ValueAnimatorFactory");

    PropertyAnimatorFactory &propertyAnimator = ENGINE().getPropertyAnimatorFactory();
    propertyAnimator.ScriptingInterfaceRegisterFunctions(L, &propertyAnimator);
    lua_setglobal(L, "PropertyAnimatorFactory");

//    EngineState &engineState = ENGINE().getEngineState();
//    engineState.ScriptingInterfaceRegisterFunctions(L, &engineState);
//    lua_setglobal(L, "EngineState");
    
    MemoryReleasePool &releasePool = ENGINE().getReleasePool();
    releasePool.ScriptingInterfaceRegisterFunctions(L, &releasePool);
    lua_setglobal(L, "MemoryReleasePool");
    
    AnimationGroupFactory &animationGroupFactory = ENGINE().getAnimationGroupFactory();
    animationGroupFactory.ScriptingInterfaceRegisterFunctions(L, &animationGroupFactory);
    lua_setglobal(L, "AnimationGroupFactory");

//    FontManager &fontManager = ENGINE().getFontManager();
//    fontManager.ScriptingInterfaceRegisterFunctions(L, &fontManager);
//    lua_setglobal(L, "FontManager");

    EventsManager &eventsManager = ENGINE().getEventsManager();
    eventsManager.ScriptingInterfaceRegisterFunctions(L, &eventsManager);
    lua_setglobal(L, "EventsManager");

    LightManager &lightManager = ENGINE().getLightMnaager();
    lightManager.ScriptingInterfaceRegisterFunctions(L, &lightManager);
    lua_setglobal(L, "LightManager");

    SoundManager &soundManager = ENGINE().getSoundManager();
    soundManager.ScriptingInterfaceRegisterFunctions(L, &soundManager);
    lua_setglobal(L, "SoundManager");

    EngineScreen &engineScreen = ENGINE().getEngineScreen();
    engineScreen.ScriptingInterfaceRegisterFunctions(L, &engineScreen);
    lua_setglobal(L, "EngineScreen");
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
//    lua_getglobal(L, "init");  /* function to be called */
//    if (lua_pcall(L, 0, 0, 0) != 0)
//    {
//        std::cout << "Error:" << lua_tostring(L, -1) << "\n";
//    }

    auto initFunction = ENGINE().GetEngineSetup().initFunction;
    if (initFunction == nullptr)
    {
        std::cout << "Error: No init function setup. Cannot start engine." << std::endl;
    }
    else
    {
        initFunction();
    }
}

void ScriptingEngine::callUpdate()
{
//    /* push functions and arguments */
//    lua_getglobal(L, "update");  /* function to be called */
//
//    /* do the call (2 arguments, 1 result) */
//    if (lua_pcall(L, 0, 0, 0) != 0) {
//        std::cout << "Error:" << lua_tostring(L, -1) << "\n";
//    }
//
    ENGINE().GetEngineSetup().frameUpdateFunction();
}

/// loadTexture(name)
int ScriptingEngine::L_textureLoad(lua_State *L)
{
    int argc = lua_gettop(L);
    const char *msgX = (char *) lua_tostring (L, argc);

    TextureI *texture = ENGINE().getTextureManager().LoadTexture(msgX);
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
        ENGINE().getTextureManager().UnloadTexture(texturePointer);
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
//        ENGINE().getProvider().DrawTexture(texturePointer, x, y);
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

    SpriteAtlasI *atlas = ENGINE().getAtlasManager().SpriteAtlasLoad(json_path, texture_path);
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
        SpriteRepresentationI *sd = ENGINE().getSpriteRendererManager().SpriteRepresentationStaticLoad(spritePointer);
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

    SpriteRepresentationI *sd = ENGINE().getSpriteRendererManager().SpriteRepresentationAnimatedLoad(frame_duration_ms, sprites);
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
    SpriteRepresentationI *spriteRender = (SpriteRepresentationI*)lua_topointer(L, argc--);

    if (spriteRender)
    {
        if (dynamic_cast<SpriteRepresentationI*>(spriteRender))
        {
            spriteRender->DrawAt(x, y);
        }
    }

    return 0;
}

int PictureModuleLoader(lua_State *L){
    std::string filename = lua_tostring(L, 1);
    filename += ".lua";

    auto  access = ENGINE().getFileAccess().GetAccess(filename);
    auto buffer = access->ReadBufferString();
    auto* str = buffer.c_str();

    if (luaL_loadbufferx(L, str, strlen(str), filename.c_str(), NULL) == 0)
    {
        // no priming needed as LUA will call the initialization function itself
        return 1;
    }
    else
    {   std::cout << "Final:" << lua_tostring(L, -1) << "\n";
        ENGINE().getConsoleRenderer().GetLogger().Log("Could not load %s module!", filename.c_str());
        return 0;
    }
}
