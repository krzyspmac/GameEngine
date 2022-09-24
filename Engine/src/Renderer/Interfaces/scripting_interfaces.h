//
//  scripting_interfaces.h
//  Engine
//
//  Created by krzysp on 11/06/2022.
//

#ifndef scripting_interfaces_h
#define scripting_interfaces_h

#ifndef SCRIPTING_BUILD
#ifdef __cplusplus
extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#endif //__cplusplus
#endif // #ifndef SCRIPTING_BUILD

namespace engine
{
    class ScriptingEngineRegistryCallerI
    {
    public:
        /**
         Calls a registry function that is a code that has been created
         in LUA when passing a `function` as a parameter, i.e.:
             f = function()
            end)

         Allows the aller to put in parameters if needed. Call with a lambda,
         register the parameters as necessary and return the number of parameters
         added.

         Checks if funcRef >= 0, otherwise does nothing.
         */

#ifndef SCRIPTING_BUILD
        virtual void CallRegistryFunction(int funcRef, std::function<int(lua_State*)> lambda) = 0;
#endif
    };
};

#endif /* scripting_interfaces_h */
