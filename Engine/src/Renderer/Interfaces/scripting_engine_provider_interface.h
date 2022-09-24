//
//  scripting_enging_provider_interface.h
//  Renderer
//
//  Created by krzysp on 19/12/2021.
//

#ifndef scripting_enging_provider_interface_h
#define scripting_enging_provider_interface_h

#include "file_access_provider.h"
#include "common.h"
#include "console_logger.hpp"

#ifdef __cplusplus
extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#endif //__cplusplus

#include "scripting_interfaces.h"

namespace engine
{

    /**
     Define a general script state. For LUA this would be lua_State*
     */
    typedef void* SCRIPT_STATE;

    class ScriptingEngineI: public ScriptingEngineRegistryCallerI
    {
    public:
        ///
        ScriptingEngineI() { }

        /**
         Get the internal engine state. This is based on implementation.
         The default scripting engine works on LUA so an internal LUA state
         will be returned.
         */
        virtual void *GetState() = 0;

        ///
        /// Creates a new L for lua.
        virtual void newState() = 0;

        /// Closes and frees memory taken
        /// by the script
        virtual void closeState() = 0;

        ///
        virtual void loadFile(FileStreamI*) = 0;

        ///
        virtual void loadChunk(char*) = 0;

        ///
        virtual void registerFunctions() = 0;

    /// Default, must-have main lua script functions
    public:
        virtual void callInit() = 0;

        virtual void callUpdate() = 0;

    public:
        /**
         Retrieves a scriptable object from the LUA stack if an object
         supports scripting.
         TODO: should not be in the interface!
         */

#ifndef SCRIPTING_BUILD
        template<typename T>
        static T *GetScriptingObjectPtr(lua_State *L, int index)
        {
            T **ptr = (T**)luaL_checkudata(
              L, index, T::ScriptingInterfaceName().c_str()
            );
            return *ptr;
        };

        /**
         Retrieves ordinary pointer is an object is not scriptable.
         TODO: should not be in the interface!
         */
        template<typename T>
        static T *GetNormalObjectPtr(lua_State *L, int index)
        {
            return (T*)lua_topointer(L, index);
        };
#endif
    };

    /// Provides an interface for the classes to
    /// register their functions in Lua.
    class ScriptingInterface
    {
    public:
#ifndef SCRIPTING_BUILD
        /// Get the name for the scripting table. Usually the `ClassName`.
        /// Later used in the script.
        static std::string ScriptingInterfaceName() { return ""; };

        /// Called by the scripting engine to get a list of
        /// functions to register for this object.
        static std::vector<luaL_Reg> ScriptingInterfaceFunctions() { return std::vector<luaL_Reg>(); };

        /// Final object must have
        /// static void ScriptingInterfaceRegisterFunctions(lua_State *L,className *object) defined.
        /// See the SCRIPTING_INTERFACE_HEADERS and SCRIPTING_INTERFACE_IMPL_NAME.
#endif
    };

    /// Helper macro to define .h ScriptingInterface complience.
    #define SCRIPTING_INTERFACE_HEADERS(className) public:            \
        static std::string ScriptingInterfaceName();                  \
        static std::vector<luaL_Reg> ScriptingInterfaceFunctions();   \
        void ScriptingInterfaceRegisterFunctions(lua_State *L, className*);

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
                ConsoleLog::Shared()->Log("Creating LUA Table for className:%s", tableName.c_str()); \
                lua_pushvalue(L, -1);                                               \
                lua_setfield(L, -2, "__index");                                     \
                std::vector<luaL_Reg> functions = ScriptingInterfaceFunctions();    \
                functions.push_back({nullptr, nullptr});                            \
                                                                                    \
                luaL_Reg *classFunctions = (luaL_Reg*)malloc(functions.size() * sizeof(luaL_Reg));                          \
                int i = 0;                                                          \
                std::for_each(functions.begin(), functions.end(), [&](luaL_Reg &reg){ \
                    luaL_Reg regItem = { reg.name, reg.func };                      \
                    classFunctions[i++] = regItem;                                  \
                });                                                                 \
                                                                                    \
                luaL_setfuncs(L, classFunctions, 0);                                \
                free(classFunctions);\
            }                                                                       \
                                                                                    \
            lua_setmetatable(L, -2);                                                \
        };
};

#endif /* scripting_enging_provider_interface_h */
