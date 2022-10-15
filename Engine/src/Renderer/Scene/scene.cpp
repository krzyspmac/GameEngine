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

#include "scene.hpp"
#include "character.hpp"
#include "light.hpp"
#include "font_bitmap.hpp"
#include "easy.h"

using namespace engine;

Scene::Scene()
    : m_mainCharacter(nullptr)
    , m_mouseDownFunctionRef(-1)
    , m_engineProvider(ENGINE().getProvider())
    , m_mouseDownIdentifier(-1)
    , m_frameUpdateCallback(nullptr)
    , m_isActive(false)
{
    m_mouseDownIdentifier = ENGINE()
        .getEventsManager()
        .RegisterMouseClickedEvents(CallableParameters1<Origin>::make_shared([&](Origin clicked){
            Vector2 pos;
            pos.x = clicked.x;
            pos.y = clicked.y;
            MouseClicked(pos);
        }))
    ;
}

Scene::~Scene()
{
    ENGINE().getEventsManager().UnregisterEvent(m_mouseDownIdentifier);
}

void Scene::MouseClicked(Vector2 pos)
{
    if (m_mainCharacter != nullptr)
    {
        m_mainCharacter->WalkTo(pos);
    }
}

void Scene::SetMainCharacter(CharacterRepresentation *rep)
{
    m_mainCharacter = rep;
}

SpriteRepresentationI *Scene::SpriteStaticLoad(SpriteAtlasI *atlas, std::string name)
{
    SpriteAtlasItemI *item = atlas->GetItemForName(name);
    if (item != nullptr)
    {
        SpriteRepresentationStatic *renderer = (SpriteRepresentationStatic*)ENGINE().getSpriteRendererManager().SpriteRepresentationStaticLoad(item);
        if (renderer != nullptr)
        {
            SpriteStaticAdd(renderer);
            return renderer;
        }
    }
    return nullptr;
}

SpriteRepresentationI *Scene::SpriteAnimatedLoad(float keyframeAnimationDelay, SpriteAtlasI *atlas)
{
    if (atlas != nullptr)
    {
        SpriteRepresentationAnimated *renderer = (SpriteRepresentationAnimated*)ENGINE().getSpriteRendererManager().SpriteRepresentationAnimatedLoad(keyframeAnimationDelay, atlas);
        if (renderer != nullptr)
        {
            SpriteAnimatedAdd(renderer);
            return renderer;
        }
    }
    return nullptr;
}

SpriteRepresentationTextI *Scene::SpriteTextLoad(FontI *font)
{
    if (font != nullptr)
    {   auto *rep = (SpriteRepresentationText*)ENGINE().getSpriteRendererManager().SpriteRepresentationTextLoad(font);
        if (rep != nullptr)
        {   SpriteTextAdd(rep);
            return rep;
        }
    }

    return nullptr;
}

void Scene::SpriteStaticAdd(SpriteRepresentationStatic *renderer)
{
    m_staticSprites.push_back(renderer);
}

void Scene::SpriteAnimatedAdd(SpriteRepresentationAnimated *renderer)
{
    m_animatedSprites.push_back(renderer);
}

void Scene::SpriteTextAdd(SpriteRepresentationText *renderer)
{
    m_textSprites.push_back(renderer);
}

CharacterRepresentation *Scene::LoadCharacter(std::string jsonFilename)
{
    CharacterRepresentation *rep = ENGINE().getCharacterManager().LoadCharacter(jsonFilename);
    m_characterRepresentations.emplace_back(rep);
    return rep;
}

void Scene::SetMouseDownFunction(int mouseFunctionRef)
{
    m_mouseDownFunctionRef = mouseFunctionRef;
}

void Scene::SetFrameUpdate(std::function<void(void)> lambda)
{
    m_frameUpdateCallback = lambda;
}

void Scene::RenderSceneSprites()
{
    if (m_frameUpdateCallback != nullptr)
    {
        m_frameUpdateCallback();
    }

    for (auto it = m_staticSprites.begin(); it != m_staticSprites.end(); ++it)
    {
        SpriteRepresentationI *sprite = (*it);
        Vector2& pos = sprite->GetPosition();
        (*it)->DrawAt(pos.x, pos.y);
    };

    for (auto* item : m_animatedSprites)
    {
        Vector2& pos = item->GetPosition();
        item->DrawAt(pos.x, pos.y);
    }

    for (auto it = m_characterRepresentations.begin(); it != m_characterRepresentations.end(); ++it)
    {
        (*it)->Render();
    };

    for (auto *textRep : m_textSprites)
    {
        textRep->Draw();
    }
}

LightI* Scene::CreateLight(std::string type, Color3 color, float ambientIntensity, Origin position, float diffuseSize, float diffuseIntensity)
{
    auto* light = ENGINE().getLightMnaager().CreateLight(type, color, ambientIntensity, position, diffuseSize, diffuseIntensity);
    if (light != nullptr)
    {
        m_lights.emplace_back(light);
        return light;
    }
    else
    {
        return nullptr;
    }
}
