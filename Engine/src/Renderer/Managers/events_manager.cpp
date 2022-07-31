//
//  events_manager.cpp
//  Engine
//
//  Created by krzysp on 30/12/2021.
//

#include "events_manager.hpp"
#include "engine.hpp"

using namespace engine;

EventsManager::EventsManager(EventProviderI &provider, EngineProviderI &engineProvider)
    : m_eventProvider(provider)
    , m_identifierCounter(0)
    , m_engineProvider(engineProvider)
    , m_shiftKeyDown(false)
    , m_controlKeyDown(false)
{
    bzero(m_keys, KEY_TABLE_SIZE);
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
                auto& state = m_keys[key];
                auto& isDown = event->GetIsDown();
                if (state != isDown)
                {
                    m_keys[key] = isDown;
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
}

void EventsManager::UnregisterAllEvents()
{
    m_mouseMoves.clear();
    m_mouseClicks.clear();
    m_keyshortcuts.clear();
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

std::vector<luaL_Reg> EventsManager::ScriptingInterfaceFunctions()
{
    std::vector<luaL_Reg> result({
        { "RegisterMouseMovedEvents", &lua_EventsManager_RegisterMouseMoveEvents }
      , { "RegisterMouseClickedEvents", &lua_EventsManager_RegisterMouseClickedEvents }
      , { "RegisterKeyShortcutsEvents", &lua_EventsManager_RegisterKeyShortcutsEvents }
      , { "UnregisterEvent", &lua_EventsManager_UnregisterEvent }
      , { "IsShiftDown", &lua_EventsManager_IsShiftDown }
      , { "IsControlDown", &lua_EventsManager_IsControlDown }
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
