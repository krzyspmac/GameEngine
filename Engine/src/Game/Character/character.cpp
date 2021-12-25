//
//  character.cpp
//  Engine
//
//  Created by krzysp on 25/12/2021.
//

#include "character.hpp"
#include "common_engine.h"
#include "character_renderer.hpp"
#include "cJSON.h"

using namespace engine;

Character::Character(std::string jsonDefinition)
: CharacterI()
{
    std::unique_ptr<FileMemoryBufferStreamI> stream(GetMainEngine()->getFileAccess().GetAccess(jsonDefinition));

    char *jsonSource = (char*)stream.get()->GetMemory();
    if (jsonSource)
    {
        cJSON *root, *node;
        SpriteAtlasI * atlas = NULL;

        root = cJSON_Parse(jsonSource);
        if (root)
        {
            cJSON *atlasNode = cJSON_GetObjectItem(root, "atlas");
            if (atlasNode)
            {
                char *atlasFilename = cJSON_GetObjectItem(atlasNode, "json")->valuestring;
                char *atlasTexture = cJSON_GetObjectItem(atlasNode, "texture")->valuestring;

                atlas = GetMainEngine()->SpriteAtlasLoad(atlasFilename, atlasTexture);
                if (atlas)
                {
                    m_characterRenderer = new CharacterRenderer(atlas, 3);
                }
            }

            cJSON *walkRight = cJSON_GetObjectItem(root, "walkRight");
            if (walkRight)
            {
                cJSON *body = cJSON_GetObjectItem(walkRight, "body");
                if (body)
                {
                    for (node = body->child ; node != NULL ; node = node->next)
                    {
                        char *spriteFilename = cJSON_GetObjectItem(node, "sprite")->valuestring;
                        int headOffsetX = cJSON_GetObjectItem(node, "headOffsetX")->valueint;
                        int headOffsetY = cJSON_GetObjectItem(node, "headOffsetY")->valueint;

                        SpriteAtlasItemI *sprite = atlas->GetItemForName(spriteFilename);
                        m_characterRenderer->AppendBodyWalkAnimationFrame(RIGHT, sprite, headOffsetX, headOffsetY);
                    }
                }

                cJSON *head = cJSON_GetObjectItem(walkRight, "head");
                if (head)
                {
                    for (node = head->child ; node != NULL ; node = node->next)
                    {
                        char *spriteFilename = cJSON_GetObjectItem(node, "sprite")->valuestring;

                        SpriteAtlasItemI *sprite = atlas->GetItemForName(spriteFilename);
                        m_characterRenderer->AppendHeadAnimationFrame(RIGHT, sprite);
                    }
                }
            }

            cJSON_Delete(root);
        }
    }
}

void Character::Draw(int x, int y)
{
    m_characterRenderer->Draw(x, y);
}
