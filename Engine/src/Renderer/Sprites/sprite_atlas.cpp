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
        char *jsonSrouce = (char*)stream.get()->GetMemory();
        if (jsonSrouce)
        {
            cJSON *root, *frames, *node, *singleFrame;
            char *filename, *rotated;
            int x, y, w, h;

            root = cJSON_Parse(jsonSrouce);
            if (root)
            {
                frames = cJSON_GetObjectItem(root, "frames");
                if (frames)
                {
                    for (node = frames->child ; node != NULL ; node = node->next)
                    {
                        singleFrame = cJSON_GetObjectItem(node, "frame");
                        if (singleFrame)
                        {
                            filename = cJSON_GetObjectItem(node, "filename")->valuestring;
                            x = cJSON_GetObjectItem(singleFrame, "x")->valueint;
                            y = cJSON_GetObjectItem(singleFrame, "y")->valueint;
                            w = cJSON_GetObjectItem(singleFrame, "w")->valueint;
                            h = cJSON_GetObjectItem(singleFrame, "h")->valueint;
                            rotated = cJSON_GetObjectItem(node, "rotated")->string;

                            this->m_texture = texture;
                            m_items.emplace_back(SpriteAtlasItemI(texture, x, y, w, h, strcmp(rotated, "true") == 0, filename));
                        }; // single frame
                    }; // for
                }; // frame
            }; // root

            m_filename = jsonFilename;
            cJSON_Delete(root);
        }; // jsonSrouce
    }; // texture
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

#pragma mark - Scripting Interface

SCRIPTING_INTERFACE_IMPL_NAME(SpriteAtlas);

static int lua_SpriteAtlas_GetItemForName(lua_State *L)
{
    SpriteAtlas **ptr = (SpriteAtlas**)luaL_checkudata(
        L, 1, SpriteAtlas::ScriptingInterfaceName().c_str()
    );
    if (ptr != nullptr && dynamic_cast<SpriteAtlas*>(*ptr) == nullptr) { return 0; }

    std::string filename = luaL_checkstring(L, 2);
    SpriteAtlasItemI *item = (SpriteAtlasItemI*) (*ptr)->GetItemForName(filename);
    if (item != nullptr && dynamic_cast<SpriteAtlasItemI*>(item) == nullptr) { return 0; }

    lua_pushlightuserdata(L, item); // return the data; SpriteAtlasItemI is not scriptable
    return 1;
}

std::vector<luaL_Reg> SpriteAtlas::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "getItemForName", &lua_SpriteAtlas_GetItemForName}
    });
    return result;
}
