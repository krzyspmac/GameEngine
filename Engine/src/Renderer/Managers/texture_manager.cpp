//
//  texture_manager.cpp
//  Engine
//
//  Created by krzysp on 08/01/2022.
//

#include "texture_manager.hpp"
#include "file_access_provider.h"
#include "engine.hpp"

using namespace engine;

TextureI *TextureManager::LoadTexture(std::string filename)
{
    TextureI *result = GetTexture(filename);
    if (!result)
    {
        FileAccessI& fileAccess = ENGINE().getFileAccess();
        EngineProviderI& engineProvider = ENGINE().getProvider();

        std::unique_ptr<FileStreamI> stream(fileAccess.GetAccess(filename));
        result = engineProvider.LoadTexture(filename, stream.get());
        if (result)
        {
            m_textures.emplace_back(std::move(result));
        }
    }

    return result;
}

TextureTargetI *TextureManager::CreateTargetTexture(int width, int height)
{
    EngineProviderI& engineProvider = ENGINE().getProvider();
    return engineProvider.CreateTargetTexture(width, height);
}

TextureI *TextureManager::GetTexture(std::string name)
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

void TextureManager::UnloadTexture(TextureI *texture)
{
    EngineProviderI& engineProvider = ENGINE().getProvider();

    for(auto it = std::begin(m_textures); it != std::end(m_textures); ++it)
    {
        TextureI *item = it->get();
        if (item == texture)
        {
            engineProvider.UnloadTexture(item);
            m_textures.erase(it);
            break;
        }
    }
}

void TextureManager::DisposeAllTextures()
{
    std::cout << "DisposeAlLTextures not implemented" << std::endl;
}

