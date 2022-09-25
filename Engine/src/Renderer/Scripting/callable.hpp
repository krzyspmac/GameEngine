//
//  callable.hpp
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#ifndef callable_hpp
#define callable_hpp

#include <iostream>
#include "callable_interface.h"
#include "scripting_engine_provider_interface.h"

#ifdef __cplusplus
extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#endif //__cplusplus

namespace engine
{

    /**
     Callable Script Encapsulation for a single scriptable object as parameter,
     configurable by the caller.
     */
    class CallableScriptFunctionSciptableInstance: public CallableScriptFunctionI
    {
        CallableScriptFunctionRef m_ref = -1;
    public:
        static CallableScriptFunctionSciptableInstance none()
        { return CallableScriptFunctionSciptableInstance(-1); };
    public:
        /**
         Construct a callable function by providing a reference for it.
         The function takes one paramter (ScriptableObject) and expectes no result.
         \code{lua}
         function (val)
         end
         \endcode
         */
        CallableScriptFunctionSciptableInstance(CallableScriptFunctionRef functionRef);

        /**
         Return the ref to the callable function.
         Available only in C++
         @private
         */
        CallableScriptFunctionRef& GetFunctionRef(){ return m_ref; };

        /**
         Perform the call. Gives an option to execute code inside the block.
         The block should perform all the necessary functions by the scripting
         engine. Lua objects need to be registered.
         Return the number of parameters put into the script.
         Available only in C++.
         @private
         */
        void PerformCall(std::function<int(lua_State*)> block);
        
        /**
         Available only in C++
         @private
         */
        bool CanCall() { return m_ref != -1; };
    };

    class CallableScriptFunctionParametersEmpty: public CallableScriptFunctionSciptableInstance
    {
    public:
        static CallableScriptFunctionParametersEmpty empty() {
            return CallableScriptFunctionParametersEmpty(-1);
        };

        CallableScriptFunctionParametersEmpty(CallableScriptFunctionRef ref)
        :   CallableScriptFunctionSciptableInstance(ref)
        { };

        void CallWithParameters() {
            PerformCall([&](lua_State *L){
                return 0;
            });
        }
    };

    template <typename A>
    class CallableScriptFunctionParameters1: public CallableScriptFunctionSciptableInstance
    {
    public:
        static CallableScriptFunctionParameters1<A> empty() {
            return CallableScriptFunctionParameters1<A>(-1);
        };

        CallableScriptFunctionParameters1(CallableScriptFunctionRef ref)
        :   CallableScriptFunctionSciptableInstance(ref)
        { };

        void CallWithParameters(A p1) {
            PerformCall([&](lua_State *L){
                lua_pushnumber(L, p1);
                return 1;
            });
        }
    };

    template <typename A, typename B>
    class CallableScriptFunctionParameters2: public CallableScriptFunctionSciptableInstance
    {
    public:
        static CallableScriptFunctionParameters2<A, B> empty() {
            return CallableScriptFunctionParameters2<A, B>(-1);
        };

        CallableScriptFunctionParameters2(CallableScriptFunctionRef ref)
        :   CallableScriptFunctionSciptableInstance(ref)
        { };

        void CallWithParameters(A p1, B p2) {
            PerformCall([&](lua_State *L){
                lua_pushnumber(L, p1);
                lua_pushnumber(L, p2);
                return 2;
            });
        }
    };

    template <typename A, typename B, typename C>
    class CallableScriptFunctionParameters3: public CallableScriptFunctionSciptableInstance
    {
    public:
        static CallableScriptFunctionParameters3<A, B, C> empty() {
            return CallableScriptFunctionParameters3<A, B, C>(-1);
        };

        CallableScriptFunctionParameters3(CallableScriptFunctionRef ref)
        :   CallableScriptFunctionSciptableInstance(ref)
        { };

        void CallWithParameters(A p1, B p2, C p3) {
            PerformCall([&](lua_State *L){
                lua_pushnumber(L, p1);
                lua_pushnumber(L, p2);
                lua_pushnumber(L, p3);
                return 3;
            });
        }
    };

};


#endif /* callable_hpp */
