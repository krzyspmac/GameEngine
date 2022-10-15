// Copyright (c) 2022 Krzysztof Pawłowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in the
// Software without restriction, including without limitation the rights to use, copy,
// modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies
// or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.

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
