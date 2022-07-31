//
//  character.cpp
//  Engine
//
//  Created by krzysp on 25/12/2021.
//

#include "character.hpp"
#include "character_renderer.hpp"
#include "engine.hpp"
#include "cJSON.h"

static int cJSON_GetObjectItemValueInt(cJSON * object, const char *string);

using namespace engine;

Character::Character(std::string jsonDefinition)
: CharacterI(jsonDefinition)
{
    std::unique_ptr<FileStreamI> stream(ENGINE().getFileAccess().GetAccess(jsonDefinition));

    auto buffer = stream->ReadBufferString();
    const char *jsonSource = buffer.c_str();
    if (jsonSource && strlen(jsonSource) > 0)
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

                atlas = ENGINE().getAtlasManager().SpriteAtlasLoad(atlasFilename, atlasTexture);
                if (atlas)
                {
                    m_characterRenderer = std::unique_ptr<CharacterRendererI>(new CharacterRenderer(atlas, 1));
                }
            }

            // Right
            cJSON *walkRightNode = cJSON_GetObjectItem(root, "walkRight");
            ProcessBodyParts(walkRightNode, atlas, RIGHT, false);

            cJSON *standRightNode = cJSON_GetObjectItem(root, "standRight");
            ProcessBodyParts(standRightNode, atlas, STAND_RIGHT, false);

            // Left
            cJSON *walkLeftNode = cJSON_GetObjectItem(root, "walkLeft");
            if (walkLeftNode)
            {
                ProcessBodyParts(walkLeftNode, atlas, LEFT, false);
            }
            else
            {
                ProcessBodyParts(walkRightNode, atlas, LEFT, true);
            }

            cJSON *standLeftNode = cJSON_GetObjectItem(root, "standLeft");
            if (walkLeftNode)
            {
                ProcessBodyParts(standLeftNode, atlas, STAND_LEFT, false);
            }
            else
            {
                ProcessBodyParts(standRightNode, atlas, STAND_LEFT, true);
            }

            // Forward
            cJSON *walkForwardNode = cJSON_GetObjectItem(root, "walkForward");
            ProcessBodyParts(walkForwardNode, atlas, FORWARD, false);

            cJSON *standForwardNode = cJSON_GetObjectItem(root, "standForward");
            ProcessBodyParts(standForwardNode, atlas, STAND_FORWARD, false);

            // Backward
            cJSON *walkBackwardNode = cJSON_GetObjectItem(root, "walkBackward");
            ProcessBodyParts(walkBackwardNode, atlas, BACKWARD, false);

            cJSON *standBackwardNode = cJSON_GetObjectItem(root, "standBackward");
            ProcessBodyParts(standBackwardNode, atlas, STAND_BACKWARD, false);

            cJSON_Delete(root);
            m_characterRenderer->PrepareCharacter();
        }
    }
}

void Character::ProcessBodyParts(void *rootPtr, SpriteAtlasI * atlas, CharacterWalkState walkState, bool reversed)
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
                ProcessBodyFrame(node, atlas, walkState, reversed);
            }
        }

        cJSON *head = cJSON_GetObjectItem(bodyPartRoot, "head");
        if (head)
        {
            for (node = head->child ; node != NULL ; node = node->next)
            {
                ProcessHeadFrame(node, atlas, walkState, reversed);
            }
        }

        m_characterRenderer->GetRenderer(walkState).SetBodyAnimationDelay(animationDelay);
        m_characterRenderer->GetRenderer(walkState).SetHeadAnimationDelay(animationDelay);
    }
}

void Character::ProcessBodyFrame(void *nodePtr, SpriteAtlasI *atlas, CharacterWalkState walkState, bool reversed)
{
    cJSON *node = (cJSON*)nodePtr;
    char *spriteFilename = cJSON_GetObjectItem(node, "sprite")->valuestring;
    int headOffsetX = cJSON_GetObjectItemValueInt(node, "headOffsetX");
    int headOffsetY = cJSON_GetObjectItemValueInt(node, "headOffsetY");
    int offsetX = cJSON_GetObjectItemValueInt(node, "offsetX");
    int offsetY = cJSON_GetObjectItemValueInt(node, "offsetY");

    SpriteAtlasItemI *sprite = atlas->GetItemForName(spriteFilename);
    m_characterRenderer->AppendBodyWalkAnimationFrame(walkState, sprite, offsetX, offsetY, headOffsetX, headOffsetY);
    m_characterRenderer->GetRenderer(walkState).SetReversed(reversed);
}

void Character::ProcessHeadFrame(void *nodePtr, SpriteAtlasI *atlas, CharacterWalkState walkState, bool reversed)
{
    cJSON *node = (cJSON*)nodePtr;
    char *spriteFilename = cJSON_GetObjectItem(node, "sprite")->valuestring;
    int offsetX = cJSON_GetObjectItemValueInt(node, "offsetX");
    int offsetY = cJSON_GetObjectItemValueInt(node, "offsetY");

    SpriteAtlasItemI *sprite = atlas->GetItemForName(spriteFilename);
    m_characterRenderer->AppendHeadAnimationFrame(walkState, sprite, offsetX, offsetY);
    m_characterRenderer->GetRenderer(walkState).SetReversed(reversed);
}

void Character::SetScale(float scale)
{
    m_characterRenderer->SetScale(scale);
}

void Character::SetZPosition(float value)
{
    m_characterRenderer->SetZPosition(value);
}

void Character::Draw(Vector2& position)
{
    m_characterRenderer->Draw(m_walkState, m_isWalking, m_talking, position);
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

#pragma mark - Scripting

SCRIPTING_INTERFACE_IMPL_NAME(Character);

static int lua_Character_getFilename(lua_State *L)
{
    Character **ptr = (Character**)luaL_checkudata(
        L, 1, Character::ScriptingInterfaceName().c_str()
     );

    if (ptr == nullptr) { return 0; }
    if (dynamic_cast<Character*>(*ptr) == nullptr) { return 0; }

    std::string result = (*ptr)->GetJsonFilename();
    lua_pushstring(L, result.c_str());
    return 1;
}

static int lua_Character_DrawAt(lua_State *L)
{
    Character *chr = ScriptingEngineI::GetScriptingObjectPtr<Character>(L, 1);
    float x = lua_tonumberx(L, 2, NULL);
    float y = lua_tonumberx(L, 3, NULL);
    Vector2 pos = {x, y};
    chr->Draw(pos);
    return 0;
}

static int lua_Character_SetScale(lua_State *L)
{
    Character *chr = ScriptingEngineI::GetScriptingObjectPtr<Character>(L, 1);
    float scale = lua_tonumberx(L, 2, NULL);
    chr->SetScale(scale);
    return 0;
}

std::vector<luaL_Reg> Character::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "GetFilename", &lua_Character_getFilename },
        { "DrawAt", &lua_Character_DrawAt },
        { "SetScale", &lua_Character_SetScale },
    });
    return result;
}
