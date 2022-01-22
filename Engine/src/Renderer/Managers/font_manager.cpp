//
//  font_manager.cpp
//  Engine
//
//  Created by krzysp on 08/01/2022.
//

#include "font_manager.hpp"
#include "font_bitmap.hpp"

using namespace engine;

FontI *FontManager::LoadFont(std::string fntFilename, std::string fontTexture)
{
    FontI *result = GetFont(fntFilename);
    if (!result)
    {
        FontI *result = new FontBitmapRepresentation(fntFilename, fontTexture, 1);
        if (result)
        {
            m_fonts.emplace_back(std::unique_ptr<FontI>(std::move(result)));
            return result;
        }
    }
    return result;
}

FontI *FontManager::GetFont(std::string name)
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

void FontManager::DisposeAllFonts()
{
    std::cout << "DisposeAllFonts not implemented" << std::endl;
}

SCRIPTING_INTERFACE_IMPL_NAME(FontManager);

static int lua_FontManager_LoadFont(lua_State *L)
{
    FontManager *mgr = ScriptingEngineI::GetScriptingObjectPtr<FontManager>(L, 1);

    const char *fntFilename = lua_tostring(L, 2);
    const char *textureFilename = lua_tostring(L, 3);

    FontBitmapRepresentation *rep = (FontBitmapRepresentation*)mgr->LoadFont(fntFilename, textureFilename);
    if (rep != nullptr)
    {
        rep->ScriptingInterfaceRegisterFunctions(L, rep);
        return 1;
    }
    else
    {
        return 0;
    }
}

std::vector<luaL_Reg> FontManager::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "LoadFont", &lua_FontManager_LoadFont}
    });
    return result;
}
