//
//  scripting_enging_provider_interface.h
//  Renderer
//
//  Created by krzysp on 19/12/2021.
//

#ifndef scripting_enging_provider_interface_h
#define scripting_enging_provider_interface_h

#include "engine_provider_interface.h"

#ifdef __cplusplus
extern "C" {
    #include "../../../Lua/code/src/lua.h"
    #include "../../../Lua/code/src/lualib.h"
    #include "../../../Lua/code/src/lauxlib.h"
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
        virtual void loadFile(const char *fname) = 0;

        ///
        virtual void registerFunctions() = 0;

    /// Default, must-have main lua script functions
    public:
        virtual void callUpdate() = 0;

    };
};

#endif /* scripting_enging_provider_interface_h */
