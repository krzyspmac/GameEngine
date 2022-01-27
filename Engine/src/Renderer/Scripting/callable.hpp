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

namespace engine
{
    /**
     Curve lambda. Provide your own implementation of the curve
     to be used in animation/translator.
     Available only in C++
     @private
     */
    class CallableCurveLamba: public CallableCurveI<float, float>
    {
        float m_min;
        float m_max;
        float m_diff;
        std::function<float(float, float, float)> m_lambda;
    public:
        CallableCurveLamba(float min, float max, std::function<float(float, float, float)> lambda);
    public:
        float GetMin() { return m_min; };
        float GetMax() { return m_max; };
        float GetDiff() { return m_diff; };
        float f(float progress);
    };

    /**
     Callable Script Function.
     */
    class CallableScriptFunctionParamless: public CallableScriptFunctionI
    {
        CallableScriptFunctionRef m_ref = -1;
    public:
        static CallableScriptFunctionParamless none;
    public:
        /**
         Construct a callable function by providing a reference for it.
         In LUA this is:
         SomeObject(function() ... end)
         */
        /**
         Construct a callable function by providing a reference for it.
         The function takes no parameters and expectes no result.
         \code{lua}
         function ()
         end
         \endcode
         */
        CallableScriptFunctionParamless(CallableScriptFunctionRef functionRef);

        /**
         Return the ref to the callable function.
         Available only in C++
         @private
         */
        CallableScriptFunctionRef& GetFunctionRef(){ return m_ref; };

        /**
         Perform the call.
         Available only in C++.
         @private
         */
        void PerformCall();

        /**
         Available only in C++
         @private
         */
        bool CanCall() { return m_ref != -1; };
    };

    /**
     Callable Script Encapsulation for a single number parameter.
     */
    class CallableScriptFunctionNumber: public CallableScriptFunctionI
    {
        CallableScriptFunctionRef m_ref = - 1;
    public:
        static CallableScriptFunctionNumber none;
    public:
        /**
         Construct a callable function by providing a reference for it.
         The function takes one paramter (float) and expectes no result.
         \code{lua}
         function (val)
         end
         \endcode
         */
        CallableScriptFunctionNumber(CallableScriptFunctionRef functionRef);

        /**
         Return the ref to the callable function.
         Available only in C++
         @private
         */
        CallableScriptFunctionRef& GetFunctionRef(){ return m_ref; };

        /**
         Perform the call.
         Available only in C++.
         @private
         */
        void PerformCall(float val);

        /**
         Available only in C++
         @private
         */
        bool CanCall() { return m_ref != -1; };
    };

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

};


#endif /* callable_hpp */
