//
//  scriptint_engine.cpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#include "common.h"
#include "scripting_engine.hpp"

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

void ScriptingEngine::loadFile(std::string fname)
{
    if(luaL_loadfile(this->L, fname.c_str()) == 0)
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
    lua_pushcclosure(L, &ScriptingEngine::lua_textureLoad, 0);
    lua_setglobal (L, "L_textureLoad");

    lua_pushcclosure(L, &ScriptingEngine::lua_unloadTexture, 0);
    lua_setglobal (L, "unloadTexture");

    lua_pushcclosure(L, &ScriptingEngine::lua_loadFont, 0);
    lua_setglobal (L, "loadFont");

    lua_pushcclosure(L, &ScriptingEngine::lua_drawText, 0);
    lua_setglobal (L, "drawText");

    lua_pushcclosure(L, &ScriptingEngine::lua_drawTexture, 0);
    lua_setglobal (L, "drawTexture");

    lua_pushcclosure(L, &ScriptingEngine::lua_spriteLoad, 0);
    lua_setglobal (L, "L_spriteLoad");

    lua_pushcclosure(L, &ScriptingEngine::lua_spriteDraw, 0);
    lua_setglobal (L, "L_spriteDraw");

    lua_pushcclosure(L, &ScriptingEngine::lua_spriteDrawAnimated, 0);
    lua_setglobal (L, "L_spriteDrawAnimated");
};

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
int ScriptingEngine::lua_textureLoad(lua_State *L)
{
    int argc = lua_gettop(L);
    const char *msgX = (char *) lua_tostring (L, argc);

    std::string path = GetMainEngine()->getFileAccess().getBundledFilepath(msgX);
    TextureI *texture = GetMainEngine()->LoadTexture(path);
    lua_pushlightuserdata(L, texture);

    return 1;
}

/// unloadtexture(texture_handle)
int ScriptingEngine::lua_unloadTexture(lua_State *L)
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
int ScriptingEngine::lua_drawTexture(lua_State *L)
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

/// loadFont(font_name)
/// returns: font_handle
int ScriptingEngine::lua_loadFont(lua_State *L)
{
    int argc = lua_gettop(L);
    const char *msgX = (char *) lua_tostring (L, argc);

    FontI *font = GetMainEngine()->LoadFont(msgX);
    lua_pushlightuserdata(L, font);

    return 1;
}

/// drawText(font_handle, x, y, r, g, b, align: "left"|"center"|"right")
int ScriptingEngine::lua_drawText(lua_State *L)
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

        GetMainEngine()->DrawText(fontPointer, text, x, y, r, g, b, align);
    }

    return 0;
}

/// L_spriteLoad(texture_handle, sprite_width, sprite_height, frame_count, frame_duration_ms)
/// returns: sprite_handle
int ScriptingEngine::lua_spriteLoad(lua_State *L)
{
    int argc = lua_gettop(L);
    int frame_duration_ms = lua_tonumberx(L, argc--, NULL);
    int frame_count = lua_tonumberx(L, argc--, NULL);
    int sprite_height = lua_tonumberx(L, argc--, NULL);
    int sprite_width = lua_tonumberx(L, argc--, NULL);
    TextureI *texturePointer = (TextureI*)lua_topointer(L, argc--);

    if (texturePointer)
    {
        SpriteDescriptor descriptor;
        descriptor.spriteWidth = sprite_width;
        descriptor.spriteHeight = sprite_height;
        descriptor.frameCount = frame_count;
        descriptor.frameDuration = frame_duration_ms;

        SpriteI *sprite = GetMainEngine()->LoadSprite(texturePointer, descriptor);
        lua_pushlightuserdata(L, sprite);
        return 1;
    }
    else
    {
        return 0;
    }
}

/// L_spriteDraw(sprite_handle, x, y, frame_number)
int ScriptingEngine::lua_spriteDraw(lua_State *L)
{
    int argc = lua_gettop(L);
    int frame_number = lua_tonumberx(L, argc--, NULL);
    int y = lua_tonumberx(L, argc--, NULL);
    int x = lua_tonumberx(L, argc--, NULL);
    SpriteI *spritePointer = (SpriteI*)lua_topointer(L, argc--);

    if (spritePointer)
    {
        spritePointer->Draw(x, y, frame_number);
    }

    return 0;
}

/// L_spriteDrawAnimated(sprite_handle, x, y)
int ScriptingEngine::lua_spriteDrawAnimated(lua_State *L)
{
    int argc = lua_gettop(L);
    int y = lua_tonumberx(L, argc--, NULL);
    int x = lua_tonumberx(L, argc--, NULL);
    SpriteI *spritePointer = (SpriteI*)lua_topointer(L, argc--);

    if (spritePointer)
    {
        spritePointer->DrawAnimated(x, y);
    }

    return 0;
}
