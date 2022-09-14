//
//  gamepad.cpp
//  Engine
//
//  Created by krzysp on 14/09/2022.
//

#include "gamepad.hpp"
#include "engine.hpp"

using namespace engine;

Gamepad::~Gamepad()
{
}

template<typename S>
static void TemplateRemoveIfMatching(std::vector<S> &handlers, GamepadEventIdentifier identifier)
{
    for (auto it = handlers.begin(); it != handlers.end(); it++)
    {
        if ((*it).GetIdentifier() == identifier)
        {
            handlers.erase(it);
            return;
        }
    }
}

void Gamepad::ProcessEvent(EventGamepadThumbstickAxisChanged* event)
{
    auto& vector = event->GetVector();

    switch (event->GetThumbstickType())
    {
        case GAMEPAD_THUMBSTICK_AXIS_LEFT:
        {
            for (auto& codeHandler : m_leftStickAxisChange)
            {
                codeHandler.Process(&vector);
            }
            break;
        }
        case GAMEPAD_THUMBSTICK_AXIS_RIGHT:
        {
            for (auto& codeHandler : m_rightStickAxisChange)
            {
                codeHandler.Process(&vector);
            }
            break;
        }
    }
}

void Gamepad::UnregisterEvent(GamepadEventIdentifier identifier)
{
    TemplateRemoveIfMatching<EventHolderGamepadStickAxis>(m_leftStickAxisChange, identifier);
    TemplateRemoveIfMatching<EventHolderGamepadStickAxis>(m_rightStickAxisChange, identifier);
}

void Gamepad::UnregisterAllEvents()
{
    m_leftStickAxisChange.clear();
    m_rightStickAxisChange.clear();
}

GamepadEventIdentifier Gamepad::RegisterLeftThumbstickAxis(CallableScriptFunctionParameters1<Vector2> fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_leftStickAxisChange.push_back(EventHolderGamepadStickAxis(identifier, fnc));
    return identifier;
}

GamepadEventIdentifier Gamepad::RegisterRightThumbstickAxis(CallableScriptFunctionParameters1<Vector2> fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_rightStickAxisChange.push_back(EventHolderGamepadStickAxis(identifier, fnc));
    return identifier;
}

/** Scripting interface */

SCRIPTING_INTERFACE_IMPL_NAME(Gamepad);

static int lua_RegisterLeftThumbstickAxis(lua_State *L)
{
    Gamepad *mgr = ScriptingEngineI::GetScriptingObjectPtr<Gamepad>(L, 1);
    int fnRef = luaL_ref( L, LUA_REGISTRYINDEX );
    auto identifier = mgr->RegisterLeftThumbstickAxis(CallableScriptFunctionParameters1<Vector2>(fnRef));
    lua_pushnumber(L, identifier);
    return 1;
}

static int lua_RegisterRightThumbstickAxis(lua_State *L)
{
    Gamepad *mgr = ScriptingEngineI::GetScriptingObjectPtr<Gamepad>(L, 1);
    int fnRef = luaL_ref( L, LUA_REGISTRYINDEX );
    auto identifier = mgr->RegisterRightThumbstickAxis(CallableScriptFunctionParameters1<Vector2>(fnRef));
    lua_pushnumber(L, identifier);
    return 1;
}

std::vector<luaL_Reg> Gamepad::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
          { "RegisterLeftThumbstickAxis", lua_RegisterLeftThumbstickAxis }
        , { "RegisterRightThumbstickAxis", lua_RegisterRightThumbstickAxis }
    });
    return result;
}
