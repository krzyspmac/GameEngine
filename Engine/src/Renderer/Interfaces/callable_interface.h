//
//  callable_interface.h
//  Engine
//
//  Created by krzysp on 04/01/2022.
//

#ifndef callable_interface_h
#define callable_interface_h

#include "scripting_interfaces.h"
#include "callable.hpp"

namespace engine
{
    /**
     Defines an interface for the callback to either the scripting engine
     or just a lambda.
     */
    class CallableI
    {
    public:
        virtual ~CallableI() { };
    };

    /**
     Abstract definition for a callable to a curve function that can give proper animation values when progressing from one value to another.
     Available only in C++.
     @private
     */
    template <typename R, typename V>
    class CallableCurveI: public CallableI
    {
    public:
        CallableCurveI(): CallableI() { };
        virtual ~CallableCurveI() { };
        virtual V GetMin() = 0;
        virtual V GetMax() = 0;
        virtual R f(V progress) = 0;
    };

    /** A concrete instance of the whole parameter stack */
    class CallableParameterStackI
    {
    public:
        typedef int CallableScriptFunctionRef;
    protected:
        CallableScriptFunctionRef m_functionRef;
    public:
        CallableParameterStackI(CallableScriptFunctionRef ref): m_functionRef(ref) { };

        bool CanCall() { return m_functionRef != -1; };
    };

    /**
     An abstract definition of the callable function to be used in the script when
     specified by the documentation. Various script related functionality will
     extend this interface to provide their own definitions.
     */
    class CallableScriptFunctionI: public CallableI
    {
    public:
        typedef int CallableScriptFunctionRef;

        CallableScriptFunctionI(CallableScriptFunctionRef) : CallableI() { };

        /**
         Available only in C++
         @private
         */
        virtual CallableScriptFunctionRef& GetFunctionRef() = 0;

        /**
         Available only in C++
         @private
         */
        virtual bool CanCall() = 0;
    };
};

#endif /* callable_interface_h */
