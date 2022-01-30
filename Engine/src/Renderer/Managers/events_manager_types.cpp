//
//  events_manager_types.cpp
//  Engine
//
//  Created by krzysp on 30/01/2022.
//

#include "events_manager_types.hpp"

using namespace engine;

/** Mouse Position Holders */
void EventHolderScriptCallableMousePosition::Process(Origin *val)
{
    m_function.PerformCall([&](lua_State *L){
        lua_pushnumber(L, val->x);
        lua_pushnumber(L, val->y);
        return 2;
    });
}

/** Key shortcuts holders */

bool EventHolderKeyShortcutPressed::Matches(bool shiftDown, bool controlDown, bool keys[KEY_TABLE_SIZE])
{
    for (auto& modifier : m_modifiers)
    {
        if (modifier == FLAG_SHIFT)
        {
            if (!shiftDown)
            {
                return false;
            }
        }
        else if (modifier == FLAG_CONTROL)
        {
            if (!controlDown)
            {
                return false;
            }
        }
    }

    for (auto& key : m_keys)
    {
        if (keys[key] != true)
        {
            return false;
        }
    }

    return true;
}

void EventHolderKeyShortcutPressedScript::Process(void*)
{
    m_function.PerformCall([](lua_State *l){
        return 0;
    });
}
