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

static int cJSON_GetObjectItemValueInt(cJSON * object, const char *string);

using namespace engine;

Character::Character(std::string jsonDefinition)
: CharacterI()
{
    std::unique_ptr<FileMemoryBufferStreamI> stream(GetMainEngine()->getFileAccess().GetAccess(jsonDefinition));

    char *jsonSource = (char*)stream.get()->GetMemory();
    if (jsonSource)
    {
        cJSON *root;
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

            ProcessBodyParts(cJSON_GetObjectItem(root, "walkRight"), atlas, RIGHT);
            ProcessBodyParts(cJSON_GetObjectItem(root, "standRight"), atlas, STAND_RIGHT);

            cJSON_Delete(root);
        }
    }
}

void Character::ProcessBodyParts(void *rootPtr, SpriteAtlasI * atlas, CharacterWalkDirection walkState)
{
    cJSON *bodyPartRoot, *node;

    bodyPartRoot = (cJSON*)rootPtr;

    if (bodyPartRoot)
    {
        int animationDelay = cJSON_GetObjectItemValueInt(bodyPartRoot, "animationDelay");

        cJSON *body = cJSON_GetObjectItem(bodyPartRoot, "body");
        if (body)
        {
            for (node = body->child ; node != NULL ; node = node->next)
            {
                char *spriteFilename = cJSON_GetObjectItem(node, "sprite")->valuestring;
                int headOffsetX = cJSON_GetObjectItemValueInt(node, "headOffsetX");
                int headOffsetY = cJSON_GetObjectItemValueInt(node, "headOffsetY");
                int offsetX = cJSON_GetObjectItemValueInt(node, "offsetX");
                int offsetY = cJSON_GetObjectItemValueInt(node, "offsetY");

                SpriteAtlasItemI *sprite = atlas->GetItemForName(spriteFilename);
                m_characterRenderer->AppendBodyWalkAnimationFrame(walkState, sprite, offsetX, offsetY, headOffsetX, headOffsetY);
            }
        }

        cJSON *head = cJSON_GetObjectItem(bodyPartRoot, "head");
        if (head)
        {
            for (node = head->child ; node != NULL ; node = node->next)
            {
                char *spriteFilename = cJSON_GetObjectItem(node, "sprite")->valuestring;
                int offsetX = cJSON_GetObjectItemValueInt(node, "offsetX");
                int offsetY = cJSON_GetObjectItemValueInt(node, "offsetY");

                SpriteAtlasItemI *sprite = atlas->GetItemForName(spriteFilename);
                m_characterRenderer->AppendHeadAnimationFrame(walkState, sprite, offsetX, offsetY);
            }
        }

        m_characterRenderer->GetRenderer(walkState).SetBodyAnimationDelay(animationDelay);
        m_characterRenderer->GetRenderer(walkState).SetHeadAnimationDelay(animationDelay);
    }

}

static CharacterWalkDirection state = STAND_RIGHT;

void Character::Draw(int x, int y)
{
    m_characterRenderer->DrawBody(state, true, x, y);
    m_characterRenderer->DrawHead(state, true, x, y);
}

void Character::Change()
{
    if (state != STAND_RIGHT)
    {
        state = STAND_RIGHT;
    }
    else
    {
        state = RIGHT;
    }
}

int cJSON_GetObjectItemValueInt(cJSON * object, const char *string)
{
    cJSON *obj = cJSON_GetObjectItem(object, string);
    if (obj)
    {
        return obj->valueint;
    }
    else
    {
        return 0;
    }
}
