//
//  engine.cpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#include "engine.hpp"
#include <vector>
#include "font.hpp"

#ifdef __cplusplus
extern "C" {
    #include "../../../Lua/code/src/lua.h"
    #include "../../../Lua/code/src/lualib.h"
    #include "../../../Lua/code/src/lauxlib.h"
}
#endif //__cplusplus

namespace engine
{

Engine::Engine(EngineProviderI &engineProvider, FileAccessI &fileAccess, ScriptingEngineI &scriptingEngine)
: EngineI(engineProvider, fileAccess, scriptingEngine)
{
}

Engine::~Engine()
{
    DisposeAllTextures();
    DisposeAllFonts();
}

void Engine::setup()
{
    m_scriptingEngine.newState();
    m_scriptingEngine.loadFile(m_fileAccess.getBundledFilepath("main.lua"));
    m_scriptingEngine.registerFunctions();
    m_scriptingEngine.callInit();
}

TextureI *Engine::LoadTexture(std::string name)
{
    TextureI *result = GetTexture(name);
    if (!result)
    {
        result = m_engineProvider.LoadTexture(name);
        if (result)
        {
            m_textures.emplace_back(std::move(result));
        }
    }

    return result;
}

TextureI *Engine::GetTexture(std::string name)
{
    for(auto it = std::begin(m_textures); it != std::end(m_textures); ++it)
    {
        TextureI *item = it->get();
        if (item->getTextureName().compare(name) == 0)
        {
            return item;
        }
    }

    return NULL;
}

void Engine::DrawTexture(TextureI *texture, int x, int y)
{
    m_engineProvider.DrawTexture(texture, x, y);
}

void Engine::UnloadTexture(TextureI *texture)
{
    for(auto it = std::begin(m_textures); it != std::end(m_textures); ++it)
    {
        TextureI *item = it->get();
        if (item == texture)
        {
            m_engineProvider.UnloadTexture(item);
            m_textures.erase(it);
            break;
        }
    }
}

void Engine::DisposeAllTextures()
{
    std::cout << "DisposeAlLTextures not implemented" << std::endl;
}

FontI *Engine::LoadFont(std::string name)
{
    FontI *result = GetFont(name);
    if (!result)
    {
        result = m_engineProvider.LoadFont(name);
        if (result)
        {
            m_fonts.emplace_back(std::move(result));
            return result;
        }
    }
    return NULL;
}

FontI *Engine::GetFont(std::string name)
{
    for(auto it = std::begin(m_fonts); it != std::end(m_fonts); ++it)
    {
        FontI *item = it->get();
        if (item->getFontName().compare(name) == 0)
        {
            return item;
        }
    }

    return NULL;
}

void Engine::DrawText(FontI *font, std::string text, int x, int y, int r, int g, int b, TEXT_ALIGNMENT align)
{
    m_engineProvider.DrawText(font, text, x, y, r, g, b, align);
}

void Engine::DisposeAllFonts()
{
    std::cout << "DisposeAllFonts not implemented" << std::endl;
}

void Engine::update()
{
    m_scriptingEngine.callUpdate();

//    m_engineProvider.DrawText(f, "test", 10, 10, 100, 100, 100, TEXT_ALIGN_LEFT);

//    static int i = 0;
//
//    if (i++ < 30)
//    {
//        TextureI *texture = GetTexture(m_fileAccess.getBundledFilepath("background.jpg"));
//        m_engineProvider.DrawTexture(texture, 0, 0);
//    } else if (i++ > 60) {
//        i = 0;
//    }
}

}

/*
 lua_State* L;
 L = luaL_newstate();
 lua_pushstring(L, "Anna");
 lua_setglobal(L, "name");
 luaL_openlibs(L);
 if(luaL_dofile(L, "hello.lua")) {
 std::cout << "Final:" << lua_tostring(L, -1) << "\n";
 }
 lua_close(L);
 */

/*
 // delete some dangerous functions
 lua_pushnil(L); lua_setglobal(L, "dofile");
 lua_pushnil(L); lua_setglobal(L, "loadfile");
 lua_pushnil(L); lua_setglobal(L, "loadlib");
 lua_pushnil(L); lua_setglobal(L, "loadstring"); // replaced
 lua_pushnil(L); lua_setglobal(L, "require");
 lua_pushnil(L); lua_setglobal(L, "rawequal");
 lua_pushnil(L); lua_setglobal(L, "rawget");
 lua_pushnil(L); lua_setglobal(L, "rawset");
 //    lua_pushnil(L); lua_setglobal(L, "getfenv");
 //    lua_pushnil(L); lua_setglobal(L, "setfenv");
 lua_pushnil(L); lua_setglobal(L, "newproxy");
 lua_pushnil(L); lua_setglobal(L, "gcinfo");
 lua_pushnil(L); lua_setglobal(L, "collectgarbage");

 see https://cpp.hotexamples.com/examples/-/-/lua_setglobal/cpp-lua_setglobal-function-examples.html
 */
