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
        void loadFile(FileMemoryBufferStreamI*);

        ///
        void registerFunctions();

        void RegisterFunctions(void *);

    /// Default, must-have main lua script functions
    public:
        void callInit();

        void callUpdate();

    /// Renderer functions available from lua
    public:

        /// lua_textureLoad(name)
        /// returns: texture_handle
        static int L_textureLoad(lua_State *L);

        /// unloadtexture(texture_handle)
        static int L_unloadTexture(lua_State *L);

        /// drawTexture(texture_handle, x, y)
        static int L_drawTexture(lua_State *L);

        /// L_loadFont(font_name)
        /// returns: font_handle
        static int L_loadFont(lua_State *L);

        /// drawText(font_handle, text, x, y, r, g, b, align: "left"|"center"|"right")
        static int L_drawText(lua_State *L);

        /// L_spriteAtlasLoad(json_path, texture_path)
        /// returns: atlas_handle
        static int L_spriteAtlasLoad(lua_State *L);

        /// L_spriteAtlasGetSprite(atlas_handle, sprite_name)
        /// returns: sprite_handle
        static int L_spriteAtlasGetSprite(lua_State *L);

        /// L_spriteDrawStaticCreate(sprite_handle, scale)
        /// returns: sprite_draw_handle
        static int L_spriteDrawStaticCreate(lua_State *L);

        /// L_spriteDrawAnimatedCreate(frame_duration_ms, scale, sprite_handle1, ...)
        /// returns: sprite_draw_handle
        static int L_spriteDrawAnimatedCreate(lua_State *L);

        /// L_spriteDrawRender(sprite_draw_handle, x, y)
        static int L_spriteDrawRender(lua_State *L);

    private:
        lua_State* L;
        EngineProviderI *m_engineProvider;
    };

};

#endif /* scriptint_engine_hpp */
