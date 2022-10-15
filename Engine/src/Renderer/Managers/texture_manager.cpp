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

