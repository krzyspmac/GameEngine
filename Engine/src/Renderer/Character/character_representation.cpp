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

#include "character_representation.hpp"
#include "character_mover.hpp"
#include "polygon_loader.hpp"
#include "engine.hpp"
#include "polygon.hpp"

using namespace engine;

CharacterRepresentation::CharacterRepresentation(CharacterI *character)
: m_character(character), m_hidden(false)
{
    m_mover = std::unique_ptr<CharacterMoverI>(new CharacterMover(m_character, 100));
}

CharacterRepresentation::~CharacterRepresentation()
{
    m_mover.reset();
}

void CharacterRepresentation::DrawAt(Vector2& position)
{
    m_character->Draw(position);
}

void CharacterRepresentation::PlaceAt(Vector2 target)
{
    m_mover->PlaceCharacter(target);
}

void CharacterRepresentation::SetScale(float val)
{
    m_character->SetScale(val);
}

void CharacterRepresentation::SetZPosition(float val)
{
    m_character->SetZPosition(val);
}

Vector2& CharacterRepresentation::GetPosition()
{
    return m_mover->GetCharacterPosition();
}

void CharacterRepresentation::WalkTo(Vector2& position)
{
    PathFinder *pf = m_pathFinder.get();
    CharacterMoverI *cm = m_mover.get();

    if (pf != nullptr && cm != nullptr)
    {
        PathI *path = pf->CalculatePath(cm->GetCharacterPosition(), position);
        m_mover->MoveCharacterAlongPath(path);
    }
    else
    {
        m_mover->MoveCharacter(position);
    }
}

void CharacterRepresentation::SetInverseWalkbox(std::string polygonJsonFilename)
{
    std::vector<Polygon> polygonList = PolygonLoader::Load(ENGINE().getFileAccess().GetAccess(polygonJsonFilename));
    m_pathFinder = std::unique_ptr<PathFinder>(new PathFinder(polygonList));
}

void CharacterRepresentation::SetCharacterWalkingSpeed(float pixelsInMilliseconds)
{
    m_mover->SetWalkingSpeed(pixelsInMilliseconds);
}

void CharacterRepresentation::SetHidden(bool value)
{
    m_hidden = value;
}

void CharacterRepresentation::Render()
{
    if (m_hidden) { return; }

    m_mover->Update();

    PathFinder *pf = m_pathFinder.get();
    if (pf != nullptr)
    {
        pf->Draw();
    }
}
