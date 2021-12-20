//
//  scriptint_engine.cpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#include "common.h"
#include "scripting_engine.hpp"

static engine::EngineI *m_curEngine = NULL;

namespace engine
{

ScriptingEngine::ScriptingEngine()
{
}

void ScriptingEngine::setEngine(EngineI *engine)
{
    m_engine = engine;
    m_curEngine = m_engine;
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
    lua_pushcclosure(L, &ScriptingEngine::lua_loadTexture, 0);
    lua_setglobal (L, "loadTexture");

    lua_pushcclosure(L, &ScriptingEngine::lua_unloadTexture, 0);
    lua_setglobal (L, "unloadTexture");

    lua_pushcclosure(L, &ScriptingEngine::lua_loadFont, 0);
    lua_setglobal (L, "loadFont");

    lua_pushcclosure(L, &ScriptingEngine::lua_drawText, 0);
    lua_setglobal (L, "drawText");

    lua_pushcclosure(L, &ScriptingEngine::lua_drawTexture, 0);
    lua_setglobal (L, "drawTexture");
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
int ScriptingEngine::lua_loadTexture(lua_State *L)
{
    int argc = lua_gettop(L);
    const char *msgX = (char *) lua_tostring (L, argc);

    std::string path = m_curEngine->getFileAccess().getBundledFilepath(msgX);
    TextureI *texture = m_curEngine->LoadTexture(path);
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
        m_curEngine->UnloadTexture(texturePointer);
    }

    return 0;
}

/// drawTexture(texture_handle, x, y)
int ScriptingEngine::lua_drawTexture(lua_State *L)
{
    int argc = lua_gettop(L);
    int y = lua_tonumberx(L, argc-0, NULL);
    int x = lua_tonumberx(L, argc-1, NULL);
    TextureI *texturePointer = (TextureI*)lua_topointer(L, argc-2);

    if (texturePointer != NULL)
    {
        m_curEngine->getProvider().DrawTexture(texturePointer, x, y);
    }

    return 0;
}

/// loadFont(font_name)
/// returns: font_handle
int ScriptingEngine::lua_loadFont(lua_State *L)
{
    int argc = lua_gettop(L);
    const char *msgX = (char *) lua_tostring (L, argc);

    FontI *font = m_curEngine->LoadFont(msgX);
    lua_pushlightuserdata(L, font);

    return 1;
}

/// drawText(font_handle, x, y, r, g, b, align: "left"|"center"|"right")
int ScriptingEngine::lua_drawText(lua_State *L)
{
    int argc = lua_gettop(L);

    const char *alignment = (char *) lua_tostring (L, argc);
    int b = lua_tonumberx(L, argc-1, NULL);
    int g = lua_tonumberx(L, argc-2, NULL);
    int r = lua_tonumberx(L, argc-3, NULL);

    int y = lua_tonumberx(L, argc-4, NULL);
    int x = lua_tonumberx(L, argc-5, NULL);

    const char *text = (char *) lua_tostring (L, argc-6);
    FontI *fontPointer = (FontI*)lua_topointer(L, argc-7);

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

        m_curEngine->DrawText(fontPointer, text, x, y, r, g, b, align);
    }

    return 0;
}

};
