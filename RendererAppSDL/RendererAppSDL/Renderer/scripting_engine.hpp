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
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
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

        /// lua_textureLoad(name)
        /// returns: texture_handle
        static int lua_textureLoad(lua_State *L);

        /// unloadtexture(texture_handle)
        static int lua_unloadTexture(lua_State *L);

        /// drawTexture(texture_handle, x, y)
        static int lua_drawTexture(lua_State *L);

        /// loadFont(font_name)
        /// returns: font_handle
        static int lua_loadFont(lua_State *L);

        /// drawText(font_handle, text, x, y, r, g, b, align: "left"|"center"|"right")
        static int lua_drawText(lua_State *L);

        /// L_spriteLoad(texture_handle, sprite_width, sprite_height, frame_count, frame_duration_ms)
        /// returns: sprite_handle
        static int lua_spriteLoad(lua_State *L);

        /// L_spriteDraw(sprite_handle, x, y, frame_number)
        static int lua_spriteDraw(lua_State *L);

        /// L_spriteDrawAnimated(sprite_handle, x, y)
        static int lua_spriteDrawAnimated(lua_State *L);

    private:
        lua_State* L;
        EngineProviderI *m_engineProvider;
    };

};

#endif /* scriptint_engine_hpp */
