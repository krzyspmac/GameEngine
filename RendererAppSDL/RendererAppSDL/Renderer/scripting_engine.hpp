//
//  scriptint_engine.hpp
//  RendererApp
//
//  Created by krzysp on 19/12/2021.
//

#ifndef scriptint_engine_hpp
#define scriptint_engine_hpp

#include "scripting_engine_provider_interface.h"
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

    class ScriptingEngine : public ScriptingEngineI
    {
    public:
        ///
        ScriptingEngine(EngineProviderI *engineProvider);

        ///
        /// Creates a new L for lua.
        void newState();

        /// Closes and frees memory taken
        /// by the script
        void closeState();

        ///
        void loadFile(const char *fname);

        ///
        void registerFunctions();

    /// Default, must-have main lua script functions
    public:
        void callUpdate();

    /// Renderer functions available from lua
    public:

        /// drawDebugString(x, y, val, text)
        static int lua_drawDebugString(lua_State *lua);

    private:
        lua_State* L;
        EngineProviderI *m_engineProvider;
    };

};

#endif /* scriptint_engine_hpp */
