//
//  events_manager.cpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#include "events_manager.hpp"
#include "engine.hpp"
#include "gamepad.hpp"

using namespace engine;

EventsManager::EventsManager(EventProviderI &provider, EngineProviderI &engineProvider)
    : m_eventProvider(provider)
    , m_identifierCounter(0)
    , m_engineProvider(engineProvider)
    , m_shiftKeyDown(false)
    , m_controlKeyDown(false)
{
    bzero(m_keys, KEY_TABLE_SIZE);
    m_keysWrapper[0] = '\0';
    m_keysWrapper[1] = '\0';
}

int EventsManager::DoEvents()
{
    EventI *baseEvent = nullptr;

    while (m_eventProvider.PollEvent(&baseEvent))
    {
        switch (baseEvent->GetType())
        {
            case EVENT_NONE:
            {
                break;
            }
            case EVENT_KEY_FLAG_STATE_CHANGE:
            {
                auto* event = static_cast<EventKeyFlagStateChanged*>(baseEvent);
                switch (event->GetFlagType())
                {
                    case FLAG_SHIFT:
                    {
                        m_shiftKeyDown = event->GetState();
                        break;
                    }
                    case FLAG_CONTROL:
                    {
                        m_controlKeyDown = event->GetState();
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
                break;
            }
            case EVENT_KEY_STATE_CHANGE:
            {
                auto* event = static_cast<EventKeyStateChanged*>(baseEvent);
                auto& key = event->GetKey();
                auto& isDown = event->GetIsDown();

                m_keys[key] = isDown;
                m_keysWrapper[0] = key;

                if (isDown)
                {
                    for (auto& keyHandler : m_keyDowns)
                    {
                        keyHandler.Process(m_keysWrapper);
                    }
                }
                else
                {
                    for (auto& keyHandler : m_keyUps)
                    {
                        keyHandler.Process(m_keysWrapper);
                    }
                }

                for (auto& keyHandler : m_keyshortcuts)
                {
                    if (keyHandler.Matches(m_shiftKeyDown, m_controlKeyDown, m_keys))
                    {
                        keyHandler.Process(nullptr);
                    }
                }

                for (auto& keyHandler : m_keyshortcutsScript)
                {
                    if (keyHandler.Matches(m_shiftKeyDown, m_controlKeyDown, m_keys))
                    {
                        keyHandler.Process(nullptr);
                    }
                }

                break;
            }
            case EVENT_MOUSEMOVE:
            {
                auto mouseEvent = static_cast<EventMouseMove*>(baseEvent);
                auto mouseLocation = &mouseEvent->GetLocation();

                for (auto& codeHandler : m_mouseMoves)
                {
                    codeHandler.Process(mouseLocation);
                }

                for (auto& handler : m_mouseMovesScript)
                {
                    handler.Process(mouseLocation);
                }
                break;
            }
            case EVENT_MOUSEUP:
            {
                auto mouseLocation = &(ENGINE().GetMousPosition());

                for (auto& codeHandler : m_mouseClicks)
                {
                    codeHandler.Process(mouseLocation);
                }

                for (auto& handler : m_mouseClickedScript)
                {
                    handler.Process(mouseLocation);
                }
                break;
            }
            case EVENT_GAMEPAD_THUMSTICK_AXIS_CHANGE:
            {
                auto* event = static_cast<EventGamepadThumbstickAxisChanged*>(baseEvent);
                for (auto& gamepad : m_gamepads)
                {
                    auto *ptr = gamepad.get();
                    if (ptr != nullptr)
                    {
                        ptr->ProcessEvent(event);
                    }
                }
                break;
            }
            case EVENT_GAMEPAD_CONNECTION_CHANGE:
            {
                auto* event = static_cast<EventGamepadConnectionChanged*>(baseEvent);

                m_gamepads.clear();

                if (event->GetConnectionStatus() == GAMEPAD_CONNECTION_STATUS_CONNECTED)
                {
                    auto *gamepadHandle = event->GetDeviceHandle();
                    auto *gamepad = new Gamepad(event->GetGamepadType(), event->GetGamepadFamily(), gamepadHandle);
                    m_gamepads.emplace_back(std::move(gamepad));

                    for (auto& codeHandler : m_gamepadConnection)
                    {
                        codeHandler.Process(gamepad);
                    }
                }
                else
                {
                    for (auto& codeHandler : m_gamepadConnection)
                    {
                        codeHandler.Process(nullptr);
                    }

                }
                break;
            }
            case EVENT_QUIT:
            {
                return 1;
            }
        }
    }

    return 0;
}

EventIdentifier EventsManager::RegisterMouseMovedEvents(std::function<void(Origin*)> lambda)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_mouseMoves.push_back(EventHolderMouseMoved(identifier, lambda));
    return identifier;
}

EventIdentifier EventsManager::RegisterMouseMovedEvents(CallableScriptFunctionParameters2<float, float> caller)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_mouseMovesScript.push_back(EventHolderMouseMovedScript(identifier, caller));
    return identifier;
}

EventIdentifier EventsManager::RegisterMouseClickedEvents(std::function<void(void*)> lambda)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_mouseClicks.push_back(EventHolderMouseClicked(identifier, lambda));
    return identifier;;
}

EventIdentifier EventsManager::RegisterMouseClickedEvents(CallableScriptFunctionParameters2<float, float> caller)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_mouseClickedScript.push_back(EventHolderMouseClickedScript(identifier, caller));
    return identifier;
}

EventIdentifier EventsManager::RegisterKeyShortcut(std::vector<EventFlagType> modifiers, std::vector<unsigned short>keys, std::function<void(void*)> lambda)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_keyshortcuts.push_back(EventHolderKeyShortcutLambda(identifier, lambda, modifiers, keys));
    return identifier;
}

EventIdentifier EventsManager::RegisterKeyShortcut(std::vector<EventFlagType> modifiers, std::vector<unsigned short>keys, CallableScriptFunctionParametersEmpty fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_keyshortcutsScript.push_back(EventHolderKeyShortcutPressedScript(identifier, fnc, modifiers, keys));
    return identifier;
}

EventIdentifier EventsManager::RegisterKeyDown(CallableScriptFunctionParameters1<char> fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_keyDowns.push_back(EventHolderKeyDown(identifier, fnc));
    return identifier;
}

EventIdentifier EventsManager::RegisterKeyUp(CallableScriptFunctionParameters1<char> fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_keyUps.push_back(EventHolderKeyDown(identifier, fnc));
    return identifier;
}

EventIdentifier EventsManager::RegisterGamepadConnection(CallableScriptFunctionParameters2<GamepadI, bool> fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_gamepadConnection.push_back(EventHolderGamepadConnection(identifier, fnc));
    return identifier;
}

EventIdentifier EventsManager::RegisterLeftThumbstickAxis(CallableScriptFunctionParameters1<Vector2> fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_leftStickAxisChange.push_back(EventHolderGamepadStickAxis(identifier, fnc));
    return identifier;
}

EventIdentifier EventsManager::RegisterRightThumbstickAxis(CallableScriptFunctionParameters1<Vector2> fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_rightStickAxisChange.push_back(EventHolderGamepadStickAxis(identifier, fnc));
    return identifier;
}

void EventsManager::UnregisterEvent(EventIdentifier identifier)
{
    for (auto it = m_mouseMoves.begin(); it != m_mouseMoves.end(); it++)
    {
        if ((*it).GetIdentifier() == identifier)
        {
            m_mouseMoves.erase(it);
            return;
        }
    }
    for (auto it = m_mouseMovesScript.begin(); it != m_mouseMovesScript.end(); it++)
    {
        if ((*it).GetIdentifier() == identifier)
        {
            m_mouseMovesScript.erase(it);
            return;
        }
    }
    for (auto it = m_mouseClicks.begin(); it != m_mouseClicks.end(); it++)
    {
        if ((*it).GetIdentifier() == identifier)
        {
            m_mouseClicks.erase(it);
            return;
        }
    }
    for (auto it = m_mouseClickedScript.begin(); it != m_mouseClickedScript.end(); it++)
    {
        if ((*it).GetIdentifier() == identifier)
        {
            m_mouseClickedScript.erase(it);
            return;
        }
    }
    for (auto it = m_keyshortcuts.begin(); it != m_keyshortcuts.end(); it++)
    {
        if ((*it).GetIdentifier() == identifier)
        {
            m_keyshortcuts.erase(it);
            return;
        }
    }
    for (auto it = m_keyshortcutsScript.begin(); it != m_keyshortcutsScript.end(); it++)
    {
        if ((*it).GetIdentifier() == identifier)
        {
            m_keyshortcutsScript.erase(it);
            return;
        }
    }
    for (auto it = m_keyDowns.begin(); it != m_keyDowns.end(); it++)
    {
        if ((*it).GetIdentifier() == identifier)
        {
            m_keyDowns.erase(it);
            return;
        }
    }
    for (auto it = m_keyUps.begin(); it != m_keyUps.end(); it++)
    {
        if ((*it).GetIdentifier() == identifier)
        {
            m_keyUps.erase(it);
            return;
        }
    }
    for (auto it = m_leftStickAxisChange.begin(); it != m_leftStickAxisChange.end(); it++)
    {
        if ((*it).GetIdentifier() == identifier)
        {
            m_leftStickAxisChange.erase(it);
            return;
        }
    }
    for (auto it = m_rightStickAxisChange.begin(); it != m_rightStickAxisChange.end(); it++)
    {
        if ((*it).GetIdentifier() == identifier)
        {
            m_rightStickAxisChange.erase(it);
            return;
        }
    }
}

void EventsManager::UnregisterAllEvents()
{
    m_mouseMoves.clear();
    m_mouseClicks.clear();
    m_keyshortcuts.clear();
    m_keyDowns.clear();
    m_keyUps.clear();
    m_gamepadConnection.clear();
    m_leftStickAxisChange.clear();
    m_rightStickAxisChange.clear();
}

#pragma mark - Scripting Interface
/** Scripting interface */

SCRIPTING_INTERFACE_IMPL_NAME(EventsManager);

static int lua_EventsManager_RegisterMouseMoveEvents(lua_State *L)
{
    EventsManager *mgr = ScriptingEngineI::GetScriptingObjectPtr<EventsManager>(L, 1);

    int functionEndRef = luaL_ref( L, LUA_REGISTRYINDEX );
    auto identifier = mgr->RegisterMouseMovedEvents(CallableScriptFunctionParameters2<float, float>(functionEndRef));
    lua_pushnumber(L, identifier);
    return 1;
}

static int lua_EventsManager_RegisterMouseClickedEvents(lua_State *L)
{
    EventsManager *mgr = ScriptingEngineI::GetScriptingObjectPtr<EventsManager>(L, 1);

    int functionEndRef = luaL_ref( L, LUA_REGISTRYINDEX );
    auto identifier = mgr->RegisterMouseClickedEvents(CallableScriptFunctionParameters2<float, float>(functionEndRef));
    lua_pushnumber(L, identifier);
    return 1;
}

static int lua_EventsManager_RegisterKeyShortcutsEvents(lua_State *L)
{
    EventsManager *mgr = ScriptingEngineI::GetScriptingObjectPtr<EventsManager>(L, 1);

    std::string modifiersString = lua_tostring(L, 2);
    std::string charactersString = lua_tostring(L, 3);
    int fnRef = luaL_ref( L, LUA_REGISTRYINDEX );

    auto modifiers = map<std::string, EventFlagType>(explode(modifiersString, "|"), [](std::string type) {
        return engine::String2EventFlagType(type);
    });

    auto keys = map<std::string, unsigned short>(explode(charactersString, "|"), [](std::string cs){
        return cs.at(0);
    });

    auto identifier = mgr->RegisterKeyShortcut(modifiers, keys, CallableScriptFunctionParametersEmpty(fnRef));
    lua_pushnumber(L, identifier);
    return 1;
}

static int lua_EventsManager_UnregisterEvent(lua_State *L)
{
    EventsManager *mgr = ScriptingEngineI::GetScriptingObjectPtr<EventsManager>(L, 1);
    int eventIdentifier = lua_tonumber(L, 2);
    mgr->UnregisterEvent(eventIdentifier);
    return 0;
}

static int lua_EventsManager_IsShiftDown(lua_State *L)
{
    EventsManager *mgr = ScriptingEngineI::GetScriptingObjectPtr<EventsManager>(L, 1);
    lua_pushnumber(L, mgr->IsShiftDown());
    return 1;
}

static int lua_EventsManager_IsControlDown(lua_State *L)
{
    EventsManager *mgr = ScriptingEngineI::GetScriptingObjectPtr<EventsManager>(L, 1);
    lua_pushnumber(L, mgr->IsControlDown());
    return 1;
}

static int lua_EventsManager_RegisterKeyDown(lua_State *L)
{
    EventsManager *mgr = ScriptingEngineI::GetScriptingObjectPtr<EventsManager>(L, 1);
    int fnRef = luaL_ref( L, LUA_REGISTRYINDEX );
    auto identifier = mgr->RegisterKeyDown(CallableScriptFunctionParameters1<char>(fnRef));
    lua_pushnumber(L, identifier);
    return 1;
}

static int lua_EventsManager_RegisterKeyUp(lua_State *L)
{
    EventsManager *mgr = ScriptingEngineI::GetScriptingObjectPtr<EventsManager>(L, 1);
    int fnRef = luaL_ref( L, LUA_REGISTRYINDEX );
    auto identifier = mgr->RegisterKeyUp(CallableScriptFunctionParameters1<char>(fnRef));
    lua_pushnumber(L, identifier);
    return 1;
}

static int lua_EventsManager_RegisterGamepadConnection(lua_State *L)
{
    EventsManager *mgr = ScriptingEngineI::GetScriptingObjectPtr<EventsManager>(L, 1);
    int fnRef = luaL_ref( L, LUA_REGISTRYINDEX );
    auto identifier = mgr->RegisterGamepadConnection(CallableScriptFunctionParameters2<GamepadI, bool>(fnRef));
    lua_pushnumber(L, identifier);
    return 1;
}

static int lua_EventsManager_GetGamepad(lua_State *L)
{
    EventsManager *mgr = ScriptingEngineI::GetScriptingObjectPtr<EventsManager>(L, 1);
    auto& gamepads = mgr->GetGamepads();
    if (gamepads.size())
    {
        auto *first = gamepads.at(0).get();
        if (first != nullptr)
        {
            auto *ptr = dynamic_cast<Gamepad*>(first);
            if (ptr != nullptr)
            {
                ptr->ScriptingInterfaceRegisterFunctions(L, ptr);
                return 1;
            }
        }
    }

    return 0;
}
std::vector<luaL_Reg> EventsManager::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "RegisterMouseMovedEvents", &lua_EventsManager_RegisterMouseMoveEvents }
      , { "RegisterMouseClickedEvents", &lua_EventsManager_RegisterMouseClickedEvents }
      , { "RegisterKeyShortcutsEvents", &lua_EventsManager_RegisterKeyShortcutsEvents }
      , { "UnregisterEvent", &lua_EventsManager_UnregisterEvent }
      , { "IsShiftDown", &lua_EventsManager_IsShiftDown }
      , { "IsControlDown", &lua_EventsManager_IsControlDown }
      , { "RegisterKeyDown", &lua_EventsManager_RegisterKeyDown }
      , { "RegisterKeyUp", &lua_EventsManager_RegisterKeyUp }
      , { "RegisterGamepadConnection", lua_EventsManager_RegisterGamepadConnection }
      , { "GetGamepad", lua_EventsManager_GetGamepad }
    });
    return result;
}

/** Helper functions */

EventFlagType engine::String2EventFlagType(std::string string)
{
    static std::vector<std::string> values = { "none", "shift", "control", "alt", "command" };

    for (int i = 0; i < values.size(); i++)
    {
        if (string == values.at(i))
        {
            return (EventFlagType)i;
        }
    }

    return FLAG_NONE;
}
