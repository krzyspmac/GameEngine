//
//  scripting_enging_provider_interface.h
//  Renderer
//
//  Created by krzysp on 19/12/2021.
//

#ifndef scripting_enging_provider_interface_h
#define scripting_enging_provider_interface_h

#include "engine_provider_interface.h"
#include "file_access_provider.h"

#ifdef __cplusplus
extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#endif //__cplusplus

namespace engine
{
    class ScriptingEngineI
    {
    public:
        ///
        ScriptingEngineI() { }

        ///
        /// Creates a new L for lua.
        virtual void newState() = 0;

        /// Closes and frees memory taken
        /// by the script
        virtual void closeState() = 0;

        ///
        virtual void loadFile(FileMemoryBufferStreamI*) = 0;

        ///
        virtual void registerFunctions() = 0;

        /// Register functions for an object if that object implements
        /// ScriptingInterface.
        virtual void RegisterFunctions(void *) = 0;

    /// Default, must-have main lua script functions
    public:
        virtual void callInit() = 0;

        virtual void callUpdate() = 0;

    };

    /// Provides an interface for the classes to
    /// register their functions in Lua.
    class ScriptingInterface
    {
    public:
        /// Get the name for the scripting table. Usually the `ClassName`.
        /// Later used in the script.
        static std::string ScriptingInterfaceName() { return ""; };

        /// Called by the scripting engine to get a list of
        /// functions to register for this object.
        static std::vector<luaL_Reg> ScriptingInterfaceFunctions() { return std::vector<luaL_Reg>(); };

        /// Final object must have
        /// static void ScriptingInterfaceRegisterFunctions(lua_State *L,className *object) defined.
        /// See the SCRIPTING_INTERFACE_HEADERS and SCRIPTING_INTERFACE_IMPL_NAME.
    };

    /// Helper macro to define .h ScriptingInterface complience.
    #define SCRIPTING_INTERFACE_HEADERS(className) public:            \
        static std::string ScriptingInterfaceName();                  \
        static std::vector<luaL_Reg> ScriptingInterfaceFunctions();   \
        static void ScriptingInterfaceRegisterFunctions(lua_State *L, className*);

    #define SCRIPTING_INTERFACE_IMPL_NAME(className)                                \
        std::string className::ScriptingInterfaceName() {                           \
        std::string tableName = std::string(#className) + std::string("MetaTable"); \
            return tableName;                                                       \
        }                                                                           \
        void className::ScriptingInterfaceRegisterFunctions(                        \
            lua_State *L,                                                           \
            className *object                                                       \
        )                                                                           \
        {                                                                           \
            std::string tableName = ScriptingInterfaceName();                       \
                                                                                    \
            className **ptr = (className**)lua_newuserdata(                         \
               L, sizeof(className*)                                                \
            );                                                                      \
            *ptr = object;                                                          \
                                                                                    \
            if (luaL_newmetatable(L, tableName.c_str()))                            \
            {                                                                       \
                printf("Creating LUA Table for className:%s\n", tableName.c_str()); \
                lua_pushvalue(L, -1);                                               \
                lua_setfield(L, -2, "__index");                                     \
                std::vector<luaL_Reg> functions = ScriptingInterfaceFunctions();    \
                functions.push_back({nullptr, nullptr});                            \
                                                                                    \
                luaL_Reg classFunctions[functions.size()];                          \
                int i = 0;                                                          \
                std::for_each(functions.begin(), functions.end(), [&](luaL_Reg &reg){ \
                    luaL_Reg regItem = { reg.name, reg.func };                      \
                    classFunctions[i++] = regItem;                                  \
                });                                                                 \
                                                                                    \
                luaL_setfuncs(L, classFunctions, 0);                                \
            }                                                                       \
                                                                                    \
            lua_setmetatable(L, -2);                                                \
        };

    /// Documentation helper macros
    #define _LUA_EXPOSED(x) /// Exposed to LUA under x
};

#endif /* scripting_enging_provider_interface_h */
