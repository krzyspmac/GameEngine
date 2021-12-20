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
#include "engine_interface.h"

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
        ScriptingEngine();

        ///
        void setEngine(EngineI *engine);

        ///
        /// Creates a new L for lua.
        void newState();

        /// Closes and frees memory taken
        /// by the script
        void closeState();

        ///
        void loadFile(std::string fname);

        ///
        void registerFunctions();

    /// Default, must-have main lua script functions
    public:
        void callInit();

        void callUpdate();

    /// Renderer functions available from lua
    public:

        /// loadTexture(name)
        /// returns: texture_handle
        static int lua_loadTexture(lua_State *L);

        /// unloadtexture(texture_handle)
        static int lua_unloadTexture(lua_State *L);

        /// drawTexture(texture_handle, x, y)
        static int lua_drawTexture(lua_State *L);

        /// loadFont(font_name)
        /// returns: font_handle
        static int lua_loadFont(lua_State *L);

        /// drawText(font_handle, text, x, y, r, g, b, align: "left"|"center"|"right")
        static int lua_drawText(lua_State *L);

    private:
        lua_State* L;
        EngineProviderI *m_engineProvider;
        EngineI *m_engine;
    };

};

#endif /* scriptint_engine_hpp */
