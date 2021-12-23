//
//  sprite_atlas.cpp
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#include "sprite_atlas.hpp"
#include "engine.hpp"
#include "cJSON.h"

using namespace engine;

SpriteAtlas::SpriteAtlas(std::string jsonFilename, std::string textureFilename)
: SpriteAtlasI(jsonFilename, textureFilename)
{
    std::unique_ptr<FileMemoryBufferStreamI> stream(GetMainEngine()->getFileAccess().GetAccess(jsonFilename));

    TextureI *texture = GetMainEngine()->LoadTexture(textureFilename);
    if (texture)
    {
        char *jsonText = (char*)stream.get()->GetMemory();
        if (jsonText)
        {
            cJSON *root, *node;
            char *filename;
            int x, y, w, h, rotated;
            root = cJSON_Parse(jsonText);

            for (node = root->child ; node != NULL ; node = node->next)
            {
                filename = cJSON_GetObjectItem(node, "filename")->valuestring;
                x = cJSON_GetObjectItem(node, "x")->valueint;
                y = cJSON_GetObjectItem(node, "y")->valueint;
                w = cJSON_GetObjectItem(node, "w")->valueint;
                h = cJSON_GetObjectItem(node, "h")->valueint;
                rotated = cJSON_GetObjectItem(node, "rotated")->valueint;

                this->m_texture = texture;
                m_items.emplace_back(SpriteAtlasItemI(texture, x, y, w, h, rotated, filename));
            }

            m_filename = jsonFilename;
            cJSON_Delete(root);
        }
    }
}

SpriteAtlas::~SpriteAtlas()
{
}

SpriteAtlasItemI *SpriteAtlas::GetItemForName(std::string name)
{
    for(auto it = std::begin(m_items); it != std::end(m_items); ++it)
    {
        if (it->GetFilename().compare(name) == 0)
        {
            return &(*it);
        }
    }

    return NULL;
}
