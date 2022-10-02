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
