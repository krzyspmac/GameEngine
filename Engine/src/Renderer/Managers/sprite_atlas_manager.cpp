//
//  sprite_atlas_manager.cpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#include "sprite_atlas_manager.hpp"
#include "sprite_atlas.hpp"

using namespace engine;

SpriteAtlasI *SpriteAtlasManager::SpriteAtlasLoad(std::string jsonFilename, std::string textureFilename)
{
    SpriteAtlasI *atlas = SpriteAtlasGet(jsonFilename);
    if (!atlas)
    {
        atlas = new SpriteAtlas(jsonFilename, textureFilename);
        if (atlas)
        {
            m_atlas.emplace_back(std::move(atlas));
        }
    }

    return atlas;
}

SpriteAtlasI *SpriteAtlasManager::SpriteAtlasGet(std::string jsonFilename)
{
    for(auto it = std::begin(m_atlas); it != std::end(m_atlas); ++it)
    {
        SpriteAtlasI *item = it->get();
        if (item->GetFilename().compare(jsonFilename) == 0)
        {
            return item;
        }
    }

    return NULL;
}

void SpriteAtlasManager::SpriteAtlasUnload(SpriteAtlasI *atlas)
{
    for(auto it = std::begin(m_atlas); it != std::end(m_atlas); ++it)
    {
        SpriteAtlasI *item = it->get();
        if (item == atlas)
        {
            m_atlas.erase(it);
            break;
        }
    }
}

void SpriteAtlasManager::SpriteAtlasDisposeAll()
{
    m_atlas.clear();
}


#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(SpriteAtlasManager);

static int lua_SpriteAtlas_SpriteAtlasLoad(lua_State *L)
{
    SpriteAtlasManager **ptr = (SpriteAtlasManager**)luaL_checkudata(
        L, 1, SpriteAtlasManager::ScriptingInterfaceName().c_str()
    );
    if (ptr == nullptr) { return 0; }
    if (dynamic_cast<SpriteAtlasManager*>(*ptr) == nullptr) { return 0; }

    std::string jsonName = luaL_checkstring(L, 2);
    std::string textureFilename = luaL_checkstring(L, 3);

    SpriteAtlas *item = (SpriteAtlas*)(*ptr)->SpriteAtlasLoad(jsonName, textureFilename);
    item->ScriptingInterfaceRegisterFunctions(L, item);
    // no need to push user data; the object is there
    return 1;
}

std::vector<luaL_Reg> SpriteAtlasManager::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "SpriteAtlasLoad", &lua_SpriteAtlas_SpriteAtlasLoad}
    });
    return result;
}
