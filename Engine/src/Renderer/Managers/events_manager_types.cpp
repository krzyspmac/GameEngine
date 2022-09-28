//
//  events_manager_types.cpp
//  Engine
//
//  Created by krzysp on 30/01/2022.
//

#include "events_manager_types.hpp"
#include "gamepad.hpp"

using namespace engine;

/** Mouse Position Holders */
void EventHolderScriptCallableMousePosition::Process(Origin *val)
{
    m_script.CallWithParameters(val->x, val->y);
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

//void EventHolderKeyShortcutPressedScript::Process(void*)
//{
//    m_script.CallWithParameters();
//}

void EventHolderMouseMoved::Process(Origin *obj)
{
    if (m_script->CanCall())
    {
        auto fnc = m_script.get();
        fnc->Call(*obj);
    }
}

void EventHolderKeyDown::Process(char *c)
{
    if (m_script.CanCall())
    {
//        m_script.PerformCall([&](lua_State *L){
//            lua_pushstring(L, c);
//            return 1;
//        });
    }
}

void EventHolderGamepadStickAxis::Process(Vector2 *vector)
{
    if (m_script.CanCall())
    {
//        m_script.PerformCall([&](lua_State *L){
//            lua_pushnumber(L, vector->x);
//            lua_pushnumber(L, vector->y);
//            return 2;
//        });
    }
}

void EventHolderGamepadConnection::Process(GamepadI **_gamepad)
{
    if (m_script == nullptr)
    {
        return;
    }

    if (m_script.get() != nullptr)
    {
        if (_gamepad != nullptr)
        {
            GamepadI* gamepad = *_gamepad;
            auto fnc = m_script.get();
            fnc->Call(gamepad, true);
        }
        else
        {
            auto fnc = m_script.get();
            fnc->Call(nullptr, false);
        }
    }
}

void EventHolderGamepadButton::Process(GamepadButtonActionHolder *descriptor)
{
    if (m_script.CanCall())
    {
//        m_script.PerformCall([&](lua_State *L){
//            lua_pushnumber(L, descriptor->button);
//            lua_pushnumber(L, descriptor->action);
//            lua_pushnumber(L, descriptor->value);
//            return 3;
//        });
    }
}
