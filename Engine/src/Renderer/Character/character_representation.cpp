//
//  character_representation.cpp
//  Engine
//
//  Created by krzysp on 31/12/2021.
//

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
