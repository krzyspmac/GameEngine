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

//                for (auto& keyHandler : m_keyshortcuts)
//                {
//                    if (keyHandler.Matches(m_shiftKeyDown, m_controlKeyDown, m_keys))
//                    {
//                        keyHandler.Process(nullptr);
//                    }
//                }
//
//                for (auto& keyHandler : m_keyshortcutsScript)
//                {
//                    if (keyHandler.Matches(m_shiftKeyDown, m_controlKeyDown, m_keys))
//                    {
//                        keyHandler.Process(nullptr);
//                    }
//                }

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
                break;
            }
            case EVENT_MOUSEUP:
            {
                auto mouseLocation = &(ENGINE().GetMousPosition());

                for (auto& codeHandler : m_mouseClicks)
                {
                    codeHandler.Process(mouseLocation);
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
            case EVENT_GAMEPAD_BUTTON_ACTION_CHANGE:
            {
                auto *event = static_cast<EventGamepadButtonEventChanged*>(baseEvent);
                auto& action = event->GetAction();

                for (auto& gamepad : m_gamepads)
                {
                    auto *ptr = gamepad.get();
                    if (ptr != nullptr)
                    {
                        ptr->ProcessButtonEvent(&action);
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
                        codeHandler.Process((GamepadI**)&gamepad);
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

EventIdentifier EventsManager::RegisterMouseMovedEvents(std::shared_ptr<CallableParameters1<Origin>> fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_mouseMoves.push_back(EventHolderMouseMoved(identifier, fnc));
    return identifier;
}

EventIdentifier EventsManager::RegisterMouseClickedEvents(std::function<void(void*)> lambda)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_mouseClicks.push_back(EventHolderMouseClicked(identifier, lambda));
    return identifier;
}

EventIdentifier EventsManager::RegisterKeyShortcut(std::vector<EventFlagType> modifiers, std::vector<unsigned short>keys, std::function<void(void*)> lambda)
{
//    EventIdentifier identifier = ++m_identifierCounter;
//    m_keyshortcuts.push_back(EventHolderKeyShortcutLambda(identifier, lambda, modifiers, keys));
//    return identifier;
    return -1;
}

EventIdentifier EventsManager::RegisterKeyShortcut(std::vector<EventFlagType> modifiers, std::vector<unsigned short>keys, CallableScriptFunctionParametersEmpty fnc)
{
//    EventIdentifier identifier = ++m_identifierCounter;
//    m_keyshortcutsScript.push_back(EventHolderKeyShortcutPressedScript(identifier, fnc, modifiers, keys));
//    return identifier;
    return -1;
}

EventIdentifier EventsManager::RegisterKeyDown(CallableScriptFunctionParameters1<char> fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
//    m_keyDowns.push_back(EventHolderKeyDown(identifier, fnc));
    return identifier;
}

EventIdentifier EventsManager::RegisterKeyUp(CallableScriptFunctionParameters1<char> fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
//    m_keyUps.push_back(EventHolderKeyDown(identifier, fnc));
    return identifier;
}

EventIdentifier EventsManager::RegisterGamepadConnection(std::shared_ptr<CallableParameters2<GamepadI*, bool>> fnc)
{
    EventIdentifier identifier = ++m_identifierCounter;
    m_gamepadConnection.push_back(EventHolderGamepadConnection(identifier, fnc));
    return identifier;
}

void EventsManager::Unregister(EventHolderIdentifier* eventHolder)
{
    if (eventHolder != nullptr)
    {
        UnregisterEvent(eventHolder->GetIdentifier());
    }
}

template <typename T>
void RemoveIfExists(EventIdentifier identifier, std::vector<T> &list)
{
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        EventHolderIdentifier holder = static_cast<EventHolderIdentifier>(*it);
        if (holder.GetIdentifier() == identifier)
        {
            list.erase(it);
            return;
        }
    }
}

void EventsManager::UnregisterEvent(EventIdentifier identifier)
{
    RemoveIfExists(identifier, m_mouseMoves);
    RemoveIfExists(identifier, m_mouseClicks);
//    RemoveIfExists(identifier, m_keyshortcuts);
    RemoveIfExists(identifier, m_keyDowns);
    RemoveIfExists(identifier, m_keyUps);
    RemoveIfExists(identifier, m_gamepadConnection);
}

void EventsManager::UnregisterAllEvents()
{
    m_mouseMoves.clear();
    m_mouseClicks.clear();
//    m_keyshortcuts.clear();
    m_keyDowns.clear();
    m_keyUps.clear();
    m_gamepadConnection.clear();
}

#pragma mark - Scripting Interface
/** Scripting interface */

SCRIPTING_INTERFACE_IMPL_NAME(EventsManager);

static int lua_EventsManager_RegisterMouseMoveEvents(lua_State *L)
{
//    EventsManager *mgr = ScriptingEngineI::GetScriptingObjectPtr<EventsManager>(L, 1);
//
//    int functionEndRef = luaL_ref( L, LUA_REGISTRYINDEX );
//    auto identifier = mgr->RegisterMouseMovedEvents(CallableScriptFunctionParameters2<float, float>(functionEndRef));
//    lua_pushnumber(L, identifier);
//    return 1;
    return 0;
}

static int lua_EventsManager_RegisterMouseClickedEvents(lua_State *L)
{
//    EventsManager *mgr = ScriptingEngineI::GetScriptingObjectPtr<EventsManager>(L, 1);
//
//    int functionEndRef = luaL_ref( L, LUA_REGISTRYINDEX );
//    auto identifier = mgr->RegisterMouseClickedEvents(CallableScriptFunctionParameters2<float, float>(functionEndRef));
//    lua_pushnumber(L, identifier);
//    return 1;
    return 0;
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
//    EventsManager *mgr = ScriptingEngineI::GetScriptingObjectPtr<EventsManager>(L, 1);
//    int fnRef = luaL_ref( L, LUA_REGISTRYINDEX );
//    auto identifier = mgr->RegisterGamepadConnection(CallableScriptFunctionParameters2<GamepadI, bool>(fnRef));
//    lua_pushnumber(L, identifier);
//    return 1;
    return 0;
}

static int lua_EventsManager_GetGamepad(lua_State *L)
{
//    EventsManager *mgr = ScriptingEngineI::GetScriptingObjectPtr<EventsManager>(L, 1);
//    auto& gamepads = mgr->GetGamepads();
//    if (gamepads.size())
//    {
//        auto *first = gamepads.at(0).get();
//        if (first != nullptr)
//        {
//            auto *ptr = dynamic_cast<Gamepad*>(first);
//            if (ptr != nullptr)
//            {
//                ptr->ScriptingInterfaceRegisterFunctions(L, ptr);
//                return 1;
//            }
//        }
//    }

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
