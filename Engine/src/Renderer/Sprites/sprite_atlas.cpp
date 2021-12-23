//
//  sprite_atlas.cpp
//  RendererAppSDL
//
//  Created by krzysp on 22/12/2021.
//

#include "sprite_atlas.hpp"
#include "engine.hpp"
#include "cJSON.h"

static char *readFile(std::string);

using namespace engine;

SpriteAtlas::SpriteAtlas(std::string jsonFilename, std::string textureFilename)
: SpriteAtlasI(jsonFilename, textureFilename)
{
    std::string jsonConvertedPath = GetMainEngine()->getFileAccess().getBundledFilepath(jsonFilename.c_str());
    std::string textureConvertedPath = GetMainEngine()->getFileAccess().getBundledFilepath(textureFilename.c_str());

    TextureI *texture = GetMainEngine()->LoadTexture(textureConvertedPath);
    if (texture)
    {
        char *jsonText = readFile(jsonConvertedPath.c_str());
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
            free(jsonText);
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

char *readFile(std::string filename)
{
    char *buffer = NULL;
    long length;
    FILE *file;

    file = fopen(filename.c_str(), "rb");

    if (file)
    {
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);

        buffer = (char*)malloc(length);
        memset(buffer, 0, length);
        fread(buffer, 1, length, file);

        fclose(file);
    }

    return buffer;
}
