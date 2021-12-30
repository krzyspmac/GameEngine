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

using namespace engine;

ScriptingEngine::ScriptingEngine()
{
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

void ScriptingEngine::loadFile(FileMemoryBufferStreamI *bufferStream)
{
    if (luaL_loadbufferx(this->L, (const char*)bufferStream->GetMemory(), bufferStream->GetSize(), "script", NULL) == 0)
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

    lua_pushcclosure(L, &ScriptingEngine::L_loadFont, 0);
    lua_setglobal (L, "L_loadFont");

    lua_pushcclosure(L, &ScriptingEngine::L_drawText, 0);
    lua_setglobal (L, "drawText");

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
//    *chrMgrPtr = &mgr;
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
};

void ScriptingEngine::RegisterFunctions(void *ptr)
{
    if(ScriptingInterface* si = dynamic_cast<ScriptingInterface*>((ScriptingInterface*)ptr))
    {
        //si.ScriptingInterfaceRegisterFunctions(L, si.ScriptingInterfaceName(), si.ScriptingInterfaceFunctions());
        printf("asd");
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

    TextureI *texture = GetMainEngine()->LoadTexture(msgX);
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
        GetMainEngine()->UnloadTexture(texturePointer);
    }

    return 0;
}

/// drawTexture(texture_handle, x, y)
int ScriptingEngine::L_drawTexture(lua_State *L)
{
    int argc = lua_gettop(L);
    int y = lua_tonumberx(L, argc--, NULL);
    int x = lua_tonumberx(L, argc--, NULL);
    TextureI *texturePointer = (TextureI*)lua_topointer(L, argc--);

    if (texturePointer != NULL)
    {
        GetMainEngine()->getProvider().DrawTexture(texturePointer, x, y);
    }

    return 0;
}

/// L_loadFont(font_name)
/// returns: font_handle
int ScriptingEngine::L_loadFont(lua_State *L)
{
    int argc = lua_gettop(L);
    const char *msgX = (char *) lua_tostring (L, argc);

    FontI *font = GetMainEngine()->LoadFont(msgX);
    lua_pushlightuserdata(L, font);

    return 1;
}

/// drawText(font_handle, x, y, r, g, b, align: "left"|"center"|"right")
int ScriptingEngine::L_drawText(lua_State *L)
{
    int argc = lua_gettop(L);

    const char *alignment = (char *) lua_tostring (L, argc--);
    int b = lua_tonumberx(L, argc--, NULL);
    int g = lua_tonumberx(L, argc--, NULL);
    int r = lua_tonumberx(L, argc--, NULL);

    int y = lua_tonumberx(L, argc--, NULL);
    int x = lua_tonumberx(L, argc--, NULL);

    const char *text = (char *) lua_tostring (L, argc--);
    FontI *fontPointer = (FontI*)lua_topointer(L, argc--);

    if (fontPointer)
    {
        TEXT_ALIGNMENT align = TEXT_ALIGN_LEFT;
        if (strcmp(alignment, "left") == 0)
        {
            align = TEXT_ALIGN_LEFT;
        }
        else if (strcmp(alignment, "center") == 0)
        {
            align = TEXT_ALIGN_CENTER;
        }
        else if (strcmp(alignment, "right") == 0)
        {
            align = TEXT_ALIGN_RIGHT;
        }

        GetMainEngine()->getProvider().DrawText(fontPointer, text, x, y, r, g, b, align);
    }

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
    int scale = lua_tonumberx(L, argc--, NULL);
    SpriteAtlasItemI *spritePointer = (SpriteAtlasItemI*)lua_topointer(L, argc--);

    if (spritePointer)
    {
        SpriteDrawI *sd = GetMainEngine()->getSpriteRendererManager().SpriteDrawLoadStatic(spritePointer, scale);
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
    int scale = lua_tonumberx(L, 2, NULL);

    SpriteDrawI *sd = GetMainEngine()->getSpriteRendererManager().SpriteDrawLoadAnimated(sprites, frame_duration_ms, scale);
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
            spriteRender->Draw(x, y);
        }
    }

    return 0;
}
